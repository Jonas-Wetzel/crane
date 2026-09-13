#ifndef INCLUDED_EXISTENTIAL_FN_PROJECTION
#define INCLUDED_EXISTENTIAL_FN_PROJECTION

#include <any>
#include <functional>
#include <utility>
#include <variant>

template <typename A, typename P> struct SigT;

template <typename A, typename P> struct SigT {
  // DATA
  A x;
  P a1;

  // ACCESSORS
  SigT<A, P> clone() const { return {x, a1}; }

  // CREATORS
  static SigT<A, P> existt(A x, P a1) { return {std::move(x), std::move(a1)}; }

  P projT2() const {
    const auto &[x0, a1] = *this;
    return a1;
  }
};

struct ExistentialFnProjection {
  static inline const SigT<std::any, std::any> measurer =
      SigT<std::any, std::any>::existt(
          std::any(), std::function<uint64_t(std::any)>(
                          [](const std::any &_any_x) -> uint64_t {
                            uint64_t x = std::any_cast<uint64_t>(_any_x);
                            return (std::any_cast<uint64_t>(x) + UINT64_C(1));
                          }));
  static inline const uint64_t measured = measurer.projT2()(UINT64_C(4));
  static inline const SigT<std::any, std::pair<std::any, std::any>> tagged =
      SigT<std::any, std::pair<std::any, std::any>>::existt(
          std::any(),
          std::make_pair(std::any(UINT64_C(7)), std::any(UINT64_C(8))));

  static inline const uint64_t tag = tagged.projT2().second;
};

#endif // INCLUDED_EXISTENTIAL_FN_PROJECTION
