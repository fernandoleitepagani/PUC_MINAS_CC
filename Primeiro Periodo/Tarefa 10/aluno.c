#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Aluno{
	char nome[30];
	int idade;
	float nota;
}

int main(){
	struct Aluno aluno;

	strcpy(aluno.nome,"Bernardo");
	aluno.idade = 15;
	aluno.nota = 10.00;

	printf("%s",aluno.nome);
	printf("%i",aluno.idade);
	printf("%.2f",aluno.nota);

	return 0;
}
