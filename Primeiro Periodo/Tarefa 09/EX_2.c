#include <stdio.h>
#include <string.h>

int main() {
    char nome[100];

    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);

    nome[strcspn(nome, "\n")] = '\0';

    printf("Quantidade de caracteres: %zu\n", strlen(nome));
    return 0;
}
