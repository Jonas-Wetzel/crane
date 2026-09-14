From Crane Require Extraction.

(** A match with a [return] clause computing a *different* type per branch is
    given one C++ return type for all branches — the one the use site wants.
    The [vnil] branch returns [tt], whose type is [unit], and clang rejects "no
    viable conversion from returned value of type 'Unit' to function return
    type 'Nat'".  Dependent matches whose branches agree on a type extract
    fine. *)

Module DependentMatchBranchTypes.
  Inductive vec : nat -> Type :=
  | vnil : vec 0
  | vcons : forall n, nat -> vec n -> vec (S n).

  Definition hd (n : nat) (v : vec (S n)) : nat :=
    match v in vec m return match m with 0 => unit | S _ => nat end with
    | vnil => tt
    | vcons _ x _ => x
    end.

  Definition run : nat := hd 0 (vcons 0 7 vnil).
End DependentMatchBranchTypes.

Crane Extraction "dependent_match_branch_types" DependentMatchBranchTypes.
