#include <existential_fn_projection.h>
#include <cassert>

int main() {
  assert(ExistentialFnProjection::measured == 5);
  assert(ExistentialFnProjection::tag == 8);
  return 0;
}
