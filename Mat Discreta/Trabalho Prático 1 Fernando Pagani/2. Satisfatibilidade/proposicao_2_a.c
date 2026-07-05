/*
 * Proposição A:
 * (p ∨ q ∨ ¬r) ∧ (p ∨ ¬q ∨ ¬s) ∧ (p ∨ ¬r ∨ ¬s) ∧ (¬p ∨ ¬q ∨ ¬s) ∧ (p ∨ q ∨ ¬s)
 */

#include <stdio.h>

int main() {
    int p, q, r, s;
    int satisfativel = 0;

    printf("=== Proposição A ===\n");
for (p = 0; p <= 1; p++)
    for (q = 0; q <= 1; q++)
    for (r = 0; r <= 1; r++)
    for (s = 0; s <= 1; s++) {
        int np=!p, nq=!q, nr=!r, ns=!s;

        int c1 = p  || q  || nr;  // (p ∨ q ∨ ¬r)
        int c2 = p  || nq || ns;  // (p ∨ ¬q ∨ ¬s)
        int c3 = p  || nr || ns;  // (p ∨ ¬r ∨ ¬s)
        int c4 = np || nq || ns;  // (¬p ∨ ¬q ∨ ¬s)
        int c5 = p  || q  || ns;  // (p ∨ q ∨ ¬s)

        int resultado = c1 && c2 && c3 && c4 && c5;

        if (resultado) satisfativel = 1;
    }

    printf("---------------------------------------------\n");
    if (satisfativel)
        printf("Resultado: A proposição A é SATISFATÍVEL.\n");
    else
        printf("Resultado: A proposição A é INSATISFATÍVEL (contradição).\n");

    return 0;
}
