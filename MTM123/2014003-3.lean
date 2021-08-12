-- Prova 01 | Pedro Lucas Damasceno - 20.1.4003

variable U : Type.
variable a : U.
variables A B C : Prop.
variables F G H : U → Prop.

lemma prova01ex3a (H : A → B ∨ C) : ¬ B → (A → C) :=
  assume H1: ¬B, 
  assume H2: A,
    have H3: B ∨ C, 
      from H H2, 
        show C, 
          from (or.elim H3 (assume H4: B, 
                              show C, 
                                from false.elim(H1 H4))
                                    (assume H5: C, H5)).

lemma prova01ex3b (H1 : ∃ x, F x ∨ G x)
                  (H2 : ∀ x, F x → H x)
                  (H3 : ∀ x, G x → H x) : ∃ x, H x := sorry
