#include "sigt_type_witness_container.h"

Nat SigtTypeWitnessContainer::depth(const SigT<std::any, List<std::any>> &p) {
  return std::any_cast<List<std::any>>(p.projT2()).length();
}
