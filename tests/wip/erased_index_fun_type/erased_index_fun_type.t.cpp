// Crane bug: an erased value in call position.
//
// [ty] is indexed by a Type that can be a function type, so [dflt] is declared
// as returning [std::any].  The call site then applies the result directly:
//   error: type 'std::any' does not provide a call operator

#include <erased_index_fun_type.h>

#include <cassert>

int main() {
  assert(ErasedIndexFunType::run.to_int() == 5);
  return 0;
}
