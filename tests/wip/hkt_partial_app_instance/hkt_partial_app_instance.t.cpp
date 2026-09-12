// Crane bug: an instance at a partially applied type constructor.
//
// [Fn (prod X)] needs a one-argument [F], but the instance emits
//   template <typename _A0, typename _A1> using F = std::pair<_A0, _A1>;
// at [prod]'s full arity, so [F<T>] does not resolve.

#include <hkt_partial_app_instance.h>

#include <cassert>

int main() {
  assert(HktPartialAppInstance::ex.first == true);
  assert(HktPartialAppInstance::ex.second.to_int() == 2);
  return 0;
}
