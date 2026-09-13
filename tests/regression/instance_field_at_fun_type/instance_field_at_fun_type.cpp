#include "instance_field_at_fun_type.h"

/// A class field whose instance is at a function type.  d := S is emitted as
/// static Nat d(Nat x), absorbing the argument, so the value no longer has the
/// field's type and the instance fails its own concept check.
Nat InstanceFieldAtFunType::ex(const Nat &x0_) { return df::d()(x0_); }
