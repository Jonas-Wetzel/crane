#include <factory_name_collision.h>
#include <cassert>

int main() {
  assert(FactoryNameCollision::head == 7);
  assert(FactoryNameCollision::cased_sum == 3);
  return 0;
}
