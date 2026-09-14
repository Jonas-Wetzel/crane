#include "dep_match_unit_fun.h"

uint64_t DepMatchUnitFun::get(const DepMatchUnitFun::tg &t, uint64_t x0_) {
  return [=]() mutable {
    if (std::holds_alternative<typename DepMatchUnitFun::tg::TF>(t.v())) {
      const auto &[a0] = std::get<typename DepMatchUnitFun::tg::TF>(t.v());
      return a0;
    } else {
      throw std::logic_error("unreachable: impossible dependent match branch");
    }
  }()(x0_);
}
