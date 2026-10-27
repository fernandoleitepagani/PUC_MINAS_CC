#include <stdio.h>
#include <stdlib.h>


int main(){
  quicksort(a, 0, n - 1);
  quicksortParcial(a, 0, n - 1, k);
  mergesort(a, 0, n - 1);
  return 0;
}




































void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int tmp = a[i], j = i - 1;

        while (j >= 0 && a[j] > tmp) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = tmp;
    }
}

void quicksortParcial(int a[], int esq, int dir, int k) {
    int i = esq, j = dir, pivo = a[(esq + dir) / 2];

    while (i <= j) {
        while (a[i] < pivo) i++;
        while (a[j] > pivo) j--;

        if (i <= j) {
            int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
            i++; j--;
        }
    }

    if (esq < j) quicksortParcial(a, esq, j, k);
    if (i < k && i < dir) quicksortParcial(a, i, dir, k);
}

void quicksort(int a[], int esq, int dir) {
    int i = esq, j = dir, pivo = a[(esq + dir) / 2];

    while (i <= j) {
        while (a[i] < pivo) i++;
        while (a[j] > pivo) j--;

        if (i <= j) {
            int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
            i++; j--;
        }
    }

    if (esq < j) quicksort(a, esq, j);
    if (i < dir) quicksort(a, i, dir);
}


void merge(int a[], int esq, int meio, int dir) {
    int tmp[dir - esq + 1];
    int i = esq, j = meio + 1, k = 0;

    while (i <= meio && j <= dir)
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];

    while (i <= meio) tmp[k++] = a[i++];
    while (j <= dir)  tmp[k++] = a[j++];

    for (i = esq, k = 0; i <= dir; i++, k++)
        a[i] = tmp[k];
}
void mergesort(int a[], int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;

        mergesort(a, esq, meio);
        mergesort(a, meio + 1, dir);
        merge(a, esq, meio, dir);
    }
}
