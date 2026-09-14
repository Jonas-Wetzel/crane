#include <dependent_match_branch_types.h>
#include <cassert>

static unsigned nat_to_uint(const Nat &n) {
  unsigned acc = 0;
  const Nat *cur = &n;
  while (std::holds_alternative<Nat::S>(cur->v())) {
    ++acc;
    cur = std::get<Nat::S>(cur->v()).a0.get();
  }
  return acc;
}

int main() {
  assert(nat_to_uint(DependentMatchBranchTypes::run) == 7);
  return 0;
}
