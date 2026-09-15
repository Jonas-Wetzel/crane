From Crane Require Import Mapping.Std.
Require Import Crane.Mapping.NatIntStd.
From Crane Require Extraction.
From Stdlib Require Import List.
From CraneTestsWIP Require Import decl_order_method_call.Regs.
Import ListNotations.

(**
  Bug: a method calls into a struct declared after it.

  [write_r] takes an [rv], so it becomes an inline method of [struct Rv].
  Its body calls [Regs::replace_nth], and [struct Regs] is emitted after
  every global-scope type, so the header does not compile. There is no
  type alias here: the call alone is enough.
*)

Definition written_second : nat :=
  match write_r [RU; RS 1; RU] 1 (RS 7) with
  | Some (_ :: RS n :: _) => n
  | _ => 0
  end.

Definition out_of_range : bool :=
  match write_r [RU] 5 RU with
  | None => true
  | Some _ => false
  end.

Crane Extraction "decl_order_method_call" written_second out_of_range.
