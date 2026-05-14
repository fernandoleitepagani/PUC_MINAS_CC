#include <stdio.h>

int main()
{
    int num1,num2;
    scanf("%i%i",&num1,&num2);
    int soma = num1 + num2;
    if (soma > 10) {
        soma = soma +5;
        printf("%i\n",soma);
    }
    else {
        soma = soma+7;
        printf("%i\n",soma);
    }
    return 0;
}