From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.

(** [comparison] is emitted as a namespace-scope [enum class] *after* the struct
    whose member functions mention it, so the member declarations refer to an
    undeclared type. *)
Module EnumAfterUse.

  Definition c (a b : nat) : comparison := Nat.compare a b.

  Definition tonat (x : comparison) : nat :=
    match x with Eq => 0 | Lt => 1 | Gt => 2 end.

  Definition ex : nat := tonat (c 1 2) + tonat (c 2 1) + tonat (c 1 1).

End EnumAfterUse.

Crane Extraction "enum_after_use" EnumAfterUse.
