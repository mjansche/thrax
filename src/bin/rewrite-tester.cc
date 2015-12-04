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
// Author: ttai@google.com (Terry Tai)
//         rws@google.com (Richard Sproat)
//
// Stand-alone binary to load up a FAR and rewrite some strings.

#include <iostream>
#include <string>
#include <vector>
using std::vector;

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <thrax/compat/utils.h>
#include <fst/arc.h>
#include <fst/fst.h>
#include <fst/string.h>
#include <fst/symbol-table.h>
#include <fst/vector-fst.h>
#include <thrax/grm-manager.h>
#include <../bin/utildefs.h>
#include <thrax/symbols.h>
#ifdef HAVE_READLINE
using thrax::File;
using thrax::Open;
#include <readline/history.h>
#include <readline/readline.h>
#endif  // HAVE_READLINE

using fst::StdArc;
using fst::StringCompiler;
using fst::SymbolTable;
using fst::VectorFst;
using thrax::FstToStrings;
using thrax::GetGeneratedSymbolTable;
using thrax::GrmManagerSpec;
using thrax::Split;
using thrax::VisitState;

typedef StringCompiler<StdArc> Compiler;

DEFINE_string(far, "", "Path to the FAR.");
DEFINE_string(rules, "", "Names of the rewrite rules.");
DEFINE_string(input_mode, "byte", "Either \"byte\", \"utf8\", or the path to a "
              "symbol table for input parsing.");
DEFINE_string(output_mode, "byte", "Either \"byte\", \"utf8\", or the path to "
              "a symbol table for input parsing.");
DEFINE_string(history_file, ".rewrite-tester-history",
              "Location of history file");
DEFINE_int64(noutput, 1, "Maximum number of output strings for each input.");

#ifdef HAVE_READLINE
using thrax::File;
using thrax::Open;
static bool kHistoryFileInitialized = false;

inline void InitializeHistoryFile() {
  // Create history file if it doesn't exist
  if (!Open(FLAGS_history_file, "r")) {
    File* fp = Open(FLAGS_history_file, "w");
    // Fail silently if we can't open it: just don't record history
    if (fp) fp->Close();
  }
  // This will fail silently if history_file doesn't open
  read_history(FLAGS_history_file.c_str());
  // Doesn't mean it succeeded: just means don't try this again:
  kHistoryFileInitialized = true;
}

bool ReadInput(string* s) {
  if (!kHistoryFileInitialized) InitializeHistoryFile();
  char* input = readline("Input string: ");
  if (!input) return false;
  s->assign(input);
  add_history(input);
  delete input;
  write_history(FLAGS_history_file.c_str());
  return true;
}
#else
bool ReadInput(string* s) {
  cout << "Input string: ";
  return static_cast<bool>(getline(cin, *s));
}
#endif  // HAVE_READLINE

int main(int argc, char** argv) {
  std::set_new_handler(FailedNewHandler);
  SET_FLAGS(argv[0], &argc, &argv, true);

  GrmManagerSpec<StdArc> grm;
  CHECK(grm.LoadArchive(FLAGS_far));

  vector<string> rules = Split(FLAGS_rules, ",");
  const fst::SymbolTable* byte_symtab = NULL;
  const fst::SymbolTable* utf8_symtab = NULL;
  if (rules.empty())
    LOG(FATAL) << "--rules must be specified";
  for (size_t i = 0; i < rules.size(); ++i) {
    vector<string> rule_bits =  Split(rules[i], "$");
    string pdt_parens_rule = "";
    if (rule_bits.size() == 2) pdt_parens_rule = rule_bits[1];
    fst::Fst<StdArc>* fst = grm.GetFst(rule_bits[0]);
    if (!fst) {
      LOG(FATAL) << "grm.GetFst() must be non NULL for rule: "
                 << rule_bits[0];
    }
    Transducer vfst(*fst);
    // If the input transducers in the FAR have symbol tables then we need to
    // add the appropriate symbol table(s) to the input strings, according to
    // the parse mode.
    if (vfst.InputSymbols()) {
      if (!byte_symtab &&
          vfst.InputSymbols()->Name() ==
          thrax::function::kByteSymbolTableName) {
        byte_symtab = vfst.InputSymbols()->Copy();
      } else if (!utf8_symtab &&
                 vfst.InputSymbols()->Name() ==
                 thrax::function::kUtf8SymbolTableName) {
        utf8_symtab = vfst.InputSymbols()->Copy();
      }
    }
    if (!pdt_parens_rule.empty()) {
      fst = grm.GetFst(pdt_parens_rule);
      if (!fst) {
        LOG(FATAL) << "grm.GetFst() must be non NULL for rule: "
                   << pdt_parens_rule;
      }
    }
  }

  const SymbolTable* generated_symtab = GetGeneratedSymbolTable(&grm);
  Compiler* compiler = NULL;
  SymbolTable* input_symtab = NULL;
  if (FLAGS_input_mode == "byte") {
    compiler = new Compiler(Compiler::BYTE);
  } else if (FLAGS_input_mode == "utf8") {
    compiler = new Compiler(Compiler::UTF8);
  } else {
    input_symtab = SymbolTable::ReadText(FLAGS_input_mode);
    CHECK(input_symtab)
        ;
    compiler = new Compiler(Compiler::SYMBOL, input_symtab);
  }

  TokenType type;
  SymbolTable* output_symtab = NULL;
  if (FLAGS_output_mode == "byte") {
    type = BYTE;
  } else if (FLAGS_output_mode == "utf8") {
    type = UTF8;
  } else {
    type = SYMBOL;
    output_symtab = SymbolTable::ReadText(FLAGS_output_mode);
    CHECK(output_symtab)
        ;
  }

  string input;
  while (ReadInput(&input)) {
    Transducer input_fst, output_fst;
    if (!compiler->operator()(input, &input_fst)) {
      cout << "Unable to parse input string." << endl;
      continue;
    }
    // Set symbols for the input, if appropriate
    if (byte_symtab && type == BYTE) {
      input_fst.SetInputSymbols(byte_symtab);
      input_fst.SetOutputSymbols(byte_symtab);
    } else if (utf8_symtab && type == UTF8) {
      input_fst.SetInputSymbols(utf8_symtab);
      input_fst.SetOutputSymbols(utf8_symtab);
    } else if (input_symtab && type == SYMBOL) {
      input_fst.SetInputSymbols(input_symtab);
      input_fst.SetOutputSymbols(input_symtab);
    }

    bool succeeded = true;
    for (size_t i = 0; i < rules.size(); ++i) {
      vector<string> rule_bits = Split(rules[i], "$");
      string pdt_parens_rule = "";
      if (rule_bits.size() == 2) pdt_parens_rule = rule_bits[1];
      if (grm.Rewrite(rule_bits[0], input_fst, &output_fst,
                      pdt_parens_rule)) {
        input_fst = output_fst;
      } else {
        succeeded = false;
        break;
      }
    }

    vector<pair<string, float> > strings;
    if (succeeded && FstToStrings(output_fst, &strings,
                                  generated_symtab, type,
                                  output_symtab, FLAGS_noutput)) {
      vector<pair<string, float> >::iterator itr = strings.begin();
      for (; itr != strings.end(); ++itr) {
        cout << "Output string: " << itr->first;
        if (FLAGS_noutput != 1 && itr->second != 0) {
          cout << " <cost=" << itr->second << ">";
        }
        cout << endl;
      }
    } else {
      cout << "Rewrite failed." << endl;
    }
  }

  delete compiler;
  delete input_symtab;
  delete output_symtab;
  delete byte_symtab;
  delete utf8_symtab;

  return 0;
}
