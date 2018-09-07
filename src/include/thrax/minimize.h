// This function minimizes the determinized input FST.

#ifndef THRAX_MINIMIZE_H_
#define THRAX_MINIMIZE_H_

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
class Minimize : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Minimize() {}
  ~Minimize() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() != 1) {
      std::cout << "Minimize: Expected 1 argument but got " << args.size()
                << std::endl;
      return nullptr;
    }
    MutableTransducer* output = new MutableTransducer(fst);
    fst::Minimize(output);
    return output;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Minimize<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_MINIMIZE_H_
