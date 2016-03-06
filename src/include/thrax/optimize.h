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
// Author: allauzen@google.com (Cyril Allauzen)
//         ttai@google.com (Terry Tai)
//
// This function does a cleaning up of an FST by determinizing and minimizing
// it.  If it's a transducer, we'll encode the arcs beforehand.
//
// This code is taken from the Optimize() function in
// nlp/fst_grammar/context_dependent_rewrite/context_dependent_rewrite.h.

#ifndef THRAX_OPTIMIZE_H_
#define THRAX_OPTIMIZE_H_

#include <iostream>
#include <vector>
using std::vector;

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

namespace thrax {
namespace function {

template <typename Arc>
class Optimize : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Optimize() {}
  virtual ~Optimize() {}

  // This function is public since other functions sometimes like to call on
  // this without having to go through the whole Function registration
  // rigmarole.
  static Transducer* ActuallyOptimize(const Transducer& fst) {
    MutableTransducer* output = new MutableTransducer(fst);

    if (output->Properties(fst::kNoEpsilons, false) != fst::kNoEpsilons)
      fst::RmEpsilon(output);
    fst::StateMap(output, fst::ArcSumMapper<Arc>(*output));
    if (!(Arc::Weight::Properties() & fst::kIdempotent))
      return output;
    if (output->Properties(fst::kAcceptor, false) != fst::kAcceptor) {
      // If the FST is not known to be an acceptor (i.e., may be a transducer),
      // we encode both labels and weights before determinization/minimization.
      fst::EncodeMapper<Arc> encoder(
          fst::kEncodeLabels | fst::kEncodeWeights, fst::ENCODE);
      fst::Encode(output, &encoder);
      MutableTransducer ifst(*output);
      fst::Determinize(ifst, output);
      fst::Minimize(output);
      fst::Decode(output, encoder);
    } else {
      // Otherwise, the FST is an acceptor. We now check whether the FST is
      // known to be deterministic.
      if (output->Properties(fst::kIDeterministic, false) !=
          fst::kIDeterministic) {
        if (!output->Properties(fst::kAcyclic | fst::kUnweighted,
                                false)) {
          // If the (possibly) nondeterministic acceptor is (possibly) weighted
          // and cyclic, we encode weights before determinization/minimization.
          fst::EncodeMapper<Arc> encoder(fst::kEncodeWeights,
                                             fst::ENCODE);
          fst::Encode(output, &encoder);
          MutableTransducer ifst(*output);
          fst::Determinize(ifst, output);
          fst::Minimize(output);
          fst::Decode(output, encoder);
        } else {
          // If the (possibly) nondeterministic acceptor is not weighted and
          // cyclic, we do not encode before determinization/minimization.
          MutableTransducer ifst(*output);
          fst::Determinize(ifst, output);
          fst::Minimize(output);
        }
      }
      else {
        // We directly minimize a deterministic acceptor; we do not need
        // to encode or determinize beforehand.
        fst::Minimize(output);
      }
    }
    fst::StateMap(output, fst::ArcSumMapper<Arc>(*output));
    return output;
  }

 protected:
  virtual Transducer* UnaryFstExecute(const Transducer& fst,
                                      const vector<DataType*>& args) {
    if (args.size() != 1) {
      std::cout << "Optimize: Expected 1 argument but got " << args.size()
                << std::endl;
      return NULL;
    }

    return ActuallyOptimize(fst);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Optimize<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_OPTIMIZE_H_
