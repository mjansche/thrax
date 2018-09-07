// This function connects an FST, removing all unreachable states and paths.

#ifndef THRAX_CONNECT_H_
#define THRAX_CONNECT_H_

#include <iostream>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/connect.h>
#include <fst/fst.h>
#include <fst/vector-fst.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

namespace thrax {
namespace function {

template <typename Arc>
class Connect : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Connect() {}
  ~Connect() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() != 1) {
      std::cout << "Connect: Expected 1 argument but got " << args.size()
                << std::endl;
      return nullptr;
    }
    MutableTransducer* output = new MutableTransducer(fst);
    fst::Connect(output);
    return output;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Connect<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_CONNECT_H_
