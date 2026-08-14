#include <stdio.h>
int main() {
    int m[2][3], soma, i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++) {
            printf("m[%d][%d]: ", i, j);
            scanf("%d", &m[i][j]);
        }
    for (i = 0; i < 2; i++) {
        soma = 0;
        for (j = 0; j < 3; j++)
            soma += m[i][j];
        printf("Soma linha %d: %d\n", i, soma);
    }
    return 0;
}
