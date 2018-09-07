#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <thrax/compat/utils.h>
#include <fst/arc.h>
#include <fst/fst.h>
#include <fst/string.h>
#include <fst/symbol-table.h>
#include <fst/vector-fst.h>
#include <thrax/grm-manager.h>
#include <../bin/utildefs.h>
#include <../bin/rewrite-tester-utils.h>
#include <thrax/symbols.h>
#ifdef HAVE_READLINE
using thrax::File;
using thrax::Open;
#include <readline/history.h>
#include <readline/readline.h>
#endif  // HAVE_READLINE

using fst::StdVectorFst;
using fst::StringCompiler;
using fst::SymbolTable;
using fst::VectorFst;
using thrax::FstToStrings;
using thrax::GetGeneratedSymbolTable;
using thrax::GrmManagerSpec;

DEFINE_string(far, "", "Path to the FAR.");
DEFINE_string(rules, "", "Names of the rewrite rules.");
DEFINE_string(input_mode, "byte", "Either \"byte\", \"utf8\", or the path to a "
              "symbol table for input parsing.");
DEFINE_string(output_mode, "byte", "Either \"byte\", \"utf8\", or the path to "
              "a symbol table for input parsing.");
DEFINE_string(history_file, ".rewrite-tester-history",
              "Location of history file");
DEFINE_int64(noutput, 1, "Maximum number of output strings for each input.");
DEFINE_bool(show_details, false, "Show the output of each individual rule when"
            " multiple rules are specified.");

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

bool RewriteTesterUtils::ReadInput(string* s) {
  if (!kHistoryFileInitialized) InitializeHistoryFile();
  char* input = readline("Input string: ");
  if (!input) return false;
  s->assign(input);
  add_history(input);
  free(input);
  write_history(FLAGS_history_file.c_str());
  return true;
}
#else   // HAVE_READLINE
bool RewriteTesterUtils::ReadInput(string* s) {
  std::cout << "Input string: ";
  return static_cast<bool>(getline(std::cin, *s));
}
#endif  // HAVE_READLINE

RewriteTesterUtils::RewriteTesterUtils() :
    compiler_(nullptr),
    byte_symtab_(nullptr),
    utf8_symtab_(nullptr),
    input_symtab_(nullptr),
    output_symtab_(nullptr)  { }

RewriteTesterUtils::~RewriteTesterUtils() {
  delete compiler_;
  delete input_symtab_;
  delete output_symtab_;
  delete byte_symtab_;
  delete utf8_symtab_;
}

void RewriteTesterUtils::Initialize() {
  CHECK(grm_.LoadArchive(FLAGS_far));
  rules_ = thrax::StringSplit(FLAGS_rules, ',');
  byte_symtab_ = nullptr;
  utf8_symtab_ = nullptr;
  if (rules_.empty()) LOG(FATAL) << "--rules must be specified";
  for (size_t i = 0; i < rules_.size(); ++i) {
    thrax::RuleTriple triple(rules_[i]);
    const auto *fst = grm_.GetFst(triple.main_rule);
    if (!fst) {
      LOG(FATAL) << "grm.GetFst() must be non nullptr for rule: "
                 << triple.main_rule;
    }
    StdVectorFst vfst(*fst);
    // If the input transducers in the FAR have symbol tables then we need to
    // add the appropriate symbol table(s) to the input strings, according to
    // the parse mode.
    if (vfst.InputSymbols()) {
      if (!byte_symtab_ &&
          vfst.InputSymbols()->Name() ==
          thrax::function::kByteSymbolTableName) {
        byte_symtab_ = vfst.InputSymbols()->Copy();
      } else if (!utf8_symtab_ &&
                 vfst.InputSymbols()->Name() ==
                 thrax::function::kUtf8SymbolTableName) {
        utf8_symtab_ = vfst.InputSymbols()->Copy();
      }
    }
    if (!triple.pdt_parens_rule.empty()) {
      fst = grm_.GetFst(triple.pdt_parens_rule);
      if (!fst) {
        LOG(FATAL) << "grm.GetFst() must be non nullptr for rule: "
                   << triple.pdt_parens_rule;
      }
    }
    if (!triple.mpdt_assignments_rule.empty()) {
      fst = grm_.GetFst(triple.mpdt_assignments_rule);
      if (!fst) {
        LOG(FATAL) << "grm.GetFst() must be non nullptr for rule: "
                   << triple.mpdt_assignments_rule;
      }
    }
  }

  generated_symtab_ = GetGeneratedSymbolTable(&grm_);
  if (FLAGS_input_mode == "byte") {
    compiler_ = new Compiler(fst::StringTokenType::BYTE);
  } else if (FLAGS_input_mode == "utf8") {
    compiler_ = new Compiler(fst::StringTokenType::UTF8);
  } else {
    input_symtab_ = SymbolTable::ReadText(FLAGS_input_mode);
    CHECK(input_symtab_)
        ;   // NOLINT
    compiler_ = new Compiler(fst::StringTokenType::SYMBOL, input_symtab_);
  }

  output_symtab_ = nullptr;
  if (FLAGS_output_mode == "byte") {
    type_ = BYTE;
  } else if (FLAGS_output_mode == "utf8") {
    type_ = UTF8;
  } else {
    type_ = SYMBOL;
    output_symtab_ = SymbolTable::ReadText(FLAGS_output_mode);
    CHECK(output_symtab_)
        ;  // NOLINT
  }
}

