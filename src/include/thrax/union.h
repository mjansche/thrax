// Wrapper for the union function, which expands the first argument and unions
// into it (destructive-mode) or just uses UnionFst (delayed-mode).

#ifndef THRAX_UNION_H_
#define THRAX_UNION_H_

#include <iostream>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class Union : public BinaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Union() {}
  ~Union() final {}

 protected:
  Transducer* BinaryFstExecute(const Transducer& left, const Transducer& right,
                               const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "Union: Expected 2 arguments but got " << args.size()
                << std::endl;
      return nullptr;
    }
    if (FLAGS_save_symbols) {
      if (!CompatSymbols(left.InputSymbols(), right.InputSymbols())) {
        std::cout << "Union: input symbol table of 1st argument "
                  << "does not match input symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
      if (!CompatSymbols(left.OutputSymbols(), right.OutputSymbols())) {
        std::cout << "Union: output symbol table of 1st argument "
                  << "does not match output symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
    }
    MutableTransducer* mutable_left = new MutableTransducer(left);
    fst::Union(mutable_left, right);
    return mutable_left;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Union<Arc>);
};

template <typename Arc>
class UnionDelayed : public BinaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;

  UnionDelayed() {}
  ~UnionDelayed() final {}

 protected:
  Transducer* BinaryFstExecute(const Transducer& left, const Transducer& right,
                               const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "UnionDelayed: Expected 2 arguments but got " << args.size()
                << std::endl;
      return nullptr;
    }
    if (FLAGS_save_symbols) {
      if (!CompatSymbols(left.InputSymbols(), right.InputSymbols())) {
        std::cout << "UnionDelayed: input symbol table of 1st argument "
                  << "does not match input symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
      if (!CompatSymbols(left.OutputSymbols(), right.OutputSymbols())) {
        std::cout << "UnionDelayed: output symbol table of 1st argument "
                  << "does not match output symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
    }
    return new fst::UnionFst<Arc>(left, right);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(UnionDelayed<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_UNION_H_
