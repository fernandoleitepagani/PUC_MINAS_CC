#include <stdio.h>
#include <stdlib.h>

void ordem(int *x, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (x[i] > x[j]) {
                int muda = x[i];
                x[i] = x[j];
                x[j] = muda;
            }
}
 
int main() {
    int x[4];
    scanf("%i %i %i %i",&x[0],&x[1],&x[2],&x[3]);
    ordem(x, 4);
    int total = x[3];
    int a = total - x[2];
    int b = total - x[1];
    int c = total - x[0];
    printf("%i %i %i\n",a,b,c);
    return 0;
}

