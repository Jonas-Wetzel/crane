#include <cassert>
#include <erased_fn_in_recursive_container.h>
int main() {
  assert(ErasedFnInRecursiveContainer::run == 2);
  return 0;
}
