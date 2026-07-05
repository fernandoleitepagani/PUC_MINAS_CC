#include <stdio.h>
int main() {
    int m[3][3], maior, i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            printf("m[%d][%d]: ", i, j);
            scanf("%d", &m[i][j]);
        }
    maior = m[0][0];
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (m[i][j] > maior)
                maior = m[i][j];
    printf("Maior: %d\n", maior);
    return 0;
}
