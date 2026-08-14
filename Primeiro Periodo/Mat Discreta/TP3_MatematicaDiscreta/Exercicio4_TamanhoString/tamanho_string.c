#include <stdio.h>

int tamanho_string(char *s) {
    if (*s == '\0') {
        return 0;
    }
    return 1 + tamanho_string(s + 1);
}

int main(void) {
    char str[256];

    printf("Digite uma string:");
    if (scanf("%255s", str) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    printf("Tamanho da string \"%s\": %d\n", str, tamanho_string(str));

    return 0;
}
