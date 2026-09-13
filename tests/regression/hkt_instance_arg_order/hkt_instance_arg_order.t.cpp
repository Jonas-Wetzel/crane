// Two instance arguments in one signature.
//
// [compose_map] binds [Fn F] then [Fn G]; the declaration, the body and the
// call site all have to number them the same way, or the outer and inner
// functors are swapped.

#include <hkt_instance_arg_order.h>

#include <cassert>
#include <variant>

int main() {
  assert(HktInstanceArgOrder::ex.has_value());
  const auto &cell = std::get<List<Nat>::Cons>(HktInstanceArgOrder::ex->v());
  // [S] mapped over [1 :: nil] under [option . list].
  assert(std::holds_alternative<Nat::S>(cell.a.v()));
  assert(std::holds_alternative<List<Nat>::Nil>(cell.l->v()));
  return 0;
}
