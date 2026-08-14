#include <stdio.h>

int mdc(int a, int b) {
    if (b == 0) {
        return a;
    }
    return mdc(b, a % b);
}

int main(void) {
    int a, b;

    printf("Digite dois inteiros a e b, com a >= b >= 0: ");
    if (scanf("%d %d", &a, &b) != 2 || a < b || b < 0) {
        printf("Entrada invalida.\n");
        return 1;
    }

    printf("MDC(%d, %d) = %d\n", a, b, mdc(a, b));

    return 0;
}
