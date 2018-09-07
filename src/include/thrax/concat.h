// Wrapper for the concatenation function, which expands the second argument and
// concatenates into there (destructive-mode) or just uses ConcatFst
// (delayed-mode).

#ifndef THRAX_CONCAT_H_
#define THRAX_CONCAT_H_

#include <iostream>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/concat.h>
#include <fst/fst.h>
#include <fst/symbol-table.h>
#include <fst/vector-fst.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class Concat : public BinaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Concat() {}
  ~Concat() final {}

 protected:
  Transducer* BinaryFstExecute(const Transducer& left, const Transducer& right,
                               const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "Concat: Expected 2 arguments but got " << args.size()
                << std::endl;
      return nullptr;
    }
    if (FLAGS_save_symbols) {
      if (!CompatSymbols(left.InputSymbols(), right.InputSymbols())) {
        std::cout << "Concat: input symbol table of 1st argument "
                  << "does not match input symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
      if (!CompatSymbols(left.OutputSymbols(), right.OutputSymbols())) {
        std::cout << "Concat: output symbol table of 1st argument "
                  << "does not match output symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
    }
    MutableTransducer* mutable_right = new MutableTransducer(right);
    fst::Concat(left, mutable_right);
    return mutable_right;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Concat<Arc>);
};

template <typename Arc>
class ConcatDelayed : public BinaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;

  ConcatDelayed() {}
  virtual ~ConcatDelayed() {}

 protected:
  Transducer* BinaryFstExecute(const Transducer& left, const Transducer& right,
                               const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "ConcatDelayed: Expected 2 arguments but got " << args.size()
                << std::endl;
      return nullptr;
    }
    if (FLAGS_save_symbols) {
      if (!CompatSymbols(left.InputSymbols(), right.InputSymbols())) {
        std::cout << "ConcatDelayed: input symbol table of 1st argument "
                  << "does not match input symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
      if (!CompatSymbols(left.OutputSymbols(), right.OutputSymbols())) {
        std::cout << "ConcatDelayed: output symbol table of 1st argument "
                  << "does not match output symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
    }
    return new fst::ConcatFst<Arc>(left, right);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(ConcatDelayed<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_CONCAT_H_
