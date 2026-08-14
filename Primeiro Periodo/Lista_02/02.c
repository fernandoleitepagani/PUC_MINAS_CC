#include <stdio.h>

int main()
{
    long int num,x,N, positivo, negativo, zero;
    float total;
    scanf("%ld",&N);
    for (x=0;x<N;x++){
        scanf("%ld",&num);
        if (num == 0){
            zero++;
        }
        else if (num > 0){
            positivo++;
        }
        else if (num < 0){
            negativo++;
        }
        total++;
    }
    positivo = positivo/total *100;
    negativo = negativo/total *100;
    zero = zero/total *100;
    printf("%ld%% POSITIVOS\n", positivo);
    printf("%ld%% NEGATIVOS\n", negativo);
    printf("%ld%% ZEROS", zero);
    return 0;
}
