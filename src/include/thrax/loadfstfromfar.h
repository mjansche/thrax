// Loads an FST from a single FAR archive.

#ifndef THRAX_LOADFSTFROMFAR_H_
#define THRAX_LOADFSTFROMFAR_H_

#include <iostream>
#include <string>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <thrax/compat/utils.h>
#include <fst/extensions/far/far.h>
#include <fst/fst.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.
DECLARE_string(indir);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class LoadFstFromFar : public Function<Arc> {
 public:
  typedef fst::VectorFst<Arc> MutableTransducer;

  LoadFstFromFar() {}
  ~LoadFstFromFar() final {}

 protected:
  DataType* Execute(const std::vector<DataType*>& args) final {
    if (args.size() != 2) {
      std::cout << "LoadFstFromFar: Expected 2 arguments but got "
                << args.size() << std::endl;
      return nullptr;
    }
    if (!args[0]->is<string>()) {
      std::cout << "LoadFstFromFar: Expected string (path) for argument 1"
                << std::endl;
      return nullptr;
    }
    const string& far_file =
        JoinPath(FLAGS_indir, *args[0]->get<string>());

    if (!args[1]->is<string>()) {
      std::cout << "LoadFstFromFar: Expected string (FST name) for argument 2"
                << std::endl;
      return nullptr;
    }
    const string& fst_name = *args[1]->get<string>();
    VLOG(2) << "Loading FST " << fst_name << " from " << far_file;
    fst::FarReader<Arc>* reader(fst::FarReader<Arc>::Open(far_file));
    if (!reader) {
      std::cout << "LoadFstFromFar: Unable to open FAR: " << far_file
                << std::endl;
      return nullptr;
    }

    if (!reader->Find(fst_name)) {
      std::cout << "LoadFstFromFar: Unable to find FST: " << fst_name
                << std::endl;
      delete reader;
      return nullptr;
    }
    MutableTransducer* fst = new MutableTransducer(*(reader->GetFst()));
    delete reader;
    if (FLAGS_save_symbols) {
      if (!fst->InputSymbols()) {
        LOG(WARNING) << "LoadFstFromFar: FLAGS_save_symbols is set "
                     << "but fst has no input symbols";
      }
      if (!fst->OutputSymbols()) {
        LOG(WARNING) << "LoadFstFromFar: FLAGS_save_symbols is set "
                     << "but fst has no output symbols";
      }
    }
    return new DataType(fst);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(LoadFstFromFar<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_LOADFSTFROMFAR_H_
