// A class whose method returns a record declared in the same module.
//
// [HasM]'s requirements name [ConceptBeforeStruct::mo], so the concept -- and
// the [static_assert] that goes with it -- follow the struct rather than
// preceding it.

#include <concept_before_struct.h>

#include <cassert>
#include <variant>

/// [nat] is a unary inductive here, so counting the successors is the only way
/// to read it back.
static int to_int(const Nat &n) {
  int k = 0;
  const Nat *p = &n;
  while (const auto *s = std::get_if<Nat::S>(&p->v())) {
    ++k;
    p = s->a0.get();
  }
  return k;
}

int main() {
  assert(to_int(ConceptBeforeStruct::ex) == 3);
  return 0;
}
