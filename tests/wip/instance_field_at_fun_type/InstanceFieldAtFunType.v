From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.
From Stdlib Require Import List.

(** A class field whose instance is at a function type.  [d := S] is emitted as
    [static Nat d(Nat x)], absorbing the argument, so the value no longer has the
    field's type and the instance fails its own concept check. *)
Module InstanceFieldAtFunType.

  Class D (A : Type) := { d : A }.

  Instance dn : D nat := { d := 0 }.
  Instance df : D (nat -> nat) := { d := S }.

  Definition ex : nat -> nat := d.
  Definition run : nat := ex 1.

End InstanceFieldAtFunType.

Crane Extraction "instance_field_at_fun_type" InstanceFieldAtFunType.
