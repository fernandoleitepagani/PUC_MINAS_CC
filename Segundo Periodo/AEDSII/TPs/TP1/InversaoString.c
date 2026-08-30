#include <stdio.h>
#define MAX 100
int size=0; // tamanho da ultima string lida

// le uma linha caractere a caractere; retorna NULL se for "FIM"
char* scan_string(char* scanned){
  size = 0; char c; char result = scanf("%c", &c);
  while (result == 1 && c != '\n') {
    scanned[size] = c;
    size++;
    result = scanf("%c", &c);
  }
  if (scanned[0]=='F' && scanned[1]=='I' && scanned[2]=='M') return NULL;
  else {scanned[size]='\0'; return scanned;}
}

// inverte a string e guarda o resultado
char* invert_string(char* scanned, char* inverted){
  int j = 0;
  for (int k = size-1; k >= 0; k--, j++) inverted[j] = scanned[k];
  inverted[j]='\0';
  return inverted;
}

int main(){
  char scanned[MAX],inverted[MAX];

  // le e inverte cada linha ate encontrar "FIM"
  while (scan_string(scanned) != NULL) { printf("%s\n", invert_string(scanned, inverted)); }
  return 0;
}
