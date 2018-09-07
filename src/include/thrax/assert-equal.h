// Assert the equality of the first and second argument, issuing a warning if
// the two are not the same and returning the value of the first. More
// specifically, the first argument is assumed to be a transducer whose *output*
// value (unweighted shortest path of righthand projection) the user wishes to
// test. The second argument is assumed to be the intended value. Thus for
// example if I have a transducer "trans", I might test if applying "trans" to
// "foo" yields "bar" thus:
//
// equality = AssertEqual[foo @ trans, bar];
//
// This allows the user to check that the behavior is as intended without an
// external test file.

#ifndef THRAX_ASSERT_EQUAL_H_
#define THRAX_ASSERT_EQUAL_H_

#include <iostream>
#include <string>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/arc-map.h>
#include <fst/determinize.h>
#include <fst/intersect.h>
#include <fst/project.h>
#include <fst/prune.h>
#include <fst/rmepsilon.h>
#include <fst/string.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.

// TODO(rws,ttai): some day we should make this so that it doesn't return a
// value, but merely runs the assertion. That, however, would require changing
// the parser.

namespace thrax {
namespace function {

template <typename Arc>
class AssertEqual : public BinaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  AssertEqual() {}
  ~AssertEqual() final {}

 protected:
  Transducer* BinaryFstExecute(const Transducer& left, const Transducer& right,
                               const std::vector<DataType*>& args) final {
    if (args.size() < 2 || args.size() > 3) {
      std::cout << "AssertEqual: Expected 2 or 3 arguments but got "
                << args.size() << std::endl;
      return nullptr;
    }
    auto mode = fst::StringTokenType::BYTE;
    const fst::SymbolTable* symbols = nullptr;
    if (args.size() > 2) {
      if (args[2]->is<string>()) {
        if (*args[2]->get<string>() == "utf8") {
          mode = fst::StringTokenType::UTF8;
        } else {
          mode = fst::StringTokenType::BYTE;
        }
      } else if (args[2]->is<fst::SymbolTable>()) {
        symbols = args[2]->get<fst::SymbolTable>();
        mode = fst::StringTokenType::SYMBOL;
      } else {
        std::cout << "AssertEqual: Invalid parse mode or symbol table "
                  << "for symbols" << std::endl;
        return nullptr;
      }
    }
    if (FLAGS_save_symbols) {
      if (!CompatSymbols(left.InputSymbols(), right.InputSymbols())) {
        std::cout << "AssertEqual: input symbol table of 1st argument "
                  << "does not match input symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
      if (!CompatSymbols(left.OutputSymbols(), right.OutputSymbols())) {
        std::cout << "AssertEqual: output symbol table of 1st argument "
                  << "does not match output symbol table of 2nd argument"
                  << std::endl;
        return nullptr;
      }
    }
    auto *mutable_left = new MutableTransducer(left);
    fst::Project(mutable_left, fst::PROJECT_OUTPUT);
    fst::RmEpsilon(mutable_left);
    MutableTransducer determinized_left;
    fst::Determinize(*mutable_left, &determinized_left);
    fst::Prune(determinized_left, mutable_left, Arc::Weight::One());
    fst::ArcMap(mutable_left, fst::RmWeightMapper<Arc>());
    MutableTransducer mutable_right(right);
    fst::Project(&mutable_right, fst::PROJECT_OUTPUT);
    fst::RmEpsilon(&mutable_right);
    MutableTransducer determinized_right;
    fst::Determinize(mutable_right, &determinized_right);
    fst::Prune(determinized_right, &mutable_right, Arc::Weight::One());
    fst::ArcMap(&mutable_right, fst::RmWeightMapper<Arc>());
    MutableTransducer intersection;
    fst::Intersect(*mutable_left, mutable_right, &intersection);
    // If both mutable_left and mutable_right have zero states, then they count
    // as equivalent. We only consider the intersection a failure if at least
    // one of them has some states.
    if ((mutable_left->NumStates() != 0 || mutable_right.NumStates() != 0) &&
        intersection.Start() == fst::kNoStateId) {
      // Print strings for debug message.
      // TODO(rws): This is still going to fail to produce useful output for
      // extended labels since those will have labels outside the range of BYTE
      // or UTF8
      fst::RmEpsilon(mutable_left);
      fst::RmEpsilon(&mutable_right);
      string lstring;
      if (mutable_left->Start() == fst::kNoStateId) {
        lstring = "nullptr";
      } else {
        string content;
        AssertEqual<Arc>::CoerceToString(*mutable_left, &content, symbols);
        lstring = "\"" + content + "\"";
      }
      string rstring;
      if (mutable_right.Start() == fst::kNoStateId) {
        rstring = "nullptr";
      } else {
        string content;
        AssertEqual<Arc>::CoerceToString(mutable_right, &content, symbols);
        rstring = "\"" + content + "\"";
      }
      std::cout << "Arguments to AssertEqual are not equivalent:\n"
                << "  expect: " << rstring << "\n"
                << "     got: " << lstring << "\n"
                << std::endl;
      delete mutable_left;
      return nullptr;
    }
    return mutable_left;
  }

 private:
  // Coerces an FST to a string by calling ShortestPath, TopSort, and the
  // string printer. This is necessary so we have exactly one string to
  // to show in the debug message.
  static void CoerceToString(const MutableTransducer &fst, string *str,
                             const fst::SymbolTable *symbols = nullptr) {
    fst::StringPrinter<Arc> printer(fst::StringTokenType::BYTE,
                                        symbols);
    if (fst.Properties(fst::kString, true) == fst::kString) {
      printer(fst, str);
    } else {
      MutableTransducer string_fst(fst);
      fst::ShortestPath(fst, &string_fst);
      fst::TopSort(&string_fst);
      printer(string_fst, str);
    }
  }
};


}  // namespace function
}  // namespace thrax

#endif  // THRAX_ASSERT_EQUAL_H_
