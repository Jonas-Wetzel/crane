(* Crane accepts [Set Crane NonAtomicRc] together with [Monads.Thread] and
   emits, in one file, both [std::thread] and the non-atomic [crane::rc]
   refcount.  Two spawned threads that share an inductive value then race on
   that refcount: copying the shared list increments a plain [size_t], so the
   count is lost and the cells are freed while still reachable.

   Nothing in the Rocq source is unsafe -- the program is pure, uses no
   axioms, and shares an immutable value between threads.  The unsoundness is
   entirely in the flag combination Crane allows without a diagnostic. *)
From Corelib Require Import PrimInt63 PrimString.
From Crane Require Extraction.
From Crane Require Import Mapping.Std Mapping.NatIntStd Monads.ITree Monads.IO Monads.Thread.
Open Scope itree_scope.
Set Crane NonAtomicRc.

Module NonatomicRcThreadRace.

  Inductive lst : Set := Nil : lst | Cons : nat -> lst -> lst.

  Fixpoint build (n : nat) : lst :=
    match n with O => Nil | S k => Cons k (build k) end.

  Fixpoint len (l : lst) : nat :=
    match l with Nil => 0 | Cons _ r => S (len r) end.

  (** Shared between both threads; every [step] copies it. *)
  Definition shared : lst := build 4.

  Definition step (l : lst) : nat := len (Cons 0 l).

  Fixpoint churn (n : nat) (l : lst) : nat :=
    match n with O => 0 | S k => step l + churn k l end.

  Fixpoint worker (n : nat) : itree concE unit :=
    match n with
    | 0 => Ret tt
    | S k =>
      (if Nat.eqb (churn 2000 shared) 0 then print_endline "unreachable"
       else Ret tt) ;;
      worker k
    end.

  Definition test : itree concE unit :=
    t1 <- spawn worker 200 ;;
    t2 <- spawn worker 200 ;;
    join t1 ;;
    join t2 ;;
    Ret tt.

  Definition run (u : unit) : unit := runConc test.

End NonatomicRcThreadRace.

Crane Extraction "nonatomic_rc_thread_race" NonatomicRcThreadRace.
