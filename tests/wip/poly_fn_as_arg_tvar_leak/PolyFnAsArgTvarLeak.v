From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.

(** A polymorphic function passed as an argument to itself.  Crane eta-expands it
    at the call site and spells the eta-parameters with the *callee's* type
    variable name, which is not in scope there. *)
Module PolyFnAsArgTvarLeak.

  Definition twice {A} (f : A -> A) : A -> A := fun x => f (f x).

  Definition run : nat := twice twice S 0.

End PolyFnAsArgTvarLeak.

Crane Extraction "poly_fn_as_arg_tvar_leak" PolyFnAsArgTvarLeak.
