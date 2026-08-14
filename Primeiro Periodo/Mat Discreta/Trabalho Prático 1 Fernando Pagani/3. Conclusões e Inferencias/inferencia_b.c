/*
 * Item B - Avaliação de Conclusões e Inferência
 *
 * Premissas (instanciadas para Ralph e Ann):
 *   P1a: C_Ralph entao P_Ralph  (se Ralph é cientista, tem computador)
 *   P1b: C_Ann  entao P_Ann    (se Ann é cientista, tem computador)
 *   P2:  not-P_Ralph            (Ralph não tem computador)
 *   P3:   P_Ann              (Ann tem computador)
 *
 * Conclusão inferida: not-C_Ralph
 *   (Ralph não é cientista da computação)
 *   nada se pode concluir sobre Ann ser ou não cientista.
 *
 * Variáveis booleanas:
 *   cr = C(Ralph), pr = P(Ralph)
 *   ca = C(Ann),   pa = P(Ann)
 */

#include <stdio.h>

int main() {
    int cr, pr, ca, pa;
    int contraexemplo = 0;

    printf("=== Item B ===\n");

    for (cr = 0; cr <= 1; cr++)
    for (pr = 0; pr <= 1; pr++)
    for (ca = 0; ca <= 1; ca++)
    for (pa = 0; pa <= 1; pa++) {
        int p1a = !cr || pr;  /* C_Ralph entao P_Ralph */
        int p1b = !ca || pa;  /* C_Ann  entao P_Ann   */
        int p2  = !pr;        /* not-P_Ralph */
        int p3  =  pa;        /* P_Ann    */

        int premissas = p1a && p1b && p2 && p3;
        int conclusao = !cr;  /* not-C_Ralph */

        if (premissas) {
            if (!conclusao) contraexemplo = 1;
        }
    }

    printf("--------------------------------------------------------------\n");
    if (!contraexemplo)
        printf("Resultado: A conclusão (not-C_Ralph) É consequência lógica das premissas.\n");
    else
        printf("Resultado: A conclusão NÃO é consequência lógica (contraexemplo encontrado).\n");

    return 0;
}
