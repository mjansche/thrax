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
// Author: ttai@google.com (Terry Tai)
//
// The AbstractGrmManager holds a set of FSTs in memory and performs
// rewrites via composition. The class is parametrized by the FST arc
// type and mutex type. AbstractGrmManager is thread-compatible.

#ifndef NLP_GRM_LANGUAGE_ABSTRACT_GRM_MANAGER_H_
#define NLP_GRM_LANGUAGE_ABSTRACT_GRM_MANAGER_H_

#include <map>
#include <string>
#include <vector>
using std::vector;

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/extensions/pdt/compose.h>
#include <fst/extensions/pdt/pdt.h>
#include <fst/extensions/pdt/shortest-path.h>
#include <fst/arc.h>
#include <fst/fstlib.h>
#include <fst/fst.h>
#include <fst/string.h>
#include <fst/vector-fst.h>
#include <thrax/make-parens-pair-vector.h>
#include <thrax/compat/stlfunctions.h>

namespace thrax {

template <typename Arc, typename TheMutexType>
class AbstractGrmManager {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;
  typedef typename Arc::Label Label;

  virtual ~AbstractGrmManager();

  // Provides a pointer to the underlying FST map so that we can set it
  // directly.  Note that use of this pointer may break the thread-compatibility
  // of this class (if one thread mucks with this pointer while another thread
  // calls other const functions).
  map<string, Transducer*>* GetFstMap() { return &fsts_; }

  // Const version of the above.
  const map<string, Transducer*> &GetFstMap() const { return fsts_; }

  // ***************************************************************************
  // REWRITE: These functions perform the actual rewriting of inputs using the
  // named FSTs.

  // Rewrites the input to the output (in various parse modes).  Returns false
  // on a failed rewrite (i.e., the input was not accepted by the rule's FST)
  // and true otherwise.  Notably, a return value of true and an empty string
  // output is a deliberate rewrite to the empty string and not a failed match.
  // If pdt_parens_rule is not empty, then it the transducer associated with
  // "rule" is assumed to be a pushdown automaton, and that associated with
  // pdt_parens_rule is assumed to specify the parentheses.
  bool RewriteBytes(const string& rule, const string& input,
                    string* output,
                    const string& pdt_parens_rule = "") const;
  bool RewriteBytes(const string& rule, const Transducer& input,
                    string* output,
                    const string& pdt_parens_rule = "") const;
  bool Rewrite(const string& rule, const string& input,
               MutableTransducer* output,
               const string& pdt_parens_rule = "") const;
  bool Rewrite(const string& rule, const Transducer& input,
               MutableTransducer* output,
               const string& pdt_parens_rule = "") const;

  // This helper function (when given a potential string fst) takes the shortest
  // path, projects the output, and then removes epsilon arcs.
  static void StringifyFst(MutableTransducer* output);

  // ***************************************************************************
  // The following functions give access to, modify, or serialize internal data.

  // Returns the FST associated with the particular name.  This class returns
  // the actual pointer to the FST (or NULL if it is not found), so the caller
  // should not free the pointer.
  Transducer* GetFst(const string& name) const;

  // This function will write the created FSTs into an FST archive with the
  // provided filename.
  virtual void ExportFar(const string& filename) const = 0;

  // TODO(rws): This, and the pointer pdt_parens_, below, may not be needed
  // ultimately, since we have changed the strategy to using the EXPAND_FILTER
  // after each composition, thus removing the parens, and obviating the need
  // for a final pdt ShortestPath. So we only need to know the parens locally to
  // a particular composition, and there may be no need to know the parens
  // globally.
  const vector<pair<Label, Label> >* pdt_parens() const {
    return pdt_parens_;
  };

 protected:
  // Simple scoped mutex lock parametrized by mutex type.
  class ScopedMutexLock {
   public:
    explicit ScopedMutexLock(TheMutexType *mu) : mu_(mu) {
    }
    ~ScopedMutexLock() {
    }
   private:
    TheMutexType *mu_;
    DISALLOW_COPY_AND_ASSIGN(ScopedMutexLock);
  };

  AbstractGrmManager();

  // Loads up the FSTs given the supplied reader. Returns true on
  // success and false otherwise.
  template <typename FarReader>
  bool LoadArchive(FarReader *reader);

  // Gets the named FST, just like GetFst(), but this function doesn't lock
  // anything and is thread unsafe.
  Transducer* GetFstUnlocked(const string& name) const;

  // The list of FSTs held by this manager.  It's mutable as some of the
  // Rewrite() functions might make cosmetic changes to the underlying FSTs.
  mutable map<string, Transducer*> fsts_;
  mutable TheMutexType fsts_mutex_;

  // Storage for parens if we are dealing with a pushdown transducer. We need
  // this to be part of the class definition since we create if there is a named
  // pdt_parens_rule.
  vector<pair<Label, Label> >* pdt_parens_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AbstractGrmManager);
};

template <typename Arc, typename TheMutexType>
AbstractGrmManager<Arc, TheMutexType>::AbstractGrmManager() {
  pdt_parens_ = new vector<pair<Label, Label> >;
}

template <typename Arc, typename TheMutexType>
AbstractGrmManager<Arc, TheMutexType>::~AbstractGrmManager() {
  STLDeleteContainerPairSecondPointers(fsts_.begin(), fsts_.end());
  delete pdt_parens_;
}

