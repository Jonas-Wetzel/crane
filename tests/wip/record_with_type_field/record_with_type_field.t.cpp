// Crane bug: a record with a [Type] field used as data.
//
// The record is demoted from a concept to a struct with erased fields,
//   struct alg { std::function<std::any(std::any, std::any)> op; std::any unit_; };
// but its literal is still built from un-erased lambdas, so the initialiser has
// no viable conversion.

#include <record_with_type_field.h>

#include <cassert>

int main() {
  assert(RecordWithTypeField::ex.to_int() == 4);
  return 0;
}
