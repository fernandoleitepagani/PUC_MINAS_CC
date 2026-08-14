#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produtos{
	char nome[30];
	int quantidade;
	float preco;
};

int main() {
	struct Produtos produtos[];
	
	strcpy(produtos[0].nome,"TV");
	produtos[0].quantidade = 100;
	produtos[0].preco = 0.25;

	strcpy(produtos[1].nome, "Computador");
	produtod[1].quantidade = 50;
	produtos[1].preco = 1.5;

	strcpy(produtos[2].nome,"Monitor");
	produtod[2].quantidade = 200;
	produtos[2].preco = 0.80;

	for(int i=0; i<3; i++){
		printf("\nProdutos: %s",produtos[i].nome);
		printf("\nQuantidade: %s",produtos[i].quantidade);
		printf("\nPreco: %s",produtos[i].preco);
	}
	return 0;
}


