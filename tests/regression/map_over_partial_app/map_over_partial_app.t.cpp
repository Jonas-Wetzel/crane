// A partially applied curried function in a callback slot.
//
// [comp S] is eta-expanded for [List::map], which calls its argument with one
// argument, so the expansion has to be curried the way the slot is:
//   [](std::function<Nat(Nat)> _x0) { return [=](Nat _x1) -> Nat { ... }; }

#include <map_over_partial_app.h>

#include <cassert>
#include <variant>

/// [nat] is a unary inductive here, so counting the successors is the only way
/// to read it back.
static int to_int(const Nat &n) {
  int k = 0;
  const Nat *p = &n;
  while (const auto *s = std::get_if<Nat::S>(&p->v())) {
    ++k;
    p = s->a0.get();
  }
  return k;
}

int main() {
  assert(to_int(MapOverPartialApp::run) == 2);
  return 0;
}
