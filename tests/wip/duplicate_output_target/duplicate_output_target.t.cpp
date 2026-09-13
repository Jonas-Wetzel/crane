#include <duplicate_output_target.h>
#include <cassert>

int main() {
  assert(First::one == 1);
  assert(Second::two == 2);
  return 0;
}
