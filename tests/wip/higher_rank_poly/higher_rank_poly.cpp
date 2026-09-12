#include "higher_rank_poly.h"

/// A rank-2 argument: f is polymorphic and gets used at two different types.
/// Crane emits the two results without casting them back from std::any, and
/// emits a bogus body for the identity lambda passed in.
std::pair<Nat, bool>
HigherRankPoly::apply_id(std::function<std::any(std::any)> f) {
  return std::make_pair(f(Nat::s(Nat::o())), f(true));
}
