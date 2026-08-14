#include <stdio.h>

int busca_binaria(int *v, int inicio, int fim, int chave) {
    if (inicio > fim) {
        return -1;
    }

    int meio = inicio + (fim - inicio) / 2;

    if (v[meio] == chave) {
        return meio;
    } else if (v[meio] < chave) {
        return busca_binaria(v, meio + 1, fim, chave);
    } else {
        return busca_binaria(v, inicio, meio - 1, chave);
    }
}

int main(void) {
    int v[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(v) / sizeof(v[0]);
    int chave;

    printf("Vetor: ");
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");

    printf("Digite a chave a buscar: ");
    if (scanf("%d", &chave) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    int resultado = busca_binaria(v, 0, n - 1, chave);

    if (resultado != -1) {
        printf("Elemento %d encontrado no indice %d\n", chave, resultado);
    } else {
        printf("Elemento %d nao encontrado\n", chave);
    }

    return 0;
}
