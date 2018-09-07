#ifndef THRAX_DATATYPE_H_
#define THRAX_DATATYPE_H_

#include <string>

#include <utility>
#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>
#include <thrax/compat/oneof.h>

namespace thrax {

class DataType {
 public:
  template <typename T>
  explicit DataType(T thing) : thing_(std::move(thing)) {}

  DataType* Copy() const {
    if (is<fst::Fst<fst::StdArc>*>()) {
      return new DataType(
          (*get<fst::Fst<fst::StdArc>*>())->Copy());
    } else if (is<fst::Fst<fst::LogArc>*>()) {
      return new DataType(
          (*get<fst::Fst<fst::LogArc>*>())->Copy());
    } else {
      DataType* retval = new DataType(thing_);
      return retval;
    }
  }

  ~DataType() {
    if (is<fst::Fst<fst::StdArc>*>())
      delete *get<fst::Fst<fst::StdArc>*>();
    else if (is<fst::Fst<fst::LogArc>*>())
      delete *get<fst::Fst<fst::LogArc>*>();
  }

  template <typename T>
  bool is() const {
    return thing_.is<T>();
  }

  template <typename T>
  const T* get() const {
    return thing_.get<T>();
  }

  template <typename T>
  T* get_mutable() {
    return thing_.get_mutable<T>();
  }

 private:
  using ThingType = thrax::Oneof<fst::Fst<fst::StdArc> *,
                                  fst::Fst<fst::LogArc> *,
                                  fst::Fst<fst::Log64Arc> *,
                                  fst::SymbolTable,
                                  string,
                                  int>;

  ThingType thing_;

  DISALLOW_COPY_AND_ASSIGN(DataType);
};

}  // namespace thrax

#endif  // THRAX_DATATYPE_H_
