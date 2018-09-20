// Reads in a file of strings to be compiled into an FST using a prefix tree.

#ifndef THRAX_STRINGFILE_H_
#define THRAX_STRINGFILE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <thrax/compat/utils.h>
#include <fst/fstlib.h>
#include <fst/string.h>
#include <thrax/algo/stripcomment.h>
#include <thrax/fst-node.h>
#include <thrax/datatype.h>
#include <thrax/function.h>
#include <thrax/symbols.h>
#include <thrax/algo/prefix_tree.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.
DECLARE_string(indir);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class StringFile : public Function<Arc> {
 public:
  typedef fst::VectorFst<Arc> MutableTransducer;
  typedef fst::PrefixTree<Arc> PrefixTree;
  typedef typename Arc::Label Label;

  StringFile() {}
  ~StringFile() final {}

 protected:
  DataType* Execute(const std::vector<DataType*>& args) final {
    if (args.size() < 1 || args.size() > 3) {
      std::cout << "StringFile: Expected 1-3 arguments but got " << args.size()
                << std::endl;
      return nullptr;
    }
    if (!args[0]->is<string>()) {
      std::cout << "StringFile: Expected string (file) for argument 1"
                << std::endl;
      return nullptr;
    }
    auto imode = fst::StringTokenType::BYTE;
    const fst::SymbolTable *isymbols = nullptr;
    if (args.size() == 1) {
      // If the StringFile call doesn't specify a parse mode, but if
      // FLAGS_save_symbols is set, we should set the symbol table to byte
      // mode.
      if (FLAGS_save_symbols) isymbols = GetByteSymbolTable();
    } else if (args.size() > 1) {
      if (args[1]->is<string>()) {
        if (*args[1]->get<string>() == "utf8") {
          imode = fst::StringTokenType::UTF8;
          if (FLAGS_save_symbols) isymbols = GetUtf8SymbolTable();
        } else {
          imode = fst::StringTokenType::BYTE;
          if (FLAGS_save_symbols) isymbols = GetByteSymbolTable();
        }
      } else if (args[1]->is<fst::SymbolTable>()) {
        isymbols = args[1]->get<fst::SymbolTable>();
        imode = fst::StringTokenType::SYMBOL;
      } else {
        std::cout << "StringFile: Invalid parse mode or symbol table "
                  << "for input symbols" << std::endl;
        return nullptr;
      }
    }
    auto omode = fst::StringTokenType::BYTE;
    // If this is an acceptor then the output symbols are whatever the input
    // symbols are.
    const fst::SymbolTable *osymbols = isymbols;
    if (args.size() > 2) {
      if (args[2]->is<string>()) {
        if (*args[2]->get<string>() == "utf8") {
          omode = fst::StringTokenType::UTF8;
          if (FLAGS_save_symbols) osymbols = GetUtf8SymbolTable();
        } else {
          omode = fst::StringTokenType::BYTE;
          if (FLAGS_save_symbols) osymbols = GetByteSymbolTable();
        }
      } else if (args[2]->is<fst::SymbolTable>()) {
        osymbols = args[2]->get<fst::SymbolTable>();
        omode = fst::StringTokenType::SYMBOL;
      } else {
        std::cout << "StringFile: Invalid parse mode or symbol table "
                  << "for output symbols" << std::endl;
        return nullptr;
      }
    }
    const auto filename = JoinPath(FLAGS_indir,
                                         *args[0]->get<string>());
    auto *fp = OpenOrDie(filename, "r");
    PrefixTree pt;
    string line;
    int linenum = 1;
    bool acceptor = true;
    for (InputBuffer ibuf(fp); ibuf.ReadLine(&line); ++linenum) {
      line = fst::StripCommentAndRemoveEscape(line);
      std::vector<string> words = thrax::StringSplit(line, '\t');
      size_t size = words.size();
      if (size == 0) {
        continue;
      }
      std::vector<Label> ilabels;
      std::vector<Label> olabels;
      if (size == 1) {
        ConvertStringToLabels(words[0], &ilabels, imode, isymbols);
        pt.Add(ilabels.begin(), ilabels.end(),
               ilabels.begin(), ilabels.end());
      } else if (size == 2) {
        ConvertStringToLabels(words[0], &ilabels, imode, isymbols);
        ConvertStringToLabels(words[1], &olabels, omode, osymbols);
        pt.Add(ilabels.begin(), ilabels.end(),
               olabels.begin(), olabels.end());
        acceptor = false;
      } else if (size == 3) {
        ConvertStringToLabels(words[0], &ilabels, imode, isymbols);
        ConvertStringToLabels(words[1], &olabels, omode, osymbols);
        std::istringstream strm(words[2]);
        typename Arc::Weight weight;
        if (!(strm >> weight))
          LOG(FATAL) << "Ill-formed weight: " << words[2] << ", line "
                     << linenum << " in " << filename;
        pt.Add(ilabels.begin(), ilabels.end(),
              olabels.begin(), olabels.end(),
              weight);
        acceptor = false;
      } else {
        std::cout << "StringFile: Possible ill-formed line " << linenum
                  << " in " << filename << std::endl;
      }
    }
    auto *fst = new MutableTransducer();
    pt.ToFst(fst);
    if (acceptor) {
      fst::Project(fst, fst::PROJECT_INPUT);
    } else {
      MutableTransducer copy(*fst);
      fst::Push<Arc, fst::REWEIGHT_TO_INITIAL>(copy, fst,
                                                       fst::kPushLabels);
    }
    fst::RmEpsilon(fst);
    fst::ArcSort(fst, arcsort_comparer_);
    if (FLAGS_save_symbols) {
      fst->SetInputSymbols(isymbols);
      fst->SetOutputSymbols(osymbols);
    }
    return new DataType(fst);
  }

 private:
  // Wrapper around internal functionality used by the OpenFst StringCompiler.
  bool ConvertStringToLabels(const string &str,
                             std::vector<Label> *labels,
                             fst::StringTokenType token_type,
                             const fst::SymbolTable* syms) const {
    return fst::internal::ConvertStringToLabels(
        str, token_type, syms, fst::kNoLabel, false, labels);
  }

  static const fst::ILabelCompare<Arc> arcsort_comparer_;
};

template <typename Arc>
const fst::ILabelCompare<Arc> StringFile<Arc>::arcsort_comparer_ =
    fst::ILabelCompare<Arc>();

}  // namespace function
}  // namespace thrax

#endif  // THRAX_STRINGFILE_H_
