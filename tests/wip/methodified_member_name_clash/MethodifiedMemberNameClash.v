(* A module with more than one inductive makes a function over [wrap]
   eligible for methodification: it is emitted as a member of [wrap]'s struct.
   The member name is the Rocq name, unchanged -- but the struct already has
   members Crane generated for it.  Two of them are reachable from ordinary
   Rocq identifiers:

     Definition v         -> clashes with the accessor   const variant_t &v() const
     Definition variant_t -> clashes with the type alias using variant_t = ...

   Both produce C++ that does not compile ("functions that differ only in
   their return type cannot be overloaded", "redefinition of 'variant_t' as a
   different kind of symbol").  A user-chosen Rocq name should never be able
   to collide with a generated member; the factory names already get this
   treatment via [factory_name_of_ctor]. *)
From Crane Require Import Extraction.
From Crane Require Import Mapping.NatIntStd.

Module MethodifiedMemberNameClash.

  (* A second inductive in the module is what makes the functions below
     methodifiable. *)
  Inductive other : Set := O1 | O2 : other -> other.

  Inductive wrap : Set := W : other -> wrap | WW : wrap -> wrap.

  Definition v (w : wrap) : nat := 0.

  Definition variant_t (w : wrap) : nat := 1.

End MethodifiedMemberNameClash.

Crane Extraction "methodified_member_name_clash" MethodifiedMemberNameClash.
