#include "curried_tvar_instantiation.h"

/// A type variable instantiated at a curried function type is spelled
/// std::function<Nat(Nat,Nat)> (flattened) in one place and
/// std::function<std::function<Nat(Nat)>(Nat)> (curried) in the other, so the
/// declaration and the call site disagree.
Nat CurriedTvarInstantiation::ex(const Nat &x0_) {
  return apply_all<std::function<Nat(Nat)>>(
      List<std::function<Nat(std::function<Nat(Nat)>, Nat)>>::cons(
          [](std::function<Nat(Nat)> g) { return g; },
          List<std::function<Nat(std::function<Nat(Nat)>, Nat)>>::nil()),
      [](Nat x) { return Nat::s(x); })(x0_);
}
