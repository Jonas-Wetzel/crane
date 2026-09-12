From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.

(** A rank-2 argument: [f] is polymorphic and gets used at two different types.
    Crane emits the two results without casting them back from [std::any], and
    emits a bogus body for the identity lambda passed in. *)
Module HigherRankPoly.

  Definition apply_id (f : forall A : Type, A -> A) : nat * bool :=
    (f nat 1, f bool true).

  Definition ex : nat * bool := apply_id (fun A x => x).

End HigherRankPoly.

Crane Extraction "higher_rank_poly" HigherRankPoly.
