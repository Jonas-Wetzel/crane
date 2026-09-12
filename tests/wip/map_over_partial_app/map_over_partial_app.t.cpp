// Crane bug: a partially applied curried function in a callback slot.
//
// [comp S] is eta-expanded into a two-parameter lambda
//   [](std::function<Nat(Nat)> _x0, Nat _x1) -> Nat
// and handed to [List::map], which calls its argument with one argument.

#include <map_over_partial_app.h>

#include <cassert>

int main() {
  assert(MapOverPartialApp::run.to_int() == 2);
  return 0;
}
