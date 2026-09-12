// Crane bug: a higher-kinded signature written as a Record rather than a Class.
//
// The record parameter is emitted as a plain [typename F] but its field type is
// spelled [F<std::any>], and the accessor treats the dictionary value as a
// scope: [f::template fmd<...>].

#include <hkt_record_dict.h>

#include <cassert>

int main() {
  assert(HktRecordDict::ex.has_value());
  assert(HktRecordDict::ex->to_int() == 2);
  return 0;
}
