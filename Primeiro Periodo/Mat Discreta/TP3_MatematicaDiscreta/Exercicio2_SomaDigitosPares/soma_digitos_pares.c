#include <stdio.h>

int soma_digitos_pares(int n) {
    if (n < 10) {
        if (n % 2 == 0) {
            return n;
        } else {
            return 0;
        }
    }

    int ultimo_digito = n % 10;
    int resto = n / 10;

    if (ultimo_digito % 2 == 0) {
        return ultimo_digito + soma_digitos_pares(resto);
    } else {
        return soma_digitos_pares(resto);
    }
}

int main(void) {
    int n;

    printf("Digite um numero inteiro nao negativo: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida.\n");
        return 1;
    }

    printf("Soma dos digitos pares de %d: %d\n", n, soma_digitos_pares(n));

    return 0;
}
