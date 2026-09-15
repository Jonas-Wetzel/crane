From Crane Require Import Mapping.Std.
Require Import Crane.Mapping.NatIntStd.
From Crane Require Extraction.
From Stdlib Require Import List.
From CraneTestsWIP Require Import decl_order_method_alias.RegFile.
Import ListNotations.

(**
  Bug: a method names things declared after its struct.

  [write_r] takes an [rv], so it becomes an inline method of [struct Rv].
  Its return type names the alias [rfile] and its body calls
  [RegFile::replace_nth], and both are declared after [struct Rv], so the
  header does not compile.

  For inductives inside a nested module, functions that name the module's
  type aliases are kept out of the methods. For a top-level inductive that
  check is missing, and nothing checks what a method's body calls.
*)

Definition written : option rfile := write_r [RU; RS 1; RU] 1 (RS 7).

Definition written_second : nat :=
  match written with
  | Some (_ :: RS n :: _) => n
  | _ => 0
  end.

Definition out_of_range : bool :=
  match write_r [RU] 5 RU with
  | None => true
  | Some _ => false
  end.

Crane Extraction "decl_order_method_alias" written_second out_of_range.