template <typename Arc, typename TheMutexType>
template <typename FarReader>
bool AbstractGrmManager<Arc, TheMutexType>::LoadArchive(FarReader *reader) {
  STLDeleteContainerPairSecondPointers(fsts_.begin(), fsts_.end());
  fsts_.clear();
  for (reader->Reset(); !reader->Done(); reader->Next()) {
    const string& name = reader->GetKey();
    Transducer* fst = new MutableTransducer(reader->GetFst());
    fsts_[name] = fst;
  }
  return true;
}

template <typename Arc, typename TheMutexType>
typename AbstractGrmManager<Arc, TheMutexType>::Transducer*
AbstractGrmManager<Arc, TheMutexType>::GetFst(const string& name) const {
  ScopedMutexLock lock(&fsts_mutex_);
  return GetFstUnlocked(name);
}

template <typename Arc, typename TheMutexType>
typename AbstractGrmManager<Arc, TheMutexType>::Transducer*
AbstractGrmManager<Arc, TheMutexType>::GetFstUnlocked(const string& name) const {
  typename map<string, Transducer*>::const_iterator pos = fsts_.find(name);
  if (pos != fsts_.end()) {
    return pos->second;
  }
  return NULL;
}

template <typename Arc, typename TheMutexType>
bool AbstractGrmManager<Arc, TheMutexType>::RewriteBytes(
    const string& rule, const string& input,
    string* output,
    const string& pdt_parens_rule) const {
  fst::StringCompiler<Arc>
      string_compiler(fst::StringCompiler<Arc>::BYTE);
  MutableTransducer str_fst;
  if (!string_compiler(input, &str_fst))
    return false;
  return RewriteBytes(rule, str_fst, output, pdt_parens_rule);
}

template <typename Arc, typename TheMutexType>
bool AbstractGrmManager<Arc, TheMutexType>::RewriteBytes(
    const string& rule,
    const Transducer& input,
    string* output,
    const string& pdt_parens_rule) const {
  MutableTransducer output_fst;
  if (!Rewrite(rule, input, &output_fst, pdt_parens_rule))
    return false;

  StringifyFst(&output_fst);

  fst::StringPrinter<Arc> printer(fst::StringPrinter<Arc>::BYTE);
  return printer(output_fst, output);
}

template <typename Arc, typename TheMutexType>
bool AbstractGrmManager<Arc, TheMutexType>::Rewrite(
    const string& rule, const string& input,
    MutableTransducer* output,
    const string& pdt_parens_rule) const {
  fst::StringCompiler<Arc>
      string_compiler(fst::StringCompiler<Arc>::BYTE);
  MutableTransducer str_fst;
  if (!string_compiler(input, &str_fst))
    return false;

  return Rewrite(rule, str_fst, output, pdt_parens_rule);
}

template <typename Arc, typename TheMutexType>
bool AbstractGrmManager<Arc, TheMutexType>::Rewrite(
    const string& rule, const Transducer& input,
    MutableTransducer* output,
    const string& pdt_parens_rule) const {
  pdt_parens_->clear();

  Transducer* rule_fst = GetFstUnlocked(rule);
  if (!rule_fst) {
    LOG(ERROR) << "Rule " << rule << " not found.";
    return false;
  }

  Transducer* pdt_parens_fst = NULL;
  if (!pdt_parens_rule.empty()) {
    pdt_parens_fst = GetFstUnlocked(pdt_parens_rule);
    if (!pdt_parens_fst) {
      LOG(ERROR) << "PDT parentheses rule " << pdt_parens_rule << " not found.";
      return false;
    }
  }

  // If the rule FST isn't input-label sorted, do it now so we can compose with
  // all inputs.  This will also carry through to future rewrites.
  if (!rule_fst->Properties(fst::kILabelSorted, false)) {
    VLOG(1) << "Updating FST " << rule << " with input label sorted version.";

    MutableTransducer* sorted_rule_fst = new MutableTransducer(*rule_fst);
    fst::ArcSort(sorted_rule_fst, fst::ILabelCompare<Arc>());
    delete rule_fst;
    rule_fst = static_cast<Transducer*>(sorted_rule_fst);
    fsts_[rule] = rule_fst;
  }

  if (pdt_parens_fst) {
    MutableTransducer mut_pdt_parens_fst(*pdt_parens_fst);
    MakeParensPairVector(mut_pdt_parens_fst, pdt_parens_);
    // EXPAND_FILTER removes the parentheses, allowing for subsequent
    // application of PDTs. At the end (in StringifyFst() we use ordinary
    // ShortestPath().
    fst::PdtComposeOptions opts(true, fst::EXPAND_FILTER);
    fst::Compose(input, *rule_fst, *pdt_parens_, output, opts);
  } else {
    fst::ComposeOptions opts(true, fst::ALT_SEQUENCE_FILTER);
    fst::Compose(input, *rule_fst, output, opts);
  }

  return true;
}

template <typename Arc, typename TheMutexType>
void AbstractGrmManager<Arc, TheMutexType>::StringifyFst(
    MutableTransducer* fst) {
  MutableTransducer temp;
  fst::ShortestPath(*fst, &temp);
  fst::Project(&temp, fst::PROJECT_OUTPUT);
  fst::RmEpsilon(&temp);
  *fst = temp;
}

}  // namespace thrax

#endif  // NLP_GRM_LANGUAGE_ABSTRACT_GRM_MANAGER_H_
