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
// Author: rws@google.com (Richard Sproat)
//
// Assert the equality of the first and second argument, issuing a warning if
// the two are not the same and returning the value of the first. More
// specifically, the first argument is assumed to be a transducer whose *output*
// value (unweighted shortest path of righthand projection) the user wishes to
// test. The second argument is assumed to be the intended value. Thus for
// example if I have a transducer "trans", I might test if applying "trans" to
// "foo" yields "bar" thus:
//
// equality = AssertEqual[foo @ trans, bar];
//
// This allows the user to check that the behavior is as intended without an
// external test file.

#ifndef THRAX_ASSERT_EQUAL_H_
#define THRAX_ASSERT_EQUAL_H_

#include <iostream>
#include <string>
#include <vector>
using std::vector;

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/arc-map.h>
#include <fst/determinize.h>
#include <fst/equivalent.h>
#include <fst/project.h>
#include <fst/rmepsilon.h>
#include <fst/shortest-path.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.

// TODO(rws,ttai): some day we should make this so that it doesn't return a
// value, but merely runs the assertion. That, however, would require changing
// the parser.

namespace thrax {
namespace function {

template <typename Arc>
class AssertEqual : public BinaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  AssertEqual() {}
  virtual ~AssertEqual() {}

 protected:
  virtual Transducer* BinaryFstExecute(const Transducer& left,
                                       const Transducer& right,
                                       const vector<DataType*>& args) {
    if (args.size() != 2) {
      cout << "AssertEqual: Expected 2 arguments but got "
           << args.size() << endl;
      return NULL;
    }

    if (FLAGS_save_symbols) {
      if (!CompatSymbols(left.InputSymbols(), right.InputSymbols())) {
        cout << "AssertEqual: input symbol table of 1st argument "
             << "does not match input symbol table of 2nd argument"
             << endl;
        return NULL;
      }
      if (!CompatSymbols(left.OutputSymbols(), right.OutputSymbols())) {
        cout << "AssertEqual: output symbol table of 1st argument "
             << "does not match output symbol table of 2nd argument"
             << endl;
        return NULL;
      }
    }

    MutableTransducer* mutable_left = new MutableTransducer(left);
    fst::Project(mutable_left, fst::PROJECT_OUTPUT);
    fst::RmEpsilon(mutable_left);
    MutableTransducer determinized_left;
    fst::Determinize(*mutable_left, &determinized_left);
    fst::ShortestPath(determinized_left, mutable_left);
    fst::ArcMap(mutable_left, fst::RmWeightMapper<Arc>());
    MutableTransducer mutable_right(right);
    fst::Project(&mutable_right, fst::PROJECT_OUTPUT);
    fst::RmEpsilon(&mutable_right);
    MutableTransducer determinized_right;
    fst::Determinize(mutable_right, &determinized_right);
    fst::ShortestPath(determinized_right, &mutable_right);
    fst::ArcMap(&mutable_right, fst::RmWeightMapper<Arc>());
    if (!fst::Equivalent(*mutable_left, mutable_right)) {
      cout << "Arguments to AssertEqual are not equivalent."
           << endl;
      delete mutable_left;
      return NULL;
    }
    return mutable_left;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(AssertEqual<Arc>);
};


}  // namespace function
}  // namespace thrax

#endif  // THRAX_ASSERT_EQUAL_H_
