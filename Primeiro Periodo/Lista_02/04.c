#include <stdio.h>
#include <stdlib.h>
float fatorial (float N){
    int x=1;
    float F = N;
    while (x<N){
        F *= N-x;
        x++;
    }
    return F;
}
float divisao (float N){
    int x=0;
    float F, E=1;
    while ((N-x) != 0){
        F = fatorial(N-x);
        E += 1/(F);
        x++;
    }
    return E;
}
int main()
{
    float N,E;
    scanf("%f",&N);
    E = divisao(N);
    printf("%.2f",E);
    return 0;
}
