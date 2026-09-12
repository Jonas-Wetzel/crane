#include "concept_before_struct.h"

Nat PeanoNat::add(const Nat &n, Nat m) {
  if (std::holds_alternative<typename Nat::O>(n.v())) {
    return m;
  } else {
    const auto &[a0] = std::get<typename Nat::S>(n.v());
    return Nat::s(PeanoNat::add(*a0, std::move(m)));
  }
}
