#include <stdio.h>

int sum(int scanned){
    int soma=0;
    while(scanned!=0){ soma += scanned%10; scanned/=10; }
    return soma;
}

int main(){
     /**variável do num recebido*/
    int scan; 
    //int first=1; /**adicionar pois no pub.out dá erro o fato de ter um \n na última resposta*/
    while(scanf("%i",&scan)!=EOF){
	printf("%i\n",sum(scan)); 
    }
    return 0;
}
