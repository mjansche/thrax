// This function reverses an FST.

#ifndef THRAX_REVERSE_H_
#define THRAX_REVERSE_H_

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
class Reverse : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Reverse() {}
  ~Reverse() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() != 1) {
      std::cout << "Reverse: Expected 1 argument but got " << args.size()
                << std::endl;
      return nullptr;
    }
    MutableTransducer* output = new MutableTransducer();
    fst::Reverse(fst, output);
    return output;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Reverse<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_REVERSE_H_