const string RewriteTesterUtils::ProcessInput(const string& input,
                                              bool prepend_output) {
  StdVectorFst input_fst, output_fst;
  if (!compiler_->operator()(input, &input_fst)) {
    return "Unable to parse input string.";
  }
  string return_val = "";
  // Set symbols for the input, if appropriate
  if (byte_symtab_ && type_ == BYTE) {
    input_fst.SetInputSymbols(byte_symtab_);
    input_fst.SetOutputSymbols(byte_symtab_);
  } else if (utf8_symtab_ && type_ == UTF8) {
    input_fst.SetInputSymbols(utf8_symtab_);
    input_fst.SetOutputSymbols(utf8_symtab_);
  } else if (input_symtab_ && type_ == SYMBOL) {
    input_fst.SetInputSymbols(input_symtab_);
    input_fst.SetOutputSymbols(input_symtab_);
  }

  bool succeeded = true;
  for (size_t i = 0; i < rules_.size(); ++i) {
    thrax::RuleTriple triple(rules_[i]);
    if (grm_.Rewrite(triple.main_rule, input_fst, &output_fst,
                     triple.pdt_parens_rule, triple.mpdt_assignments_rule)) {
      if (FLAGS_show_details && rules_.size() > 1) {
        std::vector<std::pair<string, float>> tmp;
        FstToStrings(output_fst, &tmp, generated_symtab_, type_,
                     output_symtab_, FLAGS_noutput);
        for (const auto& one_result : tmp) {
          return_val +=
              "output of rule[" +
              triple.main_rule +
              "] is: " +
              one_result.first +
              "\n";
        }
      }
      input_fst = output_fst;
    } else {
      succeeded = false;
      break;
    }
  }

  std::vector<std::pair<string, float> > strings;
  std::set<string> seen;
  if (succeeded && FstToStrings(output_fst, &strings,
                                generated_symtab_, type_,
                                output_symtab_, FLAGS_noutput)) {
    std::vector<std::pair<string, float> >::iterator itr = strings.begin();
    for (; itr != strings.end(); ++itr) {
      std::set<string>::iterator sx = seen.find(itr->first);
      if (sx != seen.end()) continue;
      if (prepend_output) {
        return_val += "Output string: " + itr->first;
      } else {
        return_val += itr->first;
      }
      if (FLAGS_noutput != 1 && itr->second != 0) {
        return_val += " <cost=" + std::to_string(itr->second) + ">";
      }
      seen.insert(itr->first);
      if (itr + 1 != strings.end()) return_val += "\n";
    }
    return return_val;
  } else {
    return "Rewrite failed.";
  }
}

// Run() for interactive mode.
void RewriteTesterUtils::Run() {
  string input;
  while (ReadInput(&input)) {
    std::cout << ProcessInput(input) << std::endl;
  }
}
