(* [Set Crane Loopify] turns tail-modulo-cons recursion into a worklist loop --
   but only for functions that stay free functions.  A module with more than
   one inductive makes [wraps] eligible for methodification, and the method it
   becomes is emitted as plain recursion:

     wrap wraps(uint64_t n) const {
       ... return wrap::ww(std::move(self).wraps(k)); }

   The sibling methods in the same struct ([wdepth], [wrap_rec]) *are*
   loopified, so this is not the loopifier declining the shape: it is the TMC
   rewrite being skipped once the function is a method.  Drop the [lst]
   inductive and [wraps] stays a free function and is loopified correctly.

   The result is an unbounded C++ recursion for a Rocq function the user asked
   to have loopified: stack overflow at depth 100000. *)
From Crane Require Import Extraction.
From Crane Require Import Mapping.NatIntStd.
Set Crane Loopify.

Module MethodifiedTmcNoLoopify.

  (* A second inductive in the module is what makes [wraps] methodifiable. *)
  Inductive lst : Set := Nil | Cons : nat -> lst -> lst.

  Inductive wrap : Set := W : lst -> wrap | WW : wrap -> wrap.

  Fixpoint wraps (n : nat) (w : wrap) : wrap :=
    match n with O => w | S k => WW (wraps k w) end.

  Fixpoint wdepth (w : wrap) : nat :=
    match w with W _ => 0 | WW x => S (wdepth x) end.

  Definition deep : nat := wdepth (wraps 100000 (W Nil)).

End MethodifiedTmcNoLoopify.

Crane Extraction "methodified_tmc_no_loopify" MethodifiedTmcNoLoopify.
