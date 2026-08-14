#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a, *b;

    a = (int *) malloc(sizeof(int));
    b = (int *) malloc(sizeof(int));

    if (a == NULL || b == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return 1;
    }

    printf("Digite o primeiro valor inteiro: ");
    scanf("%d", a);

    printf("Digite o segundo valor inteiro: ");
    scanf("%d", b);

    printf("\nPrimeiro valor: %d | Endereco: %p\n", *a, (void *)a);
    printf("Segundo valor:  %d | Endereco: %p\n", *b, (void *)b);

    if (a == b)
        printf("\nOs enderecos sao IGUAIS.\n");
    else
        printf("\nOs enderecos sao DIFERENTES.\n");

    free(a);
    free(b);
    a = NULL;
    b = NULL;

    return 0;
}
