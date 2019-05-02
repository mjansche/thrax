#ifndef FST_UTIL_STRING_STRINGPRINT_H_
#define FST_UTIL_STRING_STRINGPRINT_H_

#include <sstream>
#include <string>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fst-decl.h>
#include <fst/string.h>

namespace fst {
namespace internal {

constexpr char kSymbolSeparator[] = " ";

// Collects output labels from a string FST. This is similar to the logic of
// the FST lib's string.h, but in function form.
template <class Arc>
bool FstToOutputLabels(const Fst<Arc> &fst,
                       std::vector<typename Arc::Label> *labels) {
  using Weight = typename Arc::Weight;
  labels->clear();
  auto s = fst.Start();
  if (s == kNoStateId) {
    LOG(ERROR) << "FstToOutputLabels: Invalid start state";
    return false;
  }
  while (fst.Final(s) == Weight::Zero()) {
    ArcIterator<Fst<Arc>> aiter(fst, s);
    if (aiter.Done()) {
      LOG(ERROR) << "FstToOutputLabels: String FST does not reach final state";
      return false;
    }
    const auto &arc = aiter.Value();
    labels->push_back(arc.olabel);
    s = arc.nextstate;
    if (s == kNoStateId) {
      LOG(ERROR) << "FstToOutputLabels: Transition to invalid state";
      return false;
    }
    aiter.Next();
    if (!aiter.Done()) {
      LOG(ERROR) << "FstToOutputLabels: State with multiple arcs";
      return false;
    }
  }
  return true;
}

// Prints a single symbol from a symbol table to a output stream.
template <class Label>
bool PrintSymbol(Label label, const SymbolTable &syms, std::ostream &ostrm) {
  const auto &symbol = syms.Find(label);
  if (symbol.empty()) {
    LOG(ERROR) << "PrintSymbol: Label " << label << " is not mapped to any "
               << "textual symbol in symbol table " << syms.Name();
    return false;
  }
  ostrm << symbol;
  return true;
}

// Writes an iterable of Labels into a string according to the user-specified
// StringTokenType. This is similar to the logic in the FST lib's string.h,
// but takes a lower-level input (a vector of labels) and avoids some redundant
// checks.
template <class Label>
bool LabelsToString(const std::vector<Label> &labels, string *str,
                    StringTokenType ttype = BYTE,
                    const SymbolTable *syms = nullptr) {
  str->clear();
  switch (ttype) {
    case BYTE: {
      return LabelsToByteString(labels, str);
    }
    case UTF8: {
      return LabelsToUTF8String(labels, str);
    }
    case SYMBOL: {
      std::stringstream sstrm;
      auto it = labels.begin();
      if (it == labels.end()) return true;
      if (!PrintSymbol(*it, *syms, sstrm)) return false;
      for (++it; it != labels.end(); ++it) {
        sstrm << kSymbolSeparator;
        if (!PrintSymbol(*it, *syms, sstrm)) return false;
      }
      *str = sstrm.str();
      return true;
    }
  }
  return false;
}

}  // namespace internal

template <class Arc>
bool PrintString(const Fst<Arc> &fst, string *str, StringTokenType ttype = BYTE,
                 const SymbolTable *syms = nullptr) {
  using Label = typename Arc::Label;
  // Collects labels.
  std::vector<Label> labels;
  if (!internal::FstToOutputLabels(fst, &labels)) return false;
  // If the FST has its own output symbol table and symbol table use is
  // requested, we use it unless syms is specified.
  if (ttype == SYMBOL && !syms && !(syms = fst.OutputSymbols())) {
    LOG(ERROR) << "PrintString:: Symbol table use requested but none found";
    return false;
  }
  // Writes labels or symbols to string.
  if (!internal::LabelsToString(labels, str, ttype, syms)) return false;
  return true;
}

}  // namespace fst

#endif  // FST_UTIL_STRING_STRINGPRINT_H_
