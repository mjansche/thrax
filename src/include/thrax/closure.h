// Provides (Kleene) closure operations for the provided FST. This expands the
// provided FST and then modifies it in place.

#ifndef THRAX_CLOSURE_H_
#define THRAX_CLOSURE_H_

#include <iostream>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>
#include <thrax/fst-node.h>
#include <thrax/datatype.h>
#include <thrax/function.h>

DECLARE_bool(save_symbols);  // From util/flags.cc.

namespace thrax {
namespace function {

template <typename Arc>
class Closure : public UnaryFstFunction<Arc> {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

  Closure() {}
  ~Closure() final {}

 protected:
  Transducer* UnaryFstExecute(const Transducer& fst,
                              const std::vector<DataType*>& args) final {
    if (args.size() < 2) {
      std::cout << "Closure: Expected 2 or 4 arguments" << std::endl;
      return nullptr;
    }
    if (!args[1]->is<int>()) {
      std::cout << "Closure: Expected int/enum for argument 2" << std::endl;
      return nullptr;
    }
    RepetitionFstNode::RepetitionFstNodeType type =
        static_cast<RepetitionFstNode::RepetitionFstNodeType>(
            *args[1]->get<int>());
    MutableTransducer* output = nullptr;
    switch (type) {
      case RepetitionFstNode::STAR: {
        if (args.size() != 2) {
          std::cout << "Closure: Expected 2 arguments for star closure"
                    << std::endl;
          return nullptr;
        }
        output = new MutableTransducer(fst);
        fst::Closure(output, fst::CLOSURE_STAR);
        break;
      }
      case RepetitionFstNode::PLUS: {
        if (args.size() != 2) {
          std::cout << "Closure: Expected 2 arguments for plus closure"
                    << std::endl;
          return nullptr;
        }
        output = new MutableTransducer(fst);
        fst::Closure(output, fst::CLOSURE_PLUS);
        break;
      }
      case RepetitionFstNode::QUESTION: {
        if (args.size() != 2) {
          std::cout << "Closure: Expected 2 arguments for optional closure"
                    << std::endl;
          return nullptr;
        }
        output = ConcatRange(fst, 0, 1);
        break;
      }
      case RepetitionFstNode::RANGE: {
        if (args.size() != 4) {
          std::cout << "Closure: Expected 4 arguments for range closure"
                    << std::endl;
          return nullptr;
        }
        for (int i = 2; i < 4; ++i) {
          if (!args[i]->is<int>()) {
            std::cout << "Closure: Expected int for argument " << i + 1
                      << " for "
                      << "range closure" << std::endl;
            return nullptr;
          }
        }
        int min = *args[2]->get<int>();
        int max = *args[3]->get<int>();
        output = ConcatRange(fst, min, max);
        break;
      }
      default: {
        std::cout << "Closure: No implementation for RepetitionFstNode type "
                  << type;
        return nullptr;
      }
    }
    return output;
  }

 private:
  // Returns a new FST that is the concatenation of min to max repetitions of
  // the provided input FST fst.
  MutableTransducer* ConcatRange(const Transducer& fst, int min, int max) {
    fst::VectorFst<Arc> empty_acceptor;
    int p = empty_acceptor.AddState();
    empty_acceptor.SetStart(p);
    empty_acceptor.SetFinal(p, Arc::Weight::One());
    // If we are saving symbols then we have to add the symbol tables of our
    // input fst to this new single state FST
    if (FLAGS_save_symbols) {
      empty_acceptor.SetInputSymbols(fst.InputSymbols());
      empty_acceptor.SetOutputSymbols(fst.OutputSymbols());
    }
    fst::VectorFst<Arc>* current = empty_acceptor.Copy();
    for (int i = max; i > 0; --i) {
      fst::Concat(fst, current);
      if (i > min) {
        fst::Concat(empty_acceptor, current);
        current->SetFinal(current->Start(), Arc::Weight::One());
      }
    }
    return current;
  }

  DISALLOW_COPY_AND_ASSIGN(Closure<Arc>);
};

}  // namespace function
}  // namespace thrax

#endif  // THRAX_CLOSURE_H_
