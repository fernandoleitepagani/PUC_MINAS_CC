#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Turma{
	char nome[30];
	char professor[50];
	int quantidadeAlunos;
};

int main(){
	struct Turma turma;

	strcpy(turma.nome,"Matemática");
	strcpy(turma.professor,"Eduardo");
	turma.quantidadeAlunos = 30;

	printf("%s",turma.nome);
	printf("%s",turma.professor);
	printf("%i",turma.quantidadeAlunos);

	return 0;
}
	
