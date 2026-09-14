#include <phantom_type_arg_never_emitted.h>
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
  assert(nat_to_uint(PhantomTypeArgNeverEmitted::run) == 3);
  return 0;
}
