#include <stdio.h>
#include <stdlib.h>

int main() {
    float *temps, *aux;
    float valor, maior, soma;
    int count, i;

    count = 0;
    temps = NULL;

    printf("Digite temperaturas uma a uma. Valor negativo encerra.\n\n");

    while (1) {
        printf("Temperatura[%d]: ", count);
        scanf("%f", &valor);

        if (valor < 0)
            break;

        aux = (float *) realloc(temps, (count + 1) * sizeof(float));
        if (aux == NULL) {
            printf("Erro: falha ao alocar memoria.\n");
            free(temps);
            return 1;
        }
        temps = aux;

        temps[count] = valor;
        count++;
    }

    if (count == 0) {
        printf("Nenhuma temperatura registrada.\n");
        return 0;
    }

    maior = temps[0];
    soma  = 0.0f;
    for (i = 0; i < count; i++) {
        soma += temps[i];
        if (temps[i] > maior)
            maior = temps[i];
    }

    printf("Temperaturas registradas:\n");
    for (i = 0; i < count; i++) {
        printf("  [%d] %.2f\n", i, temps[i]);
    }
    printf("Maior temperatura: %.2f\n", maior);
    printf("Media das temperaturas: %.2f\n", soma / count);

    free(temps);
    temps = NULL;

    return 0;
}
