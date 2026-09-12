#include "erased_index_fun_type.h"

/// A type-indexed inductive whose index can be a function type.  dflt is
/// declared as returning std::any, and the call site then applies the result
/// directly: "type 'std::any' does not provide a call operator".
Nat ErasedIndexFunType::ex(const Nat &x0_) {
  return std::any_cast<Nat>(std::any_cast<std::function<std::any(std::any)>>(
      dflt<std::function<Nat(Nat)>>(ty::tf(ty::tn(), ty::tn())))(
      std::any(x0_)));
}
