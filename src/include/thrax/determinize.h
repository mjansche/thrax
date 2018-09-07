// Determinize the single FST argument.

#ifndef THRAX_DETERMINIZE_H_
#define THRAX_DETERMINIZE_H_

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
class Determinize : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Determinize() {}
  ~Determinize() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() != 1) {
      std::cout << "Determinize: Expected 1 argument but got " << args.size()
                << std::endl;
      return nullptr;
    }
    MutableTransducer* output = new MutableTransducer();
    fst::Determinize(fst, output);
    return output;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Determinize<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_DETERMINIZE_H_
