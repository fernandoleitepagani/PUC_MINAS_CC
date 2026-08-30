#include <stdint.h>
#include <stdio.h>
#define MAX 30
const char yes[4] = {'S','I','M','\0'};
const char no[4] = {'N','A','O','\0'};

// converte letra maiuscula para minuscula usando ASCII
char lower_case(char c){
    if(c >= 'A' && c <= 'Z'){ c = c - 'A' + 'a'; }
    return c;
}

// verifica se as strings são anagramas uma das outras
void verify_strings(char* scanned, char* verify){
    int count[26] = {0};
    int TrueFalse = 1;
    int i = 0, j = 0;

    // conta letras de scanned
    while(scanned[i] != '\0'){
      char c = lower_case(scanned[i]); // pega a letra poe em minuscula
      int k = c - 'a';         // calcula a posicao no array
      count[k]++;                 
      i++;
    }

    // conta letras de verify 
    while(verify[j] != '\0'){
      char c = lower_case(verify[j]); 
      int l = c - 'a';         
      count[l]--;                  
      j++;
    }
    // tamanhos diferentes, logo, NAO
    if(i != j) TrueFalse = 0; i = 0;
    
    // sobrou letra
    while(i < 26){ if(count[i] != 0) TrueFalse = 0; i++; }
    if(TrueFalse == 1) printf("%s\n", yes);
    else printf("%s\n", no);
}

int main(){
  char scanned[MAX];  
  char verify[MAX]; 

  // Le enquanto tem entrada válida. Para no FIM
  while(scanf("%s",scanned)==1){
    if (scanned[0]=='F' && scanned[1]=='I' && scanned[2]=='M' && scanned[3]=='\0') return 0; 
    scanf("%s",verify);

    // Verifica e imprime
    verify_strings(scanned,verify);
  }
  return 0;
}
