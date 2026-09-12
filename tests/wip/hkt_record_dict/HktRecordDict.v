From Crane Require Import Extraction.
From Crane Require Import Mapping.Std.

(** The same higher-kinded signature as a [Record] rather than a [Class].  The
    record's parameter is emitted as a plain [typename F] but its field type is
    spelled [F<std::any>], and the accessor treats the dictionary *value* as a
    scope ([f::template fmd<...>]). *)
Module HktRecordDict.

  Record FnD (F : Type -> Type) :=
    { fmd : forall A B, (A -> B) -> F A -> F B }.

  Definition optd : FnD option :=
    {| fmd := fun A B f o => match o with None => None | Some x => Some (f x) end |}.

  Definition ex : option nat := fmd _ optd _ _ S (Some 1).

End HktRecordDict.

Crane Extraction "hkt_record_dict" HktRecordDict.
