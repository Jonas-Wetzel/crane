From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.
From Stdlib Require Import String.

(** An erased value used as the *receiver* of a mapped type's method.  [projT2 s]
    has C++ type [std::any] and is handed straight to [.length()] with no cast. *)
Module ErasedMethodReceiver.

  Definition s : @sigT Type (fun A => A) := @existT Type (fun A => A) string "q"%string.

  Definition run : nat := String.length (projT2 s).

End ErasedMethodReceiver.

Crane Extraction "erased_method_receiver" ErasedMethodReceiver.
