/*
 * Item A - Avaliação de Conclusões e Inferência
 *
 * Premissas:
 *   P1: c → s   (comer picante → sonhos estranhos)
 *   P2: t → s   (trovões → sonhos estranhos)
 *   P3: ¬s      (não tive sonhos estranhos)
 *
 * Conclusão inferida: ¬c ∧ ¬t
 *   (Não comi picante E não houve trovões)
 *
 * O programa verifica que a conclusão é consequência lógica das premissas,
 * ou seja: em toda interpretação onde P1, P2 e P3 são verdadeiras,
 * a conclusão também é verdadeira.
 */

#include <stdio.h>

int main() {
    int c, s, t;
    int contraexemplo = 0;  /* 1 se encontrar um caso que falsifica a conclusão */

    printf("=== Item A ===\n");

    for (c = 0; c <= 1; c++)
    for (s = 0; s <= 1; s++)
    for (t = 0; t <= 1; t++) {
        int p1 = !c || s;       /* c entao s */
        int p2 = !t || s;       /* t entao s */
        int p3 = !s;            /* not-s     */

        int premissas = p1 && p2 && p3;
        int conclusao = !c && !t;  /* not-c and not-t */

        if (premissas) {
            if (!conclusao) contraexemplo = 1;
        }
    }

    printf("------------------------------------------------------\n");
    if (!contraexemplo)
        printf("Resultado: A conclusão (not-c and not-t) É consequência lógica das premissas.\n");
    else
        printf("Resultado: A conclusão NÃO é consequência lógica (contraexemplo encontrado).\n");

    return 0;
}
