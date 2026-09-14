From Crane Require Extraction.

(** A let-bound polymorphic function is lifted out of the body into a template,
    but only the *first* use is rewritten to the lifted name: the second and
    later uses still say [id2], which no longer exists.  The number of type
    instantiations is irrelevant — what matters is that the binder is used more
    than once. *)

Module LetPolymorphicLiftRename.
  Definition body (n : nat) : nat :=
    let id2 := fun (A : Type) (x : A) => x in
    id2 nat n + (if id2 bool true then 1 else 0).

  Definition run : nat := body 1.
End LetPolymorphicLiftRename.

Crane Extraction "let_polymorphic_lift_rename" LetPolymorphicLiftRename.
