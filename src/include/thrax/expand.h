// This function takes an FST and expands it to a VectorFst. This function is
// cheap if the input is already an expanded VectorFst.

#ifndef THRAX_EXPAND_H_
#define THRAX_EXPAND_H_

#include <iostream>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

namespace thrax {
namespace function {

template <typename Arc>
class Expand : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Expand() {}
  ~Expand() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() != 1) {
      std::cout << "Expand: Expected 1 argument but got " << args.size()
                << std::endl;
      return nullptr;
    }
    return new MutableTransducer(fst);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Expand<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_EXPAND_H_
