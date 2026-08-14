/*
 * Premissas (instanciadas para Libélula e Aranha):
 *   P1a: I_Lib  entao S_Lib   (se libélula é inseto, tem 6 patas)
 *   P1b: I_Ara  entao S_Ara   (se aranha é inseto, tem 6 patas)
 *   P2:  I_Lib             (libélula é inseto)
 *   P3:  not-S_Ara            (aranha não tem 6 patas)
 *   P4:  Pred
 *
 * Conclusão inferida: (Libélula tem 6 patas E aranha não é inseto)
 *
 * Variáveis:
 *   il = I(Libélula), sl = S(Libélula)
 *   ia = I(Aranha),   sa = S(Aranha)
 *   pred = Pred(Aranha, Libélula)  — sempre verdadeiro como premissa
 */

#include <stdio.h>

int main() {
    int il, sl, ia, sa;
    int contraexemplo = 0;

    printf("=== Item D ===\n");
    for (il = 0; il <= 1; il++)
    for (sl = 0; sl <= 1; sl++)
    for (ia = 0; ia <= 1; ia++)
    for (sa = 0; sa <= 1; sa++) {
        int p1a = !il || sl;   /* I_Lib entao S_Lib */
        int p1b = !ia || sa;   /* I_Ara entao S_Ara */
        int p2  =  il;         /* I_Lib */
        int p3  = !sa;         /* not-S_Ara */
        /* P4 (predação) é sempre assumida verdadeira */

        int premissas = p1a && p1b && p2 && p3;
        int conclusao = sl && !ia;  /* S_Lib and not-I_Ara */

        if (premissas) {
            if (!conclusao) contraexemplo = 1;
        }
    }

    printf("------------------------------------------------------------\n");
    if (!contraexemplo)
        printf("Resultado: A conclusão (S_Libelula and not-I_Aranha) É consequência lógica das premissas.\n");
    else
        printf("Resultado: A conclusão NÃO é consequência lógica (contraexemplo encontrado).\n");

    return 0;
}
