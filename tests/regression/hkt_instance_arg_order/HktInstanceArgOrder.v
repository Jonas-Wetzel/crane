From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.
From Stdlib Require Import List.

(** Two instance arguments in one signature.  The declaration binds them in the
    order the binders appear, but the call site passes them in the order the
    constraints were discovered, so the outer and inner functors are swapped. *)
Module HktInstanceArgOrder.

  Class Fn (F : Type -> Type) := { fm : forall A B, (A -> B) -> F A -> F B }.

  Instance optf : Fn option :=
    { fm := fun A B f o => match o with None => None | Some x => Some (f x) end }.
  Instance lstf : Fn list := { fm := fun A B f l => List.map f l }.

  Definition compose_map {F G} `{Fn F} `{Fn G} {A B} (f : A -> B) (x : F (G A))
    : F (G B) := fm _ _ (fm _ _ f) x.

  Definition ex : option (list nat) := compose_map S (Some (cons 1 nil)).

End HktInstanceArgOrder.

Crane Extraction "hkt_instance_arg_order" HktInstanceArgOrder.
