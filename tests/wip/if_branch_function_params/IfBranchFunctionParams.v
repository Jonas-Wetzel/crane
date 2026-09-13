From Crane Require Extraction.

(** An [if] whose two branches are two *different* function-typed parameters is
    emitted as an immediately-invoked lambda with a deduced return type.  The
    two [return] statements hand back two distinct closure types, so deduction
    reports conflicting types.  Returning the same function in both branches,
    or one branch returning a literal lambda, happens to work; two different
    binders do not. *)

Module IfBranchFunctionParams.
  Definition h (b : bool) (f g : nat -> nat) : nat -> nat := if b then f else g.

  Definition run : nat := h false S (fun x => x + 2) 1.
End IfBranchFunctionParams.

Crane Extraction "if_branch_function_params" IfBranchFunctionParams.
