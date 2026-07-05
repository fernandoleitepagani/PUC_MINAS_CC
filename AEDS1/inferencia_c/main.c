/*
 * Item C - Avaliação de Conclusões e Inferência
 *
 * Premissas:
 *   P1: j → d   (jogar futebol → dolorido)
 *   P2: d → p   (dolorido → usar piscina)
 *   P3: ¬p      (não usou a piscina)
 *
 * Conclusão inferida: ¬j ∧ ¬d
 *   (Não jogou futebol E não estava dolorido)
 */

#include <stdio.h>

int main() {
    int j, d, p;
    int contraexemplo = 0;

    printf("=== Item C ===\n");
    for (j = 0; j <= 1; j++)
    for (d = 0; d <= 1; d++)
    for (p = 0; p <= 1; p++) {
        int p1 = !j || d;   /* j entao d */
        int p2 = !d || p;   /* d entao p */
        int p3 = !p;        /* not-p    */

        int premissas = p1 && p2 && p3;
        int conclusao = !j && !d;  /* mot-j and not-d */

        if (premissas) {
            if (!conclusao) contraexemplo = 1;
        }
    }

    printf("------------------------------------------------------\n");
    if (!contraexemplo)
        printf("Resultado: A conclusão (not-j and not-d) É consequência lógica das premissas.\n");
    else
        printf("Resultado: A conclusão NÃO é consequência lógica (contraexemplo encontrado).\n");

    return 0;
}
