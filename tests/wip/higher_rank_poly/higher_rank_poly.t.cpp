// Crane bug: a rank-2 polymorphic argument.
//
// [apply_id] uses its argument at [nat] and at [bool].  Crane returns both
// results straight out of [std::any] with no cast, and emits a body for the
// identity lambda that is copied from the outer return type:
//   crane_erase_fn([](const auto &x) { return crane_any_cast<std::pair<Nat, bool>>(x); })

#include <higher_rank_poly.h>

#include <cassert>

int main() {
  assert(HigherRankPoly::ex.first.to_int() == 1);
  assert(HigherRankPoly::ex.second == true);
  return 0;
}
