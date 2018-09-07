#ifndef FST_UTIL_OPERATORS_SIGMA_STAR_H_
#define FST_UTIL_OPERATORS_SIGMA_STAR_H_

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/fstlib.h>

namespace fst {
namespace internal {

// Checks that a "sigma_star" FST is an unweighted cyclic acceptor.
template <class Arc>
bool CheckSigmaStarProperties(const Fst<Arc> &sigma_star,
                              const string &op_name) {
  static constexpr auto props = kAcceptor | kUnweighted;
  if (sigma_star.Properties(props, true) != props) {
    LOG(ERROR) << op_name << ": sigma_star must be a unweighted "
               << "acceptor";
    return false;
  }
  return true;
}

}  // namespace internal
}  // namespace fst

#endif  // FST_UTIL_OPERATORS_SIGMA_STAR_H_
