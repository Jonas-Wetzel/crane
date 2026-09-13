(** The library Crane emits first, even though it uses [Store].

    [table_a] is a constant, so extraction makes it a [static inline const]
    member initialised inside the struct body, and that initialiser calls
    [Store.build]. *)

From Stdlib Require Import List.
From CraneTestsRegression Require Import const_init_forward_ref.Store.
Import ListNotations.

Definition table_a : tbl := build nil.
