#include <stdio.h>

int main ()
{
    float x,y;
    printf("Valor de X: ");
    scanf("%f",&x);
    if (x<=1){
        y = 1;
        printf("%.2f\n",y);
    }
    else if (x>1 && x<= 2){
        y = 2;
        printf("%.2f\n",y);
    }
    else if (x>2 && x<=3){
        y = x*x;
        printf("%.2f\n",y);
    }
    else{
        y = x*x*x;
        printf("%.2f\n",y);
    }
    return 0;
}