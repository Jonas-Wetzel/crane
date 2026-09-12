// Crane bug: an enum emitted after the struct that uses it.
//
// [comparison] becomes a namespace-scope [enum class Comparison], but it is
// emitted below the struct whose member functions mention it:
//   error: unknown type name 'Comparison'

#include <enum_after_use.h>

#include <cassert>

int main() {
  assert(EnumAfterUse::ex.to_int() == 3);
  return 0;
}
