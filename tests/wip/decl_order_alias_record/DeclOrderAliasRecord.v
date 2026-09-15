From Crane Require Import Mapping.Std.
Require Import Crane.Mapping.NatIntStd.
From Crane Require Extraction.
From Stdlib Require Import List.
From CraneTestsWIP Require Import decl_order_alias_record.InstrLib.
Import ListNotations.

(**
  Bug: a record is emitted before the type it contains.

  The header declares [struct prog] before [using final_instr] and before
  [struct Instr], so it does not compile ("use of undeclared identifier
  'final_instr'"). Without the enum [cop] the order is right.

  [sort_inductives_within_module] places a whole Kahn layer per round, so
  [instr], which depends on [cop], moves behind [prog], which has no
  dependencies. It also does not see that [prog] needs [instr]: that
  dependency goes through the type alias [final_instr].
*)

Definition sample : prog :=
  {| code := [IGo 3; ICmp CEq; IStop]; nregs := 2 |}.

Definition sample_size : nat := length (code sample).

Definition sample_regs : nat := nregs sample.

Crane Extraction "decl_order_alias_record" sample_size sample_regs.
