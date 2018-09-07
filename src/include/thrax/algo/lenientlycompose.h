#ifndef FST_UTIL_OPERATORS_LENIENTLYCOMPOSE_H_
#define FST_UTIL_OPERATORS_LENIENTLYCOMPOSE_H_

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>
#include <thrax/algo/sigma_star.h>

// Lenient FST composition, after:
//
// L. Karttunen. 1998. The proper treatment of Optimality Theory in
// computational phonology. In Proc. FSMNLP, pages 1-12.

namespace fst {
namespace internal {

// The priority union of two FSTs Q, R consists of the union of the relations in
// Q and R (as in vanilla union) subject to the constraint that the relations in
// Q have "priority". Imagine that:
//
//     Q(a) -> b
//     R(a) -> c
//
// Then, if U is the vanilla union of Q and R, U(a) -> {b, c}. But if P is the
// priority union of Q and R, U(a) -> b (not c).
//
// Here we compute the priority union of two FSTs with respect to sigma_star, a
// cyclic, unweighted acceptor representing the universal language. Then
// priority union is simply:
//
// func PriorityUnion[Q, R, sigma_star] {
//   input = Determinize[RmEpsilon[Project[Q, 'input']]];
//   return Q | ((sigma_star - input) @ R);
// }
template <class Arc>
void PriorityUnion(MutableFst<Arc> *fst1, const Fst<Arc> &fst2,
                   const Fst<Arc> &sigma_star) {
  if (!CheckSigmaStarProperties(sigma_star, "PriorityUnion")) {
    fst1->SetProperties(kError, kError);
    return;
  }
  const ProjectFst<Arc> project(*fst1, PROJECT_INPUT);
  const RmEpsilonFst<Arc> rmepsilon(project);
  const DeterminizeFst<Arc> determinize(rmepsilon);
  const DifferenceFst<Arc> difference(sigma_star, determinize);
  // We bail out if the contract for Difference was not satisfied.
  if (difference.Properties(kError, true) == kError) {
    fst1->SetProperties(kError, kError);
    return;
  }
  const ComposeFst<Arc> compose(difference, fst2);
  Union(fst1, compose);
}

}  // namespace internal

// Lenient composition of two FSTs X, Y is simply the priority union (with
// respect to some universal language) of the composition of X and Y with X.
// Thus it is a composition which gives priority to X @ Y, falling back upon X.
// Then lenient composition is simply:
//
// func LenientlyCompose[X, Y, sigma_star] {
//   return PriorityUnion[X @ Y, X, sigma_star];
// }
template <class Arc>
void LenientlyCompose(const Fst<Arc> &ifst1, const Fst<Arc> &ifst2,
                      const Fst<Arc> &sigma_star, MutableFst<Arc> *ofst,
                      const ComposeOptions &opts = ComposeOptions()) {
  Compose(ifst1, ifst2, ofst, opts);
  internal::PriorityUnion(ofst, ifst1, sigma_star);
}

}  // namespace fst

#endif  // FST_UTIL_OPERATORS_LENIENTLYCOMPOSE_H_
