// Crane bug: a type variable instantiated at a curried function type.
//
// The declaration spells it flattened, [std::function<Nat(Nat,Nat)>]; the call
// site spells it curried, [std::function<std::function<Nat(Nat)>(Nat)>].  The
// two do not convert.

#include <curried_tvar_instantiation.h>

#include <cassert>

int main() {
  assert(CurriedTvarInstantiation::run.to_int() == 2);
  return 0;
}
