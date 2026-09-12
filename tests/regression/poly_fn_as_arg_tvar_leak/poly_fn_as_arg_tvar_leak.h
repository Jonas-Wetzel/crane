#ifndef INCLUDED_POLY_FN_AS_ARG_TVAR_LEAK
#define INCLUDED_POLY_FN_AS_ARG_TVAR_LEAK

#include "small_vector.h"
#include <atomic>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <variant>

struct Nat;

struct Nat {
  // TYPES
  struct O {};

  struct S {
    std::shared_ptr<Nat> a0;
  };

  using variant_t = std::variant<O, S>;

private:
  // DATA
  variant_t v_;

public:
  // CREATORS
  Nat() {}

  explicit Nat(O _v) : v_(_v) {}

  explicit Nat(S _v) : v_(std::move(_v)) {}

  static Nat o() { return Nat(O{}); }

  static Nat s(Nat a0) { return Nat(S{std::make_shared<Nat>(std::move(a0))}); }

  // MANIPULATORS
  ~Nat() {
    crane::small_vector<std::shared_ptr<Nat>> _stack = {};
    auto _drain = [&](variant_t &_v) {
      if (auto *_alt = std::get_if<S>(&_v)) {
        if (_alt->a0) {
          _stack.push_back(std::move(_alt->a0));
        }
      }
    };
    _drain(v_mut());
    while (!_stack.empty()) {
      auto _cur = std::move(_stack.back());
      _stack.pop_back();
      if (_cur.use_count() == 1) {
        std::atomic_thread_fence(std::memory_order_acquire);
        _drain(_cur->v_mut());
      }
    }
  }

  Nat(const Nat &) = default;
  Nat &operator=(const Nat &) = default;
  Nat(Nat &&) noexcept = default;
  Nat &operator=(Nat &&) noexcept = default;

  inline variant_t &v_mut() { return v_; }

  // ACCESSORS
  const variant_t &v() const { return v_; }
};

/// A polymorphic function passed as an argument to itself.  Crane eta-expands
/// it at the call site and spells the eta-parameters with the *callee's* type
/// variable name, which is not in scope there.
struct PolyFnAsArgTvarLeak {
  template <typename T1, typename F0>
    requires std::is_invocable_r_v<T1, F0 &, T1 &>
  static T1 twice(F0 &&f, const T1 &x) {
    return f(f(x));
  }

  static inline const Nat run = []() {
    return twice<std::function<Nat(Nat)>>(
        [](std::function<Nat(Nat)> _ec0) {
          return [=](Nat _ec1) mutable { return twice<Nat>(_ec0, _ec1); };
        },
        [](Nat x) { return Nat::s(x); })(Nat::o());
  }();
};

#endif // INCLUDED_POLY_FN_AS_ARG_TVAR_LEAK
