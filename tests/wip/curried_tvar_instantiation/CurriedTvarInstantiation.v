From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.
From Stdlib Require Import List.

(** A type variable instantiated at a curried function type is spelled
    [std::function<Nat(Nat,Nat)>] (flattened) in one place and
    [std::function<std::function<Nat(Nat)>(Nat)>] (curried) in the other, so the
    declaration and the call site disagree. *)
Module CurriedTvarInstantiation.

  Definition apply_all {A} (fs : list (A -> A)) (x : A) : A :=
    List.fold_left (fun a f => f a) fs x.

  Definition ex : nat -> nat := apply_all (cons (fun (g : nat -> nat) => g) nil) S.

  Definition run : nat := ex 1.

End CurriedTvarInstantiation.

Crane Extraction "curried_tvar_instantiation" CurriedTvarInstantiation.
