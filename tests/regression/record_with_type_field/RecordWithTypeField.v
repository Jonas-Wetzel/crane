From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.
From Stdlib Require Import List.

(** A record with a [Type] field used as data is demoted from a concept to a
    struct with erased ([std::any]) fields, but its literal is still built from
    un-erased lambdas, so the initialiser does not convert. *)
Module RecordWithTypeField.

  Record alg := { ty : Type; op : ty -> ty -> ty; unit_ : ty }.

  Definition natalg : alg := {| ty := nat; op := Nat.add; unit_ := 0 |}.

  Definition fold3 (a : alg) (x : ty a) : ty a := op a x (op a x (unit_ a)).

  Definition ex : nat := fold3 natalg 2.
  Definition algs : list alg := cons natalg nil.

End RecordWithTypeField.

Crane Extraction "record_with_type_field" RecordWithTypeField.
