#include <stdio.h>

void ajustarTemperatura(float *temperatura, float ajuste) {
    *temperatura += ajuste;
}

int main() {
    float temperatura, ajuste;

    printf("Digite a temperatura atual: ");
    scanf("%f", &temperatura);

    printf("Digite o valor de ajuste (positivo ou negativo): ");
    scanf("%f", &ajuste);

    printf("\nTemperatura antes do ajuste: %.2f\n", temperatura);

    ajustarTemperatura(&temperatura, ajuste);

    printf("Temperatura depois do ajuste: %.2f\n", temperatura);

    return 0;
}
