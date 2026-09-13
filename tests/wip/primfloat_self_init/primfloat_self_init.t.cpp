#include <primfloat_self_init.h>
#include <cassert>
#include <cmath>

int main() {
  assert(std::isinf(PrimFloatSelfInit::inf));
  assert(std::isnan(PrimFloatSelfInit::not_a_number));
  assert(PrimFloatSelfInit::ordinary == 0.5);
  return 0;
}
