// An instance at a partially applied type constructor.
//
// [Fn (prod X)] needs a one-argument [F], so the instance emits
//   template <typename _A0> using F = std::pair<T1, _A0>;
// keeping the argument the carrier already fixed.

#include <hkt_partial_app_instance.h>

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
  assert(HktPartialAppInstance::ex.first == true);
  assert(to_int(HktPartialAppInstance::ex.second) == 2);
  return 0;
}
