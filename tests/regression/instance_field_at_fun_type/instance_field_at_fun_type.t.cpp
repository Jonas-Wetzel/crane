// A class field whose instance is at a function type.
//
// [Instance df : D (nat -> nat) := { d := S }] keeps the arrow inside the
// value: the accessor stays nullary, as the concept requires, and returns a
// [std::function<Nat(Nat)>].

#include <instance_field_at_fun_type.h>

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
  assert(to_int(InstanceFieldAtFunType::run) == 2);
  return 0;
}
