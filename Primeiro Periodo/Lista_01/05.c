#include <stdio.h>

int main()
{
    float  diaria;
    scanf("%f",&diaria);
    float a1 = diaria*0.75;
    float a2 = a1*64.0;
    float a3 = diaria*40.0;
    float a4 = a2 - a3;
    printf("Valor promocional: %.2f\n",a1);
    printf("Promocional com 80%% ocupado: %.2f\n",a2);
    printf("Normal com 50%% ocupado: %.2f\n",a3);
    printf("Diferença entre os valores: %.2f\n",a4);
}