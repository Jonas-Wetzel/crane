// A type variable instantiated at a curried function type.
//
// The list element type [A -> A] at [A = nat -> nat] must be spelled the way
// the declaration writes it, [std::function<F(F)>], at every position: the
// cons cell, its tail, and the call's template argument.

#include <curried_tvar_instantiation.h>

#include <cassert>

static int to_int(Nat n) {
  int i = 0;
  while (std::holds_alternative<Nat::S>(n.v())) {
    n = *std::get<Nat::S>(n.v()).a0;
    ++i;
  }
  return i;
}

int main() {
  assert(to_int(CurriedTvarInstantiation::run) == 2);
  return 0;
}
