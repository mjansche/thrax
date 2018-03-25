// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright 2005-2011 Google, Inc.
// Author: rws@google.com (Richard Sproat)
//
// Definitions needed by various utilities here.

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <../bin/utildefs.h>

#include <stack>
#include <string>
#include <utility>
using std::pair; using std::make_pair;
#include <vector>
using std::vector;

#include <fst/arc.h>
#include <fst/fst.h>
#include <fst/string.h>
#include <fst/symbol-table.h>
#include <fst/vector-fst.h>
#include <thrax/algo/paths.h>
#include <thrax/grm-manager.h>

DEFINE_string(field_separator, " ",
              "Field separator for strings of symbols from a symbol table.");

namespace thrax {

namespace {
inline bool AppendLabel(StdArc::Label label, TokenType type,
                        const SymbolTable* generated_symtab,
                        SymbolTable* symtab, string* path) {
  if (label != 0) {
    // Check first to see if this label is in the generated symbol set. Note
    // that this should not conflict with a user-provided symbol table since
    // the parser used by GrmCompiler doesn't generate extra labels if a
    // string is parsed using a user-provided symbol table.
    if (generated_symtab && !generated_symtab->Find(label).empty()) {
      string sym = generated_symtab->Find(label);
      *path += "[" + sym + "]";
    } else if (type == SYMBOL) {
      string sym = symtab->Find(label);
      if (sym == "") {
        LOG(ERROR) << "Missing symbol in symbol table for id: " << label;
        return false;
      }
      // For non-byte or utf8 symbols, one overwhelmingly wants these to be
      // space-separated.
      if (*path != "") {
        *path += FLAGS_field_separator;
      }
      *path += sym;
    } else if (type == BYTE) {
      path->push_back(label);
    } else if (type == UTF8) {
      string utf8_string;
      std::vector<int> labels;
      labels.push_back(label);
      if (!fst::LabelsToUTF8String(labels, &utf8_string)) {
        LOG(ERROR) << "LabelsToUTF8String: Bad code point: " << label;
        return false;
      }
      *path += utf8_string;
    }
  }
  return true;
}
}  // namespace

bool FstToStrings(const Transducer& fst,
                  std::vector<std::pair<string, float> >* strings,
                  const SymbolTable* generated_symtab,
                  TokenType type,
                  SymbolTable* symtab,
                  size_t n) {
  Transducer temp;
  fst::ShortestPath(fst, &temp, n);
  fst::Project(&temp, fst::PROJECT_OUTPUT);
  fst::RmEpsilon(&temp);
  if (temp.Start() == fst::kNoStateId) {
    return false;
  }
  for (fst::PathIterator<StdArc> iter(temp, /*check_acyclic*/ false);
       !iter.Done(); iter.Next()) {
    string path;
    for (auto label : iter.OValue()) {
      if (!AppendLabel(label, type, generated_symtab, symtab, &path)) {
        return false;
      }
    }
    strings->emplace_back(std::move(path), iter.Weight().Value());
  }
  return true;
}

const fst::SymbolTable*
GetGeneratedSymbolTable(GrmManagerSpec<StdArc>* grm) {
  const fst::Fst<StdArc>* symbolfst = grm->GetFst("*StringFstSymbolTable");
  if (symbolfst) {
    Transducer mutable_symbolfst(*symbolfst);
    return mutable_symbolfst.InputSymbols()->Copy();
  }
  return NULL;
}

}  // namespace thrax
