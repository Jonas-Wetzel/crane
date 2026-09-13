#ifndef INCLUDED_INSTANCE_METHOD_IGNORES_ARG
#define INCLUDED_INSTANCE_METHOD_IGNORES_ARG

#include <any>
#include <concepts>
#include <utility>

struct ic;
/// An instance method that discards its argument (fun _ => 1) loses the
/// argument on the way out: the method is emitted nullary while the concept
/// still requires the one-argument shape, so the instance fails the concept's
/// static_assert and its own body mentions the now-unbound template
/// parameter T1.  The same class with a method that actually matches on its
/// argument comes out right, so this is the erasure of an unused parameter,
/// not the class machinery.
template <typename I, typename A>
concept C = requires {
  { I::m(std::declval<A>()) } -> std::convertible_to<uint64_t>;
};

struct ic {
  static uint64_t m() { return UINT64_C(1); }
};

static_assert(C<ic, std::any>);

struct InstanceMethodIgnoresArg {
  static inline const uint64_t run = [](T1 _sat0) { return ic::m(_sat0); };
};

#endif // INCLUDED_INSTANCE_METHOD_IGNORES_ARG
