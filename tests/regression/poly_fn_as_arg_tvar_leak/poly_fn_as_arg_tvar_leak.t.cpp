// A polymorphic function passed as an argument to itself.  Crane eta-expands
// it at the call site, so the eta-parameters have to be spelled with this
// site's type arguments rather than the callee's own type variables.

#include <poly_fn_as_arg_tvar_leak.h>

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
  assert(to_int(PolyFnAsArgTvarLeak::run) == 4);
  return 0;
}
