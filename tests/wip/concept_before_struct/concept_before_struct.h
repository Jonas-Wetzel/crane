#ifndef INCLUDED_CONCEPT_BEFORE_STRUCT
#define INCLUDED_CONCEPT_BEFORE_STRUCT

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

struct PeanoNat {
  static Nat add(const Nat &n, Nat m);
};

/// A class whose method returns a record type.  The concept is emitted at
/// namespace scope *before* the struct that defines the record, but its body
/// names ConceptBeforeStruct::mo.

template <typename I, typename A>
concept HasM = requires {
  { I::getm() } -> std::convertible_to<ConceptBeforeStruct::mo>;
};

struct ConceptBeforeStruct {
  struct mo {
    Nat mz;
    std::function<Nat(Nat, Nat)> mop;
  };

  struct hn {
    static mo getm() { return mo{Nat::o(), PeanoNat::add}; }
  };

  static_assert(HasM<hn, Nat>);
  static inline const Nat ex =
      hn::getm().mop(Nat::s(Nat::o()), Nat::s(Nat::s(Nat::o())));
};

#endif // INCLUDED_CONCEPT_BEFORE_STRUCT
