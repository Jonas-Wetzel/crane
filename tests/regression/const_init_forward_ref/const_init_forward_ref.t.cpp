#include <const_init_forward_ref.h>

#include <cassert>

int main() {
  // [build] conses one element onto the empty table, so the length is 1.
  // The assertion is never reached today: the generated header does not
  // compile, because [struct Coord] names [Store] before [struct Store] is
  // declared.
  assert(answer == 1);
  return 0;
}
