#ifndef THRAX_MAKE_PARENS_PAIR_VECTOR_H_
#define THRAX_MAKE_PARENS_PAIR_VECTOR_H_

#include <map>
#include <set>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>

// This is only needed for (M)PdtCompose and for grammar managers when they use
// (M)PDTs.

namespace thrax {

template <class Arc>
void MakeParensPairVector(
    const fst::Fst<Arc> &parens_transducer,
    std::vector<std::pair<typename Arc::Label, typename Arc::Label>> *parens) {
  using Label = typename Arc::Label;
  std::set<Label> seen_labels;
  for (fst::StateIterator<fst::Fst<Arc>> siter(parens_transducer);
       !siter.Done(); siter.Next()) {
    const auto state = siter.Value();
    for (fst::ArcIterator<fst::Fst<Arc>> aiter(parens_transducer,
                                                       state);
         !aiter.Done(); aiter.Next()) {
      const auto &arc = aiter.Value();
      if (!arc.ilabel && !arc.olabel) {
      } else if (!arc.ilabel) {
        LOG(WARNING) << "PdtCompose: left parenthesis corresponding to "
                     << arc.olabel << " is null";
      } else if (!arc.olabel) {
        LOG(WARNING) << "PdtCompose: right parenthesis corresponding to "
                     << arc.ilabel << " is null";
      } else {
        {
          const auto it = seen_labels.find(arc.ilabel);
          if (it != seen_labels.end()) {
            LOG(FATAL) << "PdtCompose: risky reuse of left paren "
                       << arc.ilabel;
          }
        }
        {
          const auto it = seen_labels.find(arc.olabel);
          if (it != seen_labels.end()) {
            LOG(FATAL) << "PdtCompose: risky reuse of right paren "
                       << arc.olabel;
          }
        }
        if (arc.ilabel == arc.olabel) {
          LOG(FATAL) << "PdtCompose: left parenthesis "
                     << arc.ilabel
                     << " is identical to right parenthesis "
                     << arc.olabel;
        }
        parens->emplace_back(arc.ilabel, arc.olabel);
      }
    }
  }
}

template <class Arc>
void MakeAssignmentsVector(
    const fst::Fst<Arc> &assignments_transducer,
    const std::vector<std::pair<typename Arc::Label, typename Arc::Label>>
        &parens,
    std::vector<typename Arc::Label> *assignments) {
  using Label = typename Arc::Label;
  std::map<Label, Label> assignment_map;
  for (fst::StateIterator<fst::Fst<Arc>> siter(assignments_transducer);
       !siter.Done(); siter.Next()) {
    const auto state = siter.Value();
    for (fst::ArcIterator<fst::Fst<Arc>> aiter(assignments_transducer,
                                                       state);
         !aiter.Done(); aiter.Next()) {
      const auto &arc = aiter.Value();
      if (!arc.ilabel && !arc.olabel) {
      } else if (!arc.ilabel) {
        LOG(WARNING) << "MPdtCompose: left parenthesis"
                     << "corresponding to assignment "
                     << arc.olabel << " is null";
      } else if (!arc.olabel) {
        LOG(WARNING) << "MPdtCompose: assignment corresponding"
                     << " to left parenthesis "
                     << arc.ilabel << " is null";
      } else {
        assignment_map[arc.ilabel] = arc.olabel;
      }
    }
  }
  for (const auto &paren : parens) {
    const auto it = assignment_map.find(paren.first);
    if (it == assignment_map.end()) {
      LOG(FATAL) << "MPdtCompose: left parenthesis " << paren.first
                 << " has no statck assignment";
    }
    assignments->emplace_back(it->second);
  }
}

}  // namespace thrax

#endif  // THRAX_MAKE_PARENS_PAIR_VECTOR_H_
