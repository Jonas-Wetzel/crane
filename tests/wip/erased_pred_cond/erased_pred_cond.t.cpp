#include <erased_pred_cond.h>

#include <cassert>
#include <iostream>

int main() {
  // run 1 4 = if even 4 then S 4 else 4 = 5
  auto s = ErasedPredCond::sample;
  std::cout << "sample = " << s << std::endl;
  assert(s == 5);
  return 0;
}
