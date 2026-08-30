#include <stdio.h>
#define MAX 30

// Retorna o comprimento da string
int sub_long_count(char *fs){
  // count  = maior comprimento ja encontrado
  // length = tamanho da string
  // bigger = comprimento da substring atual
  // found  = 1 se o tmp ja apareceu na janela, 0 se não
  
  int count = 0, length = 0, bigger; 
  char tmp;

  while (fs[length] != '\0') { length++; } // conta tamanho da string

  //Navega por cada posição até encontrar maior substring
  for (int j = 0; j < length; j++) {
    bigger=0; 
    for (int k = j; k < length; k++) {
      int found=0;
      tmp = fs[k];
      for (int p = j; p < k; p++) { if (fs[p] == tmp) found = 1; } // tmp já apareceu antes
      if (found == 1) k = length; //encerra, pois tmp já apareceu (parte para próximo)
      else bigger++; //aumenta tamnho se novo char
    }
    if (bigger > count) count = bigger; //atualiza maior comprimento encontrado
  }
  return count;
}

int main(){
  char fullString[MAX];

  //escanea até ler FIM
  while(scanf("%s",fullString)==1){
    if (fullString[0]=='F' && fullString[1]=='I' && fullString[2]=='M' && fullString[3]=='\0') return 0; 
    printf("%i\n",sub_long_count(fullString));
  }
  return 0;
}
