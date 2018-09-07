// Loads the appropriate symbol table given the string.

#ifndef THRAX_SYMBOLTABLE_H_
#define THRAX_SYMBOLTABLE_H_

#include <iostream>
#include <string>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <thrax/compat/utils.h>
#include <fst/symbol-table.h>
#include <thrax/datatype.h>
#include <thrax/function.h>
#include <thrax/compat/stlfunctions.h>

DECLARE_string(indir);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class SymbolTable : public Function<Arc> {
 public:
  SymbolTable() {}
  ~SymbolTable() final {}

 protected:
  DataType* Execute(const std::vector<DataType*>& args) final {
    if (args.size() != 1) {
      std::cout << "SymbolTable: Expected 1 argument but got " << args.size()
                << std::endl;
      return nullptr;
    }
    if (!args[0]->is<string>()) {
      std::cout << "SymbolTable: Expected string (path) for argument 1"
                << std::endl;
      return nullptr;
    }
    const string& file =
        JoinPath(FLAGS_indir, *args[0]->get<string>());
    VLOG(2) << "Loading symbol table: " << file;
    fst::SymbolTable* symtab(fst::SymbolTable::ReadText(file));
    if (!symtab) {
      std::cout << "SymbolTable: Unable to load symbol table file: " << file
                << std::endl;
      return nullptr;
    }
    DataType* output = new DataType(*symtab);
    delete symtab;
    return output;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(SymbolTable<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_SYMBOLTABLE_H_
