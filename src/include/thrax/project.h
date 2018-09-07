// Projects the FST onto the input or output dimension.

#ifndef THRAX_PROJECT_H_
#define THRAX_PROJECT_H_

#include <iostream>
#include <string>
#include <vector>

#include <fst/fstlib.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

namespace thrax {
namespace function {

template <typename Arc>
class Project : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Project() {}
  ~Project() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "Project: Expected 2 arguments but received " << args.size()
                << std::endl;
      return nullptr;
    }
    if (!args[1]->is<string>()) {
      std::cout << "Project: Expected string for argument 2" << std::endl;
      return nullptr;
    }

    const string& project = *args[1]->get<string>();
    if (project == "input") {
      return new fst::ProjectFst<Arc>(fst, fst::PROJECT_INPUT);
    } else if (project == "output") {
      return new fst::ProjectFst<Arc>(fst, fst::PROJECT_OUTPUT);
    } else {
      std::cout << "Project: Invalid projection parameter: " << project
                << " (should be 'input' or 'output')" << std::endl;
      return nullptr;
    }
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Project<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_PROJECT_H_
