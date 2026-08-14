/*
 * Proposição A:
 * Verifica se existe alguma combinação de valores de p e q
 * que torna a fórmula verdadeira.
 */

#include <stdio.h>

int main() {
    int p, q;
    int satisfativel = 0;
    printf("Proposicao: (p or not-q) and (not-p or q) and (not-p or not-q)\n\n");

    for (p = 0; p <= 1; p++) {
        for (q = 0; q <= 1; q++) {
            int not_p = !p;
            int not_q = !q;

            int clausula1 = p  || not_q;   // (p or not-q)
            int clausula2 = not_p || q;    // (not-p or q)
            int clausula3 = not_p || not_q; // (not-p or not-q)

            int resultado = clausula1 && clausula2 && clausula3;
            if (resultado) {
                satisfativel = 1;
            }
        }
    }

    printf("------------------------------------------------------\n");
    if (satisfativel) {
        printf("Resultado: A proposição A é SATISFATÍVEL.\n");
    } else {
        printf("Resultado: A proposição A é INSATISFATÍVEL (contradição).\n");
    }

    return 0;
}
