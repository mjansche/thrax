// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright 2005-2011 Google, Inc.
// Author: mjansche@google.com (Martin Jansche)
//
// A helper class that constructs a prefix-tree (trie) transducer from a finite
// dictionary of weighted string pairs.
//
// For efficiency, this class constructs its own representation of the
// prefix-tree transducer, before writing it to an FST.  The representation
// consists of a trie for the input symbols of the transducer (using the INode
// struct); at each final state of the input trie there is a trie for the
// outputs associated with this input (using the ONode struct).

#ifndef THRAX_ALGO_PREFIX_TREE_H_
#define THRAX_ALGO_PREFIX_TREE_H_

#include <map>
#include <stack>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/arc.h>
#include <fst/vector-fst.h>
#include <thrax/compat/stlfunctions.h>

namespace fst {

// This class is neither thread-safe nor thread-hostile.
template <class Arc>
class PrefixTree {
  typedef typename Arc::StateId StateId;
  typedef typename Arc::Label Label;
  typedef typename Arc::Weight Weight;

  struct INode;
  struct ONode;

  typedef map<Label, INode *> ichild_map;
  typedef map<Label, ONode *> ochild_map;

  // Prefix tree node for the input labels of the FST.
  class INode {
   public:
    INode() : output(NULL), state(kNoStateId) {}
    ichild_map children;
    ONode *output;
    StateId state;
  };

  // Prefix tree node for the output labels of the FST.
  struct ONode {
    ONode() : weight(Weight::Zero()), state(kNoStateId) {}
    ochild_map children;
    Weight weight;
    StateId state;
  };

 public:
  PrefixTree() : num_states_(0), root_(NULL) {
  }

  ~PrefixTree() {
    Clear();
  }

  int num_states() const { return num_states_; }

  // Add an entry to the prefix tree, consisting of two label sequences and a
  // weight.  Each label sequence must be provided as a pair of iterators.
  template <typename Iterator1, typename Iterator2>
  void Add(Iterator1 iter1, Iterator1 end1,
           Iterator2 iter2, Iterator2 end2,
           const Weight &weight = Weight::One()) {
    if (!root_) {
      CHECK_EQ(0, num_states_);
      root_ = new INode();
      root_->state = num_states_++;
    }
    INode *n = root_;
    for (/*empty*/; iter1 != end1; ++iter1) {
      if (0 == *iter1)  // Skip over epsilons.
        continue;
      n = LookupOrInsertNew(&n->children, *iter1);
      if (kNoStateId == n->state)
        n->state = num_states_++;
    }
    if (!n->output) {
      n->output = new ONode();
      n->output->state = num_states_++;
    }
    ONode *o = n->output;
    for (/*empty*/; iter2 != end2; ++iter2) {
      if (0 == *iter2)  // Skip over epsilons.
        continue;
      o = LookupOrInsertNew(&o->children, *iter2);
      if (kNoStateId == o->state)
        o->state = num_states_++;
    }
    o->weight = Plus(o->weight, weight);
  }

  // Removes all elements from this prefix tree.
  void Clear() {
    if (!root_) {
      CHECK_EQ(0, num_states_);
      return;
    }
    stack<INode *> iq;
    stack<ONode *> oq;
    // First, perform a simple depth-first traversal over the input trie,
    // starting at the root node.  Node coloring is not needed, since we're
    // dealing with a tree.
    iq.push(root_);
    while (!iq.empty()) {
      INode *n = iq.top();
      iq.pop();
      if (n->output)
        oq.push(n->output);  // Found a root node of an output trie.
      for (typename ichild_map::const_iterator iter = n->children.begin();
           iter != n->children.end(); ++iter) {
        iq.push(iter->second);
      }
      delete n;
    }
    // Second, perform simple depth-first traversals over the output tries,
    // starting at their root nodes.
    while (!oq.empty()) {
      ONode *o = oq.top();
      oq.pop();
      for (typename ochild_map::const_iterator oter = o->children.begin();
           oter != o->children.end(); ++oter) {
        oq.push(oter->second);
      }
      delete o;
    }
    num_states_ = 0;
    root_ = NULL;
  }

  // Write the current prefix tree transducer to 'fst'.
  void ToFst(VectorFst<Arc> *fst) {
    if (!fst) {
      LOG(FATAL) << "fst must be non NULL";
    }
    fst->DeleteStates();
    if (0 == num_states_) {
      CHECK(!root_);
      return;
    }
    // For the creation of the FST to be efficient, we must reserve enough space
    // for the states and arcs, to avoid reallocation and internal copying.
    fst->ReserveStates(num_states_);
    for (int i = 0; i < num_states_; ++i)
      fst->AddState();
    fst->SetStart(root_->state);
    stack<INode *> iq;
    stack<ONode *> oq;
    iq.push(root_);
    while (!iq.empty()) {
      INode *n = iq.top();
      iq.pop();
      StateId q = n->state;
      CHECK_NE(kNoStateId, q);
      ONode *o = n->output;
      fst->ReserveArcs(q, (o ? 1 : 0) + n->children.size());
      if (o) {
        fst->AddArc(q, Arc(0, 0, Arc::Weight::One(), o->state));
        oq.push(o);
      }
      for (typename ichild_map::iterator iter = n->children.begin();
           iter != n->children.end(); ++iter) {
        fst->AddArc(q, Arc(iter->first, 0, Arc::Weight::One(),
                           iter->second->state));
        iq.push(iter->second);
      }
    }
    while (!oq.empty()) {
      ONode *o = oq.top();
      oq.pop();
      StateId q = o->state;
      CHECK_NE(kNoStateId, q);
      for (typename ochild_map::iterator oter = o->children.begin();
           oter != o->children.end(); ++oter) {
        fst->AddArc(q, Arc(0, oter->first, Arc::Weight::One(),
                           oter->second->state));
        oq.push(oter->second);
      }
      fst->SetFinal(q, o->weight);
    }
  }

 private:
  int num_states_;
  INode *root_;
  DISALLOW_COPY_AND_ASSIGN(PrefixTree);
};

}  // namespace fst

#endif  // THRAX_ALGO_PREFIX_TREE_H_
