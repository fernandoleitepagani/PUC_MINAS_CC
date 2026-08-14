#include <stdio.h>

void calcular(float nota1, float nota2, float *soma, float *media) {
    *soma = nota1 + nota2;
    *media = *soma / 2.0;
}

int main() {
    float nota1, nota2, soma, media;

    printf("Digite a primeira nota: ");
    scanf("%f", &nota1);

    printf("Digite a segunda nota: ");
    scanf("%f", &nota2);

    calcular(nota1, nota2, &soma, &media);

    printf("\nSoma das notas: %.2f\n", soma);
    printf("Media das notas: %.2f\n", media);

    return 0;
}
