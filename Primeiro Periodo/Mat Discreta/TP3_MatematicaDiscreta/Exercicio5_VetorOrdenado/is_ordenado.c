#include <stdio.h>

int is_ordenado(int *v, int n) {
    if (n <= 1) {
        return 1;
    }
    if (v[n - 2] > v[n - 1]) {
        return 0;
    }
    return is_ordenado(v, n - 1);
}

int main(void) {
    int v1[] = {1, 2, 3, 4, 5};
    int v2[] = {1, 5, 2, 4, 3};

    int n1 = sizeof(v1) / sizeof(v1[0]);
    int n2 = sizeof(v2) / sizeof(v2[0]);

    printf("v1 esta ordenado? %s\n", is_ordenado(v1, n1) ? "Sim" : "Nao");
    printf("v2 esta ordenado? %s\n", is_ordenado(v2, n2) ? "Sim" : "Nao");

    return 0;
}
