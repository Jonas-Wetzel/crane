From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.
From Stdlib Require Import List.

(** [comp S] is a partially applied curried function.  Crane eta-expands it into
    a two-parameter lambda and hands that to [List::map], which calls its
    argument with one argument. *)
Module MapOverPartialApp.

  Definition comp {A B C} (f : B -> C) (g : A -> B) : A -> C := fun x => f (g x).

  Definition ex : list (nat -> nat) := List.map (comp S) (cons S (cons S nil)).

  Definition run : nat := match ex with nil => 0 | cons f _ => f 0 end.

End MapOverPartialApp.

Crane Extraction "map_over_partial_app" MapOverPartialApp.
