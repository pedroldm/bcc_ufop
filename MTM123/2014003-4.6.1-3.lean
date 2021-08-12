import data.set
open set

variable {U : Type}
variables A B C : set U

theorem ex4613 : A ⊆ B → 𝒫(A) ⊆ 𝒫(B) :=
    assume H1 : A ⊆ B,
    assume X,
    assume H2 : X ∈ 𝒫(A),
        have H3 : X ⊆ A, from H2,
    assume y,
    assume H4 : y ∈ X,
        have H5 : y ∈ A, from H3 H4,
        H1 H5.