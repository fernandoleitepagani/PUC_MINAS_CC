#include <stdio.h>

int main() {
    int mat[3][3], soma = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            printf("mat[%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }

    for (int i = 0; i < 3; i++)
        soma += mat[i][i];

    printf("Soma da diagonal principal: %d\n", soma);
    return 0;
}
