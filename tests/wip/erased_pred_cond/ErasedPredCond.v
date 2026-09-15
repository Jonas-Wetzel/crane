From Crane Require Extraction.

Module ErasedPredCond.

(** A value-dependent semantic type: [semty n] mentions [n], so Crane has no
    C++ spelling for it and erases it to [std::any].  The pair it stands for
    holds a predicate and an action, exactly the shape
    [Crane.Libraries.ParseALot]'s [production_semty] has.

    The interesting position is [p x] in the [if]: it is an application of an
    erased function, so its result arrives as [std::any] and the condition
    needs [std::any_cast<bool>].  Crane instead casts it at the type of the
    [if]'s *branches*, which does not compile. *)

Definition semty (n : nat) : Type := ((nat -> bool) * (nat -> nat))%type.

Definition table (n : nat) : option (semty n) :=
  match n with
  | 0 => None
  | _ => Some (Nat.even, S)
  end.

Definition run (n x : nat) : nat :=
  match table n with
  | Some (p, f) => if p x then f x else x
  | None => x
  end.

Definition sample : nat := run 1 4.

End ErasedPredCond.

Crane Extraction "erased_pred_cond" ErasedPredCond.
