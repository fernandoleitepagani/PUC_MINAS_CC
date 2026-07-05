/*
 * Proposição B:
 * Verifica se existe alguma combinação de valores de p e q
 * que torna a fórmula verdadeira.
 */

#include <stdio.h>

int main() {
    int p, q;
    int satisfativel = 0;
    printf("Proposicao: (p entao q) and (p entao not-q) and (not-p entao q) and (not-p entao not-q)\n\n");
    for (p = 0; p <= 1; p++) {
        for (q = 0; q <= 1; q++) {
            int not_p = !p;
            int not_q = !q;

            // a → b  ≡  ¬a ∨ b
            int clausula1 = not_p || q;      // (p entao q)
            int clausula2 = not_p || not_q;  // (p entao not-q)
            int clausula3 = p     || q;      // (not-p entao q)
            int clausula4 = p     || not_q;  // (not-p entao not-q)

            int resultado = clausula1 && clausula2 && clausula3 && clausula4;

            if (resultado) {
                satisfativel = 1;
            }
        }
    }

    printf("--------------------------------------------------------------------\n");
    if (satisfativel) {
        printf("Resultado: A proposição B é SATISFATÍVEL.\n");
    } else {
        printf("Resultado: A proposição B é INSATISFATÍVEL (contradição).\n");
    }

    return 0;
}
