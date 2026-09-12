// Crane bug: a polymorphic function passed as an argument to itself.
//
// Crane eta-expands [twice] at the call site and spells the eta-parameters with
// the callee's type variable name, which is not in scope there:
//   error: use of undeclared identifier 'T1'

#include <poly_fn_as_arg_tvar_leak.h>

#include <cassert>

int main() {
  assert(PolyFnAsArgTvarLeak::run.to_int() == 4);
  return 0;
}
