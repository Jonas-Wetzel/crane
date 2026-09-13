#include "module_alias_factory_name.h"

/// A module alias is transparent to Rocq but not to the factory-method namer:
/// reached through the alias A, the constructor c of Lib.t is called as
/// A::t::c0(...), while the type declares the factory as c.  Using Lib
/// directly works; only the aliased path gets the 0 suffix.
uint64_t Lib::get(const Lib::t &x) {
  const auto &[a0] = x;
  return a0;
}
