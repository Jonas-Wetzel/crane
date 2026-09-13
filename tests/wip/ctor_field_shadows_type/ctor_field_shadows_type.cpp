#include "ctor_field_shadows_type.h"

uint64_t CtorFieldShadowsType::total(const CtorFieldShadowsType::t &x) {
  const auto &[t0, extra] = x;
  return (t0 + extra);
}
