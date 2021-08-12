variables P Q R S T : Prop.

lemma ex1571a (H1 : (P ∧ Q) ∧ R)
              (H2 : S ∧ T) : Q ∧ S :=
  and.intro
    (and.elim_right (and.elim_left H1))
    (and.elim_left H2). 

lemma ex1571c (H1 : P)
              (H2 : P → (P → Q)) : Q :=
  show Q,
    from (H2 H1 (show P, from (H1))).

lemma ex1571d : (P ∧ Q) → P :=
  assume H : P ∧ Q,
    (and.elim_left H).

lemma ex1571e (H1 : P) : Q → P ∧ Q :=
  assume H : Q,
    and.intro
      (show P, from (H1))
      (show Q, from (H)).