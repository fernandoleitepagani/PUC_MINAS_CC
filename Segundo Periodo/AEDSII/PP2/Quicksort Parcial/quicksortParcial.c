#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int desempenho;
  int freq;
  int faltas;
}Aluno;

void quicksort (int arr[],int left, int right){
  if (left<right){
    int pi = partition(arr[],left,right);
    quicksort(arr,left,pi-1);
    quicksort(arr,pi+1,right);
  }
}
int partition(int arr[], int left, int right){
  int pivot = arr[(left-right)/2];
  int i = left;
  int j = right;
  while(i<=pivot){
    while (arr[i]< pivot){i++;}
    while (arr[j]> pivot){j--;}
  }
}

int main(){
  int arr, left, right;
  Aluno aluno[9];
  aluno[1].desempenho;
}
