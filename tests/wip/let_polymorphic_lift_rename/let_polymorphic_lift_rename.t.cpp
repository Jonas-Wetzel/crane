#include <let_polymorphic_lift_rename.h>
#include <cassert>

static unsigned nat_to_uint(const Nat &n) {
  unsigned acc = 0;
  const Nat *cur = &n;
  while (std::holds_alternative<Nat::S>(cur->v())) {
    ++acc;
    cur = std::get<Nat::S>(cur->v()).a0.get();
  }
  return acc;
}

int main() {
  assert(nat_to_uint(LetPolymorphicLiftRename::run) == 2);
  return 0;
}
