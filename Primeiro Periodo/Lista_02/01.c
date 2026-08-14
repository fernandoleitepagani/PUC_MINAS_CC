#include <stdio.h>

int main()
{
    long int num,x,N, positivo, negativo, zero;
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
    }
    printf("%ld POSITIVOS\n", positivo);
    printf("%ld NEGATIVOS\n", negativo);
    printf("%ld ZEROS", zero);
    return 0;
}
