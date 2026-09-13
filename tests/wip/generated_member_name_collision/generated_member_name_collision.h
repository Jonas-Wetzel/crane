#ifndef INCLUDED_GENERATED_MEMBER_NAME_COLLISION
#define INCLUDED_GENERATED_MEMBER_NAME_COLLISION

#include <type_traits>
#include <variant>

struct GeneratedMemberNameCollision {
  struct boxed {
    // DATA
    uint64_t clone;
    uint64_t v_mut;

    // ACCESSORS
    boxed clone() const { return {clone, v_mut}; }

    // CREATORS
    static boxed box(uint64_t clone, uint64_t v_mut) { return {clone, v_mut}; }

    uint64_t unbox() const {
      const auto &[clone0, v_mut] = *this;
      return (clone0 + v_mut);
    }

    template <typename T1, typename F0>
      requires std::is_invocable_r_v<T1, F0 &, uint64_t &, uint64_t &>
    T1 boxed_rec(F0 &&f) const {
      const auto &[clone1, v_mut0] = *this;
      return f(clone1, v_mut0);
    }

    template <typename T1, typename F0>
      requires std::is_invocable_r_v<T1, F0 &, uint64_t &, uint64_t &>
    T1 boxed_rect(F0 &&f) const {
      const auto &[clone1, v_mut0] = *this;
      return f(clone1, v_mut0);
    }
  };

  struct clone {
    // DATA
    uint64_t a0;

    // ACCESSORS
    clone clone() const { return {a0}; }

    // CREATORS
    static clone dup(uint64_t a0) { return {a0}; }

    uint64_t undup() const {
      const auto &[a0] = *this;
      return a0;
    }

    template <typename T1, typename F0>
      requires std::is_invocable_r_v<T1, F0 &, uint64_t &>
    T1 clone_rec(F0 &&f) const {
      const auto &[a0] = *this;
      return f(a0);
    }

    template <typename T1, typename F0>
      requires std::is_invocable_r_v<T1, F0 &, uint64_t &>
    T1 clone_rect(F0 &&f) const {
      const auto &[a0] = *this;
      return f(a0);
    }
  };

  static inline const uint64_t boxed_sum =
      boxed::box(UINT64_C(1), UINT64_C(2)).unbox();

  static inline const uint64_t clone_val = clone::dup(UINT64_C(4)).undup();
};

#endif // INCLUDED_GENERATED_MEMBER_NAME_COLLISION
