// Removes weights from arcs and final states (i.e. setting them to
// Weight::One()).

#ifndef THRAX_RMWEIGHT_H_
#define THRAX_RMWEIGHT_H_

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fst.h>
#include <fst/invert.h>
#include <fst/vector-fst.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

namespace thrax {
namespace function {

template <typename Arc>
class RmWeight : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;

  RmWeight() {}
  ~RmWeight() override {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) override {
    if (args.size() != 1) {
      std::cout << "Invert: Expected 1 argument but got " << args.size()
                << std::endl;
      return nullptr;
    }

    return new fst::ArcMapFst<Arc, Arc, fst::RmWeightMapper<Arc>>(
        fst, fst::RmWeightMapper<Arc>());
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(RmWeight<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_RMWEIGHT_H_
