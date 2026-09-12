#include "enum_after_use.h"

/// comparison is emitted as a namespace-scope enum class *after* the struct
/// whose member functions mention it, so the member declarations refer to an
/// undeclared type.
Comparison EnumAfterUse::c(const Nat::nat &x0_, const Nat::nat &x1_) {
  return Nat::compare(x0_, x1_);
}

Nat::nat EnumAfterUse::tonat(Comparison x) {
  switch (x) {
  case Comparison::EQ: {
    return Nat::nat::o();
  }
  case Comparison::LT: {
    return Nat::nat::s(Nat::nat::o());
  }
  case Comparison::GT: {
    return Nat::nat::s(Nat::nat::s(Nat::nat::o()));
  }
  default:
    std::unreachable();
  }
}

Comparison Nat::compare(const Nat::nat &n, const Nat::nat &m) {
  if (std::holds_alternative<typename Nat::nat::O>(n.v())) {
    if (std::holds_alternative<typename Nat::nat::O>(m.v())) {
      return Comparison::EQ;
    } else {
      return Comparison::LT;
    }
  } else {
    const auto &[a0] = std::get<typename Nat::nat::S>(n.v());
    if (std::holds_alternative<typename Nat::nat::O>(m.v())) {
      return Comparison::GT;
    } else {
      const auto &[a00] = std::get<typename Nat::nat::S>(m.v());
      return Nat::compare(*a0, *a00);
    }
  }
}
