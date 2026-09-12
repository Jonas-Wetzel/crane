// Crane bug: two instance arguments passed in the wrong order.
//
// [compose_map] binds [F] then [G], but the call site passes [lstf, optf] where
// the declaration wants [optf, lstf], so the outer and inner functors are
// swapped and the argument no longer converts.

#include <hkt_instance_arg_order.h>

#include <cassert>

int main() {
  assert(HktInstanceArgOrder::ex.has_value());
  assert(HktInstanceArgOrder::ex->length() == 1);
  return 0;
}
