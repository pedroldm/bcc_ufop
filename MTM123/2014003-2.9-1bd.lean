variable U : Type
variables P Q R : U → Prop.

lemma ex291b (H : ∀ x, P x → ¬Q x) : ¬(∃ x, P x ∧ Q x ) :=
  assume H1 : ∃ x, P x ∧ Q x,
    show false, from exists.elim H1 (assume y,
                                     assume H2 : P y ∧ Q y,
                                        have H3 : P y → ¬ Q y, from H y,
                                        have H4 : P y, from and.elim_left H2,
                                        have H5 : ¬ Q y, from H3 H4,
                                        have H6 : Q y, from and.elim_right H2,
                                            show false, from H5 H6).

lemma ex291d (H : ∃ x, (P x ∧ Q x))
             (H1 : ∀ x, (P x → R x)) : ∃ x, (R x ∧ Q x) :=
exists.elim H (assume y,
               assume H2 : P y ∧ Q y,
                  have H3 : P y → R y, from H1 y,
                  have H4 : P y, from and.elim_left H2,
                  have H5 : R y, from H3 H4,
                  have H6 : Q y, from and.elim_right H2,
                      show ∃ x, (R x ∧ Q x),
                      from (exists.intro y (and.intro H5 H6))).