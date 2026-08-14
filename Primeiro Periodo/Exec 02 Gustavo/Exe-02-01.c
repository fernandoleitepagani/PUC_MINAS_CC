#include <stdio.h>
#include <stdlib.h>

float fatura(int consumo){
    float a;
    if (consumo <=5){
        a = consumo * 12;
    }
    else if(consumo > 5  && consumo <=15){
        a = 5 * 12 + (consumo -5) * 8;
    }
    else if (consumo > 15 && consumo <=20){
        a = (consumo -15)*5 +5*12 + 10*8;
    }
    else if (consumo > 20){
        a = 1.1*((consumo -15)*5 +5*12 + 10*8);
    }
    return a;
}

int main()
{
    int x, consumo;
    float arrecadado, faturatotal;
    faturatotal = 0;
    arrecadado=0;
    for (x=1;x<11 && consumo != 0;x++){
        printf("Cliente %i: ", x);
        scanf("%i",&consumo);
        faturatotal = fatura(consumo);
        if (faturatotal>150.00){
            faturatotal = faturatotal*0.8;
        }
        else{
            faturatotal = faturatotal;
        }
        arrecadado = faturatotal+arrecadado;
    }
    printf("Total arrecadado: R$%.2f",arrecadado);
    return 0;
}