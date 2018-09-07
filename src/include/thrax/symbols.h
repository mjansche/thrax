// Builds the symbol tables needed for byte and utf8 if FLAGS_save_symbols is
// set

#ifndef THRAX_SYMBOLS_H_
#define THRAX_SYMBOLS_H_

#include <string>

#include <fst/fstlib.h>

namespace thrax {
namespace function {

// Defined in loader.cc
fst::SymbolTable* GetByteSymbolTable();
fst::SymbolTable* GetUtf8SymbolTable();
void AddToByteSymbolTable(string symbol, int64 label);
void AddToUtf8SymbolTable(string symbol, int64 label);

static const char kByteSymbolTableName[] = "**Byte symbols";
static const char kUtf8SymbolTableName[] = "**UTF8 symbols";

class SymbolTableBuilder {
 public:
  SymbolTableBuilder();
  ~SymbolTableBuilder();
  fst::SymbolTable* GetByteSymbolTable();
  fst::SymbolTable* GetUtf8SymbolTable();
  void AddToByteSymbolTable(string symbol, int64 label);
  void AddToUtf8SymbolTable(string symbol, int64 label);

 private:
  void GenerateByteSymbolTable();
  inline void GenerateUtf8SymbolTable();

  fst::Mutex map_mutex_;
  fst::SymbolTable* byte_symbols_;
  fst::SymbolTable* utf8_symbols_;
  DISALLOW_COPY_AND_ASSIGN(SymbolTableBuilder);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_SYMBOLS_H_
