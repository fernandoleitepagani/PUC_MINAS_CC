#include <stdio.h>
int main() {
    int m[2][2], soma = 0, i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++) {
            printf("m[%d][%d]: ", i, j);
            scanf("%d", &m[i][j]);
            soma += m[i][j];
        }
    printf("Soma: %d\n", soma);
    return 0;
}
