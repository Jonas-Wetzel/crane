(** Two [Crane Extraction] commands naming the same output file silently
    overwrite one another: the second unit's header and implementation replace
    the first's, with no warning, so the declarations of the first module are
    simply gone.  Either the second command should be refused or the two units
    should be kept apart. *)

From Crane Require Import Extraction.
From Crane Require Import Mapping.Std Mapping.NatIntStd.

Module First.
  Definition one : nat := 1.
End First.

Module Second.
  Definition two : nat := 2.
End Second.

Crane Extraction "duplicate_output_target" First.
Crane Extraction "duplicate_output_target" Second.
