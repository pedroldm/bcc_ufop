-- Live javascript version of Lean

import data.set 

open set

-- universo de discurso
variable {U : Type}

-- garantindo que o universo é não vazio
variable x : U

-- definindo dois conjuntos.
variables A B C : set U

-- definindo uma família

variable F : set (set U)

-- definindo a união de famílias

def Union (G : set (set U)) : set U :=
    {x | ∃ X, X ∈ G ∧ x ∈ X}

-- interseção de famílias 

def Intersection (G : set (set U)) : set U := 
  {x | ∀ X, X ∈ G → x ∈ X}

lemma ex1 : A \ (A \ B) ⊆ A ∩ B := 
     assume x,
     assume H : x ∈ A ∧ (x ∉ A ∨ x ∈ B),
     have H1 : x ∉ A ∨ x ∈ B, from and.elim_right H,
     have H2 : x ∈ A, from and.elim_left H,
     have H3 : x ∈ B, from or.elim H1 H2,
     show x ∈ A ∧ x ∈ B, from and.intro H2 H3.

lemma ex2 : A ∈ F → Intersection F ⊆ Union F := 
    assume H: A ∈ F,
    assume x,
    assume H1: x ∈ Intersection F,
    have H2: A ∈ F → x ∈ A, from H1 A,
    have H3: x ∈ A, from H2 H,
    show ∃ A, A ∈ F ∧ x ∈ A, from exists.intro A(and.intro H H3).

lemma ex3 : A ∩ C ⊆ B ∧ x ∈ C → x ∉ A \ B := 
    assume H : A ∩ C ⊆ B ∧ x ∈ C,
    assume H1 : x ∈ A \ B,
    have Ha : x ∈ A, from and.elim_left H1,
    have Hb : x ∉ B, from and.elim_right H1,
    have Hc : x ∈ C, from and.elim_right H,
    have H2 : x ∈ A ∩ C, from and.intro Ha Hc,
    have H3 : A ∩ C ⊆ B, from and.elim_left H,
    have H4 : x ∈ B, from H3 H2,
    show false, from Hb H4.

lemma ex4 : A ⊆ B → A \ C ⊆ B \ C :=
    assume H : ∀ x, x ∈ A → x ∈ B,
    assume x,
    assume Ha: x ∈ A ∧ x ∉ C,
    have Hb : x ∈ A → x ∈ B, from H x,
    have Hc : x ∈ A, from and.elim_left Ha,
    have Hd : x ∉ C, from and.elim_right Ha,
    have He : x ∈ B, from Hb Hc,
    show x ∈ B ∧ x ∉ C, from and.intro He Hd.