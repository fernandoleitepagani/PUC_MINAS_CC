#include <stdio.h>

float fatura(int consumo,float hour){
    float a;
    if (consumo <=100){
        a = consumo * 0.50;
    }
    else if(consumo > 100  && consumo <=300){
        a = 100 * 0.50 + (consumo -100) * 0.75;
    }
    else if (consumo > 300 && consumo <=500){
        a = (consumo -300)*1.20 +100*0.50 + 200*0.75;
    }
    else if (consumo > 500){
        a = (consumo -500)*1.80 + 200*1.20 + 100*0.50 + 200*0.75;
    }
    if (hour <= 21 || hour >= 18){
        a *= 1.20;
    }
    else{
        a = a;
    }
    if (a>700){
        a *= 0.88;
    }
    else if (a>400 && a<= 700){
        a *= 1.08;
    }
    else{
        a = a;
    }
    return a;
}

float fatura_maior(float b1,float b2,float b3,float b4,float b5){
    if (b1>b2 && b1>b3 && b1>b4 && b1>b5){
        return b1;
    }
    else if (b2>b1 && b2>b3 && b2>b4 && b2>b5){
        return b2;
    }
    else if (b3>b2 && b3>b1 && b3>b4 && b3>b5){
        return b3;
    }
    else if (b4>b1 && b4>b2 && b4>b3 && b4>b5){
        return b4;
    }
    else {
        return b5;
    }
}

int main () {
    int x, consumo;
    consumo = 1;
    float fatura_cliente = 0;
    float fatura_total = 0;
    float hour,a1,a2,a3,a4,a5,maior_fatura;
    for (x=1;x<6 && consumo != 0;x++){
        printf("Consumo Cliente %i(em Kwh): ",x);
        scanf("%i",&consumo);
        printf("Horário em que ocorreu o consumo: ");
        scanf("%f",&hour);
        fatura_cliente = fatura(consumo,hour);
        if (x==1){
            a1 = fatura_cliente;
        }
        else if (x==2){
            a2 = fatura_cliente;
        }
        else if (x==3){
            a3 = fatura_cliente;
        }
        else if (x==4){
            a4 = fatura_cliente;
        }
        else {
            a5 = fatura_cliente;
        }
    }
    maior_fatura=fatura_maior(a1,a2,a3,a4,a5);
    printf("Maior Fatura: R$%.2f",maior_fatura);
    return 0;
}
