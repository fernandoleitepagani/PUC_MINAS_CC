#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;

    p = (int *) malloc(sizeof(int));
    if (p == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return 1;
    }

    printf("Digite um valor inteiro: ");
    scanf("%d", p);

    printf("\nValor armazenado: %d\n", *p);
    printf("Endereco da variavel ponteiro (p): %p\n", (void *)&p);
    printf("Endereco da memoria alocada (*p): %p\n", (void *)p);

    free(p);
    p = NULL;

    return 0;
}
