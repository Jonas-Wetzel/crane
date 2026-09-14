#include <cassert>
#include <instance_method_ignores_arg.h>
int main() {
  assert(InstanceMethodIgnoresArg::run == 1);
  return 0;
}
