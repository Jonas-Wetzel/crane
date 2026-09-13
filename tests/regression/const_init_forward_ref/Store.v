(** The library Crane emits second.  It defines a type alias and a function
    returning that type, and depends on nothing else in this test. *)

From Stdlib Require Import List.
Import ListNotations.

Definition tbl : Type := list nat.

Definition build (t : tbl) : tbl := 1 :: t.
