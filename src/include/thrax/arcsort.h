// Arc-sorts the single FST argument.

#ifndef THRAX_ARCSORT_H_
#define THRAX_ARCSORT_H_

#include <iostream>
#include <string>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/arcsort.h>
#include <fst/fst.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

namespace thrax {
namespace function {

template <typename Arc>
class ArcSort : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  ArcSort() {}
  ~ArcSort() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "ArcSort: Expected 2 arguments but received " << args.size()
                << std::endl;
      return nullptr;
    }
    if (!args[1]->is<string>()) {
      std::cout << "ArcSort: Expected string for argument 2" << std::endl;
      return nullptr;
    }
    const string& sort = *args[1]->get<string>();
    if (sort == "input") {
      return new fst::ArcSortFst<Arc, fst::ILabelCompare<Arc> >(
          fst, fst::ILabelCompare<Arc>());
    } else if (sort == "output") {
      return new fst::ArcSortFst<Arc, fst::OLabelCompare<Arc> >(
          fst, fst::OLabelCompare<Arc>());
    } else {
      std::cout << "ArcSort: Invalid sort parameter: " << sort
                << " (should be 'input' or 'output')" << std::endl;
      return nullptr;
    }
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(ArcSort<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_ARCSORT_H_
