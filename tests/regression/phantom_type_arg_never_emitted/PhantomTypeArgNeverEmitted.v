From Crane Require Extraction.

(** [phantom A] does not store an [A], so nothing in the program's *values*
    ever mentions [bool].  The call site still spells the instantiation
    [phantom<Bool0>], but dependency collection only walks value positions, so
    the [Bool0] enum is never emitted: "use of undeclared identifier
    'Bool0'".  Anything else in the module that mentions [bool] in a value
    position hides the bug, which is why this test computes with [nat] only. *)

Module PhantomTypeArgNeverEmitted.
  Inductive phantom (A : Type) : Type := ph : nat -> phantom A.
  Arguments ph {A} _.

  Definition get {A} (p : phantom A) : nat := match p with ph n => n end.

  Definition run : nat := get (ph (A:=bool) 3).
End PhantomTypeArgNeverEmitted.

Crane Extraction "phantom_type_arg_never_emitted" PhantomTypeArgNeverEmitted.
