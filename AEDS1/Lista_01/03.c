#include <stdio.h>

int main()
{
    int ano,idade;
    char aniversario;
    scanf("%d %c",&ano,&aniversario);
    idade = 2023-ano;
    if(aniversario =='N')
    {
       idade = idade-1;
    }
    if(idade>18)
    {
        printf("%d\nPode dirigir\n",idade);
    }
    if(idade<18)
    {
        printf("%d\nNao pode dirigir\n",idade);
    }
    return 0;
}