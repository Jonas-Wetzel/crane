#include "sibling_module_type_qualified.h"

uint64_t SiblingModuleTypeQualified::f(const Lib::t &x) {
  const auto &[a0] = x;
  return a0;
}

uint64_t SiblingModuleTypeQualified::g(const Lib::Inner::u &y) {
  const auto &[a0] = y;
  return a0;
}
