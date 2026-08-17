#include <stdio.h>

int main(){
    char s1[50], s2[50], sf[100];
    while (scanf("%s %s",s1,s2)!=EOF){
	int i=0, j=0, k=0;
	while (s1[i]!='\0'||s2[j]!='\0'){
		if (s1[i]!='\0'){ sf[k] = s1[i];i++;k++;}
		if (s2[j]!='\0'){sf[k] = s2[j];j++;k++;} 
	}
        sf[k] = '\0';
	printf("%s\n",sf);
    }
    return 0;
}
