#ifndef INCLUDED_PRIMFLOAT_SELF_INIT
#define INCLUDED_PRIMFLOAT_SELF_INIT

struct PrimFloat {
  static inline const double infinity = infinity;
  static inline const double nan = nan;
};

struct PrimFloatSelfInit {
  static inline const double inf = PrimFloat::infinity;
  static inline const double not_a_number = PrimFloat::nan;
  static inline const double ordinary = 0x1p-1;
};

#endif // INCLUDED_PRIMFLOAT_SELF_INIT
