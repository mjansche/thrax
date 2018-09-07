// LenientlyComposes two FSTs together.
//
// Requires three arguments, namely two transducers to be leniently composed,
// and a third FST representing the transitive closure of the universal alphabet
// (sigma star).

#ifndef THRAX_LENIENTLYCOMPOSE_H_
#define THRAX_LENIENTLYCOMPOSE_H_

#include <iostream>
#include <string>
#include <vector>

#include <fst/fstlib.h>
#include <thrax/algo/lenientlycompose.h>
#include <thrax/datatype.h>
#include <thrax/function.h>
#include <thrax/compat/stlfunctions.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class LenientlyCompose : public Function<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  LenientlyCompose() {}
  ~LenientlyCompose() final {}

 protected:
  DataType* Execute(const std::vector<DataType*>& args) final {
    if (args.size() != 3) {
      std::cout << "LenientyCompose: Expected 3 arguments but got "
                << args.size()
                << std::endl;
      return nullptr;
    }
    if (!args[0]->is<Transducer*>() ||
        !args[1]->is<Transducer*>() ||
        !args[2]->is<Transducer*>()) {
      std::cout << "LenientlyCompose: Arguments should be FSTs" << std::endl;
      return nullptr;
    }
    const Transducer* left = *args[0]->get<Transducer*>();
    const Transducer* right = *args[1]->get<Transducer*>();
    const Transducer* sigstar = *args[2]->get<Transducer*>();
    if (FLAGS_save_symbols) {
      if (!CompatSymbols(left->OutputSymbols(), right->InputSymbols())) {
        std::cout << "LenientlyCompose: output symbol table of 1st argument "
                  << "does not match input symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
      // LenientlyCompose computes the difference between sigstar and the input
      // projection of the first FST, so that means the same comparison as is
      // done in Difference must be done here.
      if (!CompatSymbols(sigstar->InputSymbols(), left->InputSymbols())) {
        std::cout << "LenientlyCompose: Input symbol of 1st argument "
                  << "does not match input symbol table of sigma star argument"
                  << std::endl;
        return nullptr;
      }
      if (!CompatSymbols(sigstar->OutputSymbols(),
                         left->InputSymbols() /* sic */)) {
        std::cout << "LenientlyCompose: Input symbol of 1st argument "
                  << "does not match output symbol table of sigma star argument"
                  << std::endl;
        return nullptr;
      }
    }
    MutableTransducer* output = new MutableTransducer();
    fst::LenientlyCompose(*left, *right, *sigstar, output);
    return new DataType(output);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(LenientlyCompose<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_LENIENTLYCOMPOSE_H_
