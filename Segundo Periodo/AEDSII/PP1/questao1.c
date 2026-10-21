#include <string.h>
#include <stdio.h>

typedef struct Egresso{
  int periodo;
  char nome [51];
}Egresso;

void imprimir (Egresso e[], int n){
  for(int i=0; i<n;i++){
    printf("%d %s\n",e[i].periodo,e[i].nome);
  }
}

void insercao (Egresso e[], int n){
  for(int i=0;i<n;i++){
    int j=i-1;
    Egresso tmp = e[i];
    while(j>=0 && (e[j].periodo>tmp.periodo || e[j].periodo == tmp.periodo && strcmp(e[j].nome,tmp.nome)>0)){
      e[j+1]=e[j];
      j--;
    }
    e[j+1]=tmp;
  }
}


int main(){
  Egresso egressos[100];
  int n=0;
  while(scanf("%d %[^\n]",&egressos[n].periodo,egressos[n].nome)==2){ n++; }
  insercao(egressos, n);
  imprimir(egressos,n);
  return 0;
}
