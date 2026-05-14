#include <stdio.h>

int main ()
{
    char var;
    float salario;
    printf("Opcao: ");
    scanf("%c",&var);
    printf("Salario atual: ");
    scanf("%f",&salario);
    switch (var){
        case "A":
            salario = salario*1.08;
            printf("%.2f\n",salario);
            break;
        case "B":
            salario = salario*1.11;
            printf("%.2f\n",salario);
            break;
        case "C":
            if (salario <= 1000){
                salario = salario +350.00;
                printf("%.2f\n",salario);
            }
            else {
                salario = salario +200.00;
                printf("%.2f\n",salario);
            }
            break;
    }
    return  0;
}