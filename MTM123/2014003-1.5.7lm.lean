variables P Q R S : Prop.

lemma ex157l (H1 : P → Q)
             (H2 : R → S) : (P ∨ R) → (Q ∨ S) :=
  assume H3 : P ∨ R,
  show Q ∨ S, from (or.elim H3
                   (assume H4 : P,
                    show Q ∨ S, from (or.intro_left S(H1 H4)))
                   (assume H5 : R,
                    show Q ∨ S, from (or.intro_right Q(H2 H5)))).

lemma ex157m (H1 : Q → R) : (P → Q) → (P → R) :=
  assume H2 : P → Q,
  assume H3 : P,
  show R, from (H1
                (show Q, from (H2 H3))).