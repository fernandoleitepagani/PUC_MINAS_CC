/*
 * Proposição C:
 * Verifica se existe alguma combinação de valores de p e q
 * que torna a fórmula verdadeira.
 */

#include <stdio.h>

int main() {
    int p, q;
    int satisfativel = 0;
    printf("Proposicao C: (p sse q) and (not-p sse q)\n\n");

    for (p = 0; p <= 1; p++) {
        for (q = 0; q <= 1; q++) {
            int not_p = !p;

            // a ↔ b  ≡  (a && b) || (!a && !b)
            int bicondicional1 = (p == q);       // (p sse q)
            int bicondicional2 = (not_p == q);   // (not-p sse q)

            int resultado = bicondicional1 && bicondicional2;

            if (resultado) {
                satisfativel = 1;
            }
        }
    }

    printf("------------------------------------------------------\n");
    if (satisfativel) {
        printf("Resultado: A proposição C é SATISFATÍVEL.\n");
    } else {
        printf("Resultado: A proposição C é INSATISFATÍVEL (contradição).\n");
    }

    return 0;
}
