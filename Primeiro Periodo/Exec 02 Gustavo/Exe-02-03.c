#include <stdio.h>

int destaque (float nota1, float nota2,float nota3,float nota4,float nota5){
    if (nota1 >= 5.0 && nota2 >= 5.0 && nota3 >= 6.0 && nota4 >= 6.0 && nota5 >=7.0)
        return 1;
    else
        return 0;
}

int main() {
    int x, distincao;
    float nota1, nota2, nota3, nota4, nota5, avg, avg_final, total;
    total = 0;
    avg_final = 0;
    distincao = 0;

    for (x=1;x<=8;x++){
        printf("\nAluno %i\n",x);
        printf("Nota 1: ");
        scanf ("%f",&nota1);
        if (nota1 != -1){
            printf("Nota 2: ");
            scanf ("%f",&nota2);
            printf("Nota 3: ");
            scanf ("%f",&nota3);
            printf("Nota 4: ");
            scanf ("%f",&nota4);
            printf("Nota 5: ");
            scanf ("%f",&nota5);
            avg = (nota1+(2.0*nota2)+(3.0*nota3)+(4.0*nota4)+(5.0*nota5))/(15.0);
            total = total + avg;
            distincao = distincao + destaque(nota1,nota2,nota3,nota4,nota5);
            avg_final = total/(8.0);
        }
        else{
            break;
        }
    }
    printf("Media Geral: %.2f\n",avg_final);
    printf("Aprovados com Distincao: %i alunos",distincao);
}
