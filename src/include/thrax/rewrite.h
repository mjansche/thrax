// Wrapper for the rewrite function, where we have two FSTs and rewrite the
// the first into the second.  This function creates only on-the-fly
// transducers.

#ifndef THRAX_REWRITE_H_
#define THRAX_REWRITE_H_

#include <iostream>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>
#include <thrax/algo/crossproduct.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class Rewrite : public BinaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;

  Rewrite() {}
  ~Rewrite() final {}

 protected:
  Transducer* BinaryFstExecute(const Transducer& left, const Transducer& right,
                               const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "Rewrite: Expected 2 arguments but got " << args.size()
                << std::endl;
      return nullptr;
    }
    // If we keep the symbol tables and if either the input or the output is not
    // an acceptor, then the output symbols of the left and the output symbols
    // of the right must match.
    if (FLAGS_save_symbols &&
        (!left.Properties(fst::kAcceptor, true) ||
         !right.Properties(fst::kAcceptor, true))) {
      if (!CompatSymbols(left.OutputSymbols(), right.InputSymbols())) {
        std::cout << "Rewrite: output symbol table of 1st argument "
                  << "does not match input symbol table of 2nd argument "
                  << "and at least one is not an acceptor" << std::endl;
        return nullptr;
      }
    }
    auto *output = new fst::VectorFst<Arc>;
    fst::CrossProduct(left, right, output);
    return output;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Rewrite<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_REWRITE_H_
