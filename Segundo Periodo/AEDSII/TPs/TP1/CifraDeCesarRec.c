#include <stdio.h>
#define MAX 400



//função recursiva
char* cifrarRec(char *s, int i){
    int key = 3; //chave ciframento
    if (s[i] == '\0') {          // para se chegar no fim da string
        return s;
    }
    else { 
        s[i] = (char)(s[i] + key);
        cifrarRec(s, i + 1);        // recursão
        return s;
    }
}

//contador
char* cifrar(char *s){
    return cifrarRec(s, 0);
}

int main(){
    int length = 0;
    char passwd[MAX];
    char scanned;
    while (1) {
        length = 0;
        // lê caractere por caractere até o '\n'
        while (scanf("%c", &scanned) == 1 && scanned != '\n') {
            if (length < MAX - 1) { 
                passwd[length] = scanned; 
                length++; 
            }
        }
        passwd[length] = '\0'; // fim da string
        // ser ler FIM, para
        if (passwd[0] == 'F' && passwd[1] == 'I' && passwd[2] == 'M' && passwd[3] == '\0') 
            return 0;
        printf("%s\n", cifrar(passwd));
    }

    return 0;
}
