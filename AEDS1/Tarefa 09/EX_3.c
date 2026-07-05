#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[100];
    int idade;
    float peso;
} Paciente;

int main() {
    Paciente p;

    printf("Nome: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &p.idade);

    printf("Peso: ");
    scanf("%f", &p.peso);

    printf("\n--- Dados do Paciente ---\n");
    printf("Nome: %s\nIdade: %d\nPeso: %.2f kg\n", p.nome, p.idade, p.peso);
    return 0;
}
