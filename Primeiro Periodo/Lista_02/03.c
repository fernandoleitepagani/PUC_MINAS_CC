#include <stdio.h>

int main()
{
    long int num,x,num39,num5,num2;
    for (x=0;x<10;x++){
        scanf("%ld",&num);
        if (num%3 == 0 && num%9 == 0){
            num39++;
        }
        else if (num%5 == 0){
            num5++;
        }
        else if (num%2 == 0){
            num2++;
        }
        else{
            printf("Numero nao eh divisivel pelos valores\n");
        }
    }
    printf("%ld Numeros sao divisiveis por 3 e por 9\n",num39);
    printf("%ld Numeros sao divisiveis por 2\n", num2);
    printf("%ld Numeros sao divisiveis por 5\n", num5);
    return 0;
}
