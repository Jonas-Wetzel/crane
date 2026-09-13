#include <cassert>
#include <sibling_module_type_qualified.h>
int main() {
  assert(SiblingModuleTypeQualified::run == 3);
  return 0;
}
