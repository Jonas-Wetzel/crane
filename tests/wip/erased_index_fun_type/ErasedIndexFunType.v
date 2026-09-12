From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.

(** A type-indexed inductive whose index can be a function type.  [dflt] is
    declared as returning [std::any], and the call site then applies the result
    directly: "type 'std::any' does not provide a call operator". *)
Module ErasedIndexFunType.

  Inductive ty : Type -> Type :=
  | TN : ty nat
  | TF : forall A B, ty A -> ty B -> ty (A -> B).

  Fixpoint dflt {T} (t : ty T) : T :=
    match t with
    | TN => 0
    | TF A B _ b => fun _ => dflt b
    end.

  Definition ex : nat -> nat := dflt (TF nat nat TN TN).
  Definition run : nat := ex 5.

End ErasedIndexFunType.

Crane Extraction "erased_index_fun_type" ErasedIndexFunType.
