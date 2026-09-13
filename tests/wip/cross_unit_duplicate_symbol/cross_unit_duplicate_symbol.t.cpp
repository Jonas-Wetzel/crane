#include <cross_unit_duplicate_symbol.h>
#include <cassert>

int main() {
  assert(Use::answer == 2);
  return 0;
}
