#include <stdio.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    printf("Digite o primeiro numero: ");
    scanf("%d", &x);

    printf("Digite o segundo numero: ");
    scanf("%d", &y);

    printf("\nValores antes da troca: x = %d, y = %d\n", x, y);

    trocar(&x, &y);

    printf("Valores depois da troca: x = %d, y = %d\n", x, y);

    return 0;
}
