#include <stdio.h>
#include <stdlib.h>

int main() {
    int *vetor, *aux;
    int n, m, i;

    printf("Digite o numero inicial de valores (n): ");
    scanf("%d", &n);

    vetor = (int *) malloc(n * sizeof(int));
    if (vetor == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return 1;
    }

    printf("Digite os %d valores:\n", n);
    for (i = 0; i < n; i++) {
        printf("  Valor[%d]: ", i);
        scanf("%d", &vetor[i]);
    }

    printf("\nDigite o novo tamanho do vetor (m > %d): ", n);
    scanf("%d", &m);

    if (m <= n) {
        printf("Erro: m deve ser maior que n.\n");
        free(vetor);
        return 1;
    }

    aux = (int *) realloc(vetor, m * sizeof(int));
    if (aux == NULL) {
        printf("Erro: falha no realloc.\n");
        free(vetor);
        return 1;
    }
    vetor = aux;

    printf("Digite os %d novos valores:\n", m - n);
    for (i = n; i < m; i++) {
        printf("  Valor[%d]: ", i);
        scanf("%d", &vetor[i]);
    }

    printf("\nTodos os elementos do vetor:\n");
    for (i = 0; i < m; i++) {
        printf("  vetor[%d] = %d\n", i, vetor[i]);
    }

    free(vetor);
    vetor = NULL;

    return 0;
}
