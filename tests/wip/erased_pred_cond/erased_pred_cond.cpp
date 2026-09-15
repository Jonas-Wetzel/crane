#include "erased_pred_cond.h"

Option<ErasedPredCond::semty> ErasedPredCond::table(const Nat &n) {
  if (std::holds_alternative<typename Nat::O>(n.v())) {
    return Option<ErasedPredCond::semty>::none();
  } else {
    return Option<ErasedPredCond::semty>::some(
        Prod<std::function<Bool0(Nat)>, std::function<Nat(Nat)>>::pair(
            [](const Nat &_x) { return _x.even(); },
            [](Nat x) { return Nat::s(x); }));
  }
}

Nat ErasedPredCond::run(const Nat &n, Nat x) {
  auto &&_sv = table(n);
  if (std::holds_alternative<typename Option<
          Prod<std::function<Bool0(Nat)>, std::function<Nat(Nat)>>>::Some>(
          _sv.v())) {
    const auto &[a0] = std::get<typename Option<
        Prod<std::function<Bool0(Nat)>, std::function<Nat(Nat)>>>::Some>(
        _sv.v());
    const auto &[a00, a10] = a0;
    switch (a00(x)) {
    case Bool0::TRUE_: {
      return a10(std::move(x));
    }
    case Bool0::FALSE_: {
      return x;
    }
    default:
      std::unreachable();
    }
  } else {
    return x;
  }
}
