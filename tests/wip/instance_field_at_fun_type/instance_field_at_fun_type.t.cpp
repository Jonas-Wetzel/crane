// Crane bug: a class field whose instance is at a function type.
//
// [Instance df : D (nat -> nat) := { d := S }] is emitted as
//   struct df { static Nat d(Nat x) { return Nat::s(x); } };
// absorbing the argument, so [df] no longer satisfies [D<df, function<Nat(Nat)>>].

#include <instance_field_at_fun_type.h>

#include <cassert>

int main() {
  assert(InstanceFieldAtFunType::run.to_int() == 2);
  return 0;
}
