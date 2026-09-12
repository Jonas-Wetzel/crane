// Crane bug: an enum emitted after the struct that uses it.
//
// [comparison] becomes a namespace-scope [enum class Comparison], but it is
// emitted below the struct whose member functions mention it:
//   error: unknown type name 'Comparison'

#include <enum_after_use.h>

#include <cassert>

static int to_int(const Nat::nat &n) {
  int k = 0;
  const Nat::nat *p = &n;
  while (const auto *s = std::get_if<Nat::nat::S>(&p->v())) {
    ++k;
    p = s->a0.get();
  }
  return k;
}

int main() {
  assert(to_int(EnumAfterUse::ex) == 3);
  return 0;
}
