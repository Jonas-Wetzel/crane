#include <generated_member_name_collision.h>
#include <cassert>

int main() {
  assert(GeneratedMemberNameCollision::boxed_sum == 3);
  assert(GeneratedMemberNameCollision::clone_val == 4);
  return 0;
}
