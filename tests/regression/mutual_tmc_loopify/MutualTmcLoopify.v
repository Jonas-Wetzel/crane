From Crane Require Import Extraction.
From Crane.Mapping Require Import Std.

Module MutualTmcLoopify.

(** Mutual recursion whose recursive calls are under a constructor (TMC).

    Loopification inlines the sibling [odds] into [evens] as an
    immediately-invoked lambda, which still calls [evens].  That body is
    adopted as a second entry point of [evens]'s frame machine, so both halves
    of the mutual recursion push onto one stack and the extracted [evens] has
    no C++ self-call -- it survives the depth this test exercises. *)

Inductive mylist := mnil | mcons : nat -> mylist -> mylist.

Fixpoint evens (n : nat) : mylist :=
  match n with
  | O => mnil
  | S k => mcons n (odds k)
  end
with odds (n : nat) : mylist :=
  match n with
  | O => mnil
  | S k => mcons n (evens k)
  end.

Fixpoint len (l : mylist) : nat :=
  match l with mnil => 0 | mcons _ r => S (len r) end.

End MutualTmcLoopify.

Crane Loopify MutualTmcLoopify.evens.
Crane Extraction "mutual_tmc_loopify" MutualTmcLoopify.evens MutualTmcLoopify.len.
