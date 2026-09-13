#ifndef INCLUDED_INSTANCE_FIELD_AT_FUN_TYPE
#define INCLUDED_INSTANCE_FIELD_AT_FUN_TYPE

#include "small_vector.h"
#include <atomic>
#include <concepts>
#include <functional>
#include <memory>
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

/// A class field whose instance is at a function type.  d := S is emitted as
/// static Nat d(Nat x), absorbing the argument, so the value no longer has the
/// field's type and the instance fails its own concept check.

template <typename I, typename A>
concept D = requires {
  { I::d() } -> std::convertible_to<A>;
};

struct InstanceFieldAtFunType {
  struct dn {
    static Nat d() { return Nat::o(); }
  };

  static_assert(D<dn, Nat>);

  struct df {
    static std::function<Nat(Nat)> d() {
      return [](Nat x) { return Nat::s(x); };
    }
  };

  static_assert(D<df, std::function<Nat(Nat)>>);
  static Nat ex(const Nat &x0_);
  static inline const Nat run = ex(Nat::s(Nat::o()));
};

#endif // INCLUDED_INSTANCE_FIELD_AT_FUN_TYPE
