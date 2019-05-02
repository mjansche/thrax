#ifndef FST_UTIL_STRING_STRINGPRINT_H_
#define FST_UTIL_STRING_STRINGPRINT_H_

#include <string>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fst-decl.h>
#include <fst/string.h>

namespace fst {

template <class Arc>
bool PrintString(const Fst<Arc> &fst, string *str, StringTokenType ttype = BYTE,
                 const SymbolTable *syms = nullptr) {
  const StringPrinter<Arc> printer(ttype, syms);
  return printer(fst, str);
}

}  // namespace fst

#endif  // FST_UTIL_STRING_STRINGPRINT_H_
