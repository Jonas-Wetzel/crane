// Crane bug: a concept emitted before the struct it names.
//
// [HasM] is emitted at namespace scope above [struct ConceptBeforeStruct], but
// its body mentions [ConceptBeforeStruct::mo]:
//   error: use of undeclared identifier 'ConceptBeforeStruct'

#include <concept_before_struct.h>

#include <cassert>

int main() {
  assert(ConceptBeforeStruct::ex.to_int() == 3);
  return 0;
}
