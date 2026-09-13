#include <eponymous_record_own_type.h>
#include <cassert>

int main() {
  // The module is renamed out of the way of the record it cannot absorb.
  assert(EponymousRecordOwnType_Mod::answer == 5);
  assert(EponymousRecordOwnType_Mod::default_value.field == 5);
  return 0;
}
