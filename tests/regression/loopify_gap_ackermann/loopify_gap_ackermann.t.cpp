// Ackermann recurses with an inner result as the argument of an outer
// recursive call (ack m' (ack_n n')), through a fixpoint local to ack.  The
// local fixpoint becomes a second entry point of ack's frame machine, so the
// generated ack is iterative: no C++ self-call, one stack for both entries.
#include "loopify_gap_ackermann.h"

#include <cassert>
#include <iostream>

int main() {
  // Standard Ackermann values.
  assert(LoopifyGapAckermann::ack(0, 0) == 1);
  assert(LoopifyGapAckermann::ack(1, 1) == 3);
  assert(LoopifyGapAckermann::ack(2, 3) == 9);
  assert(LoopifyGapAckermann::ack(3, 3) == 61);
  std::cout << "loopify_gap_ackermann: ack(3,3) = "
            << LoopifyGapAckermann::ack(3, 3) << " PASSED" << std::endl;
  return 0;
}
