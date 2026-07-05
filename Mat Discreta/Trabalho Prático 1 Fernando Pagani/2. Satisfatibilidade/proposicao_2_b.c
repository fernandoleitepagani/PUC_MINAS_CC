/*
 * Proposição B:
 * (¬p ∨ ¬q ∨ r) ∧ (¬p ∨ q ∨ ¬s) ∧ (p ∨ ¬q ∨ ¬s) ∧ (¬p ∨ ¬r ∨ ¬s) ∧ (p ∨ q ∨ ¬r) ∧ (p ∨ ¬r ∨ ¬s)
 */

#include <stdio.h>

int main() {
    int p, q, r, s;
    int satisfativel = 0;

    printf("=== Proposição B ===\n");

    for (p = 0; p <= 1; p++)
    for (q = 0; q <= 1; q++)
    for (r = 0; r <= 1; r++)
    for (s = 0; s <= 1; s++) {
        int np=!p, nq=!q, nr=!r, ns=!s;

        int c1 = np || nq || r;   // (¬p ∨ ¬q ∨ r)
        int c2 = np || q  || ns;  // (¬p ∨ q ∨ ¬s)
        int c3 = p  || nq || ns;  // (p ∨ ¬q ∨ ¬s)
        int c4 = np || nr || ns;  // (¬p ∨ ¬r ∨ ¬s)
        int c5 = p  || q  || nr;  // (p ∨ q ∨ ¬r)
        int c6 = p  || nr || ns;  // (p ∨ ¬r ∨ ¬s)

        int resultado = c1 && c2 && c3 && c4 && c5 && c6;

        if (resultado) satisfativel = 1;
    }

    printf("--------------------------------------------------\n");
    if (satisfativel)
        printf("Resultado: A proposição B é SATISFATÍVEL.\n");
    else
        printf("Resultado: A proposição B é INSATISFATÍVEL (contradição).\n");

    return 0;
}
