#include <stdio.h>

// retorna a soma dos dígitos
int sum(int scanned){
    int soma=0;
    while(scanned!=0){ soma += scanned%10; scanned/=10; }
    return soma;
}

int main(){
    //Le numero escaneado
    int scan; 

    // Le ate o End Of File
    while(scanf("%i",&scan)!=EOF){
	printf("%i\n",sum(scan)); 
    }
    return 0;
}
