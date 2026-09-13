From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.
From Stdlib Require Import PeanoNat.

(** A class whose method returns a record type.  The concept is emitted at
    namespace scope *before* the struct that defines the record, but its body
    names [ConceptBeforeStruct::mo]. *)
Module ConceptBeforeStruct.

  Record mo := { mz : nat ; mop : nat -> nat -> nat }.

  Class HasM (A : Type) := { getm : mo }.

  Instance hn : HasM nat := { getm := {| mz := 0 ; mop := Nat.add |} }.

  Definition ex : nat := mop (getm (A:=nat)) 1 2.

End ConceptBeforeStruct.

Crane Extraction "concept_before_struct" ConceptBeforeStruct.
