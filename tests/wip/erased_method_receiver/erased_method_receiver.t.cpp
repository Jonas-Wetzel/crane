// Crane bug: an erased value used as a method receiver.
//
// [projT2 s] has C++ type [std::any] and is handed straight to [.length()]:
//   error: no member named 'length' in 'std::any'

#include <erased_method_receiver.h>

#include <cassert>

int main() {
  assert(ErasedMethodReceiver::run.to_int() == 1);
  return 0;
}
