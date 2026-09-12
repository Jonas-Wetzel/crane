From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.

(** An instance at a partially applied type constructor.  The instance's member
    alias is emitted at the constructor's full arity
    ([template <typename _A0, typename _A1> using F = std::pair<_A0,_A1>]) rather
    than at the arity the class demands, so [F<T>] does not resolve. *)
Module HktPartialAppInstance.

  Class Fn (F : Type -> Type) := { fm : forall A B, (A -> B) -> F A -> F B }.

  Instance pf (X : Type) : Fn (prod X) :=
    { fm := fun A B f p => (fst p, f (snd p)) }.

  Definition ex : (bool * nat)%type := fm _ _ S (true, 1).

End HktPartialAppInstance.

Crane Extraction "hkt_partial_app_instance" HktPartialAppInstance.
