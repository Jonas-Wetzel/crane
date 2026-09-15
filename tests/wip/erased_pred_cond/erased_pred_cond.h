#ifndef INCLUDED_ERASED_PRED_COND
#define INCLUDED_ERASED_PRED_COND

#include "crane_fn.h"
#include "small_vector.h"
#include <any>
#include <atomic>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <variant>

enum class Bool0;
template <typename A> struct Option;
template <typename A, typename B> struct Prod;
struct Nat;
enum class Bool0 { TRUE_, FALSE_ };

template <typename A> struct Option {
  // TYPES
  struct Some {
    A a;
  };

  struct None {};

  using variant_t = std::variant<Some, None>;

private:
  // DATA
  variant_t v_;

public:
  // CREATORS
  Option() {}

  explicit Option(Some _v) : v_(std::move(_v)) {}

  explicit Option(None _v) : v_(_v) {}

  template <typename _U> Option(const Option<_U> &_other) {
    if (std::holds_alternative<typename Option<_U>::Some>(_other.v())) {
      const auto &[a] = std::get<typename Option<_U>::Some>(_other.v());
      this->v_ = Some{[&]() -> A {
        if constexpr (std::is_same_v<_U, std::any>) {
          return crane_any_cast<A>(a);
        } else {
          return A(a);
        }
      }()};
    } else {
      this->v_ = None{};
    }
  }

  static Option<A> some(A a) { return Option<A>(Some{std::move(a)}); }

  static Option<A> none() { return Option<A>(None{}); }

  // MANIPULATORS
  inline variant_t &v_mut() { return v_; }

  // ACCESSORS
  const variant_t &v() const { return v_; }
};

template <typename A, typename B> struct Prod {
  // DATA
  A a0;
  B a1;

  // ACCESSORS
  Prod<A, B> clone() const { return {a0, a1}; }

  // CREATORS
  static Prod<A, B> pair(A a0, B a1) { return {std::move(a0), std::move(a1)}; }
};

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

  Bool0 even() const {
    const Nat *_loop_self = this;
    while (true) {
      auto &&_sv = *_loop_self;
      if (std::holds_alternative<typename Nat::O>(_sv.v())) {
        return Bool0::TRUE_;
      } else {
        const auto &[a0] = std::get<typename Nat::S>(_sv.v());
        auto &&_sv0 = *a0;
        if (std::holds_alternative<typename Nat::O>(_sv0.v())) {
          return Bool0::FALSE_;
        } else {
          const auto &[a00] = std::get<typename Nat::S>(_sv0.v());
          _loop_self = crane_raw(a00);
        }
      }
    }
  }
};

struct ErasedPredCond {
  /// A value-dependent semantic type: semty n mentions n, so Crane has no
  /// C++ spelling for it and erases it to std::any.  The pair it stands for
  /// holds a predicate and an action, exactly the shape
  /// Crane.Libraries.ParseALot's production_semty has.
  ///
  /// The interesting position is p x in the if: it is an application of an
  /// erased function, so its result arrives as std::any and the condition
  /// needs std::any_cast<bool>.  Crane instead casts it at the type of the
  /// if's *branches*, which does not compile.
  using semty = Prod<std::function<Bool0(Nat)>, std::function<Nat(Nat)>>;
  static Option<semty> table(const Nat &n);
  static Nat run(const Nat &n, Nat x);
  static inline const Nat sample =
      run(Nat::s(Nat::o()), Nat::s(Nat::s(Nat::s(Nat::s(Nat::o())))));
};

#endif // INCLUDED_ERASED_PRED_COND
