// Para esse exercício: False = 0 e True = 1

#include <stdio.h>
#define MAX 400

//Escaneia caracter por caracter e constroi a string (fiz por causa dos espaços que dava erro)
char* scan_string(char* scanned){
  int size=0; char c; int result = scanf("%c", &c);

  //cria a string a partir dos caracteres
  while (result == 1 && c != '\n') {
    scanned[size] = c;
    size++;
    result = scanf("%c", &c);
  }
  //Acaba se ler FIM
  if (size == 3 && scanned[0]=='F' && scanned[1]=='I' && scanned[2]=='M') return NULL;
  else {scanned[size]='\0'; return scanned;}
}

//verifica se é vogal
int isVogals(char *s){
  char t = *s;
  if (t== '\0') return 1; // fim ,só achou vogais

  //se não for vogal, return 0
  if (t != 'a' && t != 'e' && t != 'i' && t != 'o' && t != 'u' &&
      t != 'A' && t != 'E' && t != 'I' && t != 'O' && t != 'U') { return 0; }

  return isVogals(s + 1); // Recursividade -> até acabar string
}

//verifica se é consoante 
int notVogals(char *s){
  char t = *s;
  if (t == '\0') return 1; // fim 

  // checa se é uma letra
  if(!((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z'))) return 0;

  // checa se é vogal
  if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u' || t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U') { return 0; }

  return notVogals(s+1); // Recursividade -> até acabar string
}

//verifica se é inteiro 
int intNumber(char *s){
  char t = *s;
  if (t== '\0') return 1; // fim 

  //se algum nao for numero, false
  if (t != '0' && t != '1' && t != '2' && t != '3' && t != '4' &&
      t != '5' && t != '6' && t != '7' && t != '8' && t != '9') { return 0; }

  return intNumber(s + 1); // Recursividade -> até acabar string
}

//verifica se é real 
int realNumber(char *s){
  char t = *s;
  int result;

  if (t== '\0') return 1; // fim

  if (t == '.' || t == ','){
    result = realNumber(s + 1);

    if (result == 2) return 0;
    else if (result == 1) return 2;
    else return 0;
  }

  if (t < '0' || t > '9') return 0;

  return realNumber(s + 1); // Recursividade -> até acabar string
}


int main(){
  char scanned[MAX];
  while (scan_string(scanned) != NULL) {
    //imprime resposta baseado no valor das funções
    if(isVogals(scanned)==1) printf("SIM");
    else printf("NAO");

    if(notVogals(scanned)==1) printf(" SIM");
    else printf(" NAO");

    if(intNumber(scanned)==1) printf(" SIM");
    else printf(" NAO");

    if(realNumber(scanned)!=0) printf(" SIM");
    else printf(" NAO");

    printf("\n");
  }
  return 0;
}

