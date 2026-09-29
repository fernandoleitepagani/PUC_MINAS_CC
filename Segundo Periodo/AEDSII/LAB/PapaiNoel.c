#include <stdio.h>
#include <string.h>


int main(){
  int good=0,bad=0,N;
  char behavior, array[100][21];

  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    scanf(" %c %s", &behavior, array[i]);
    if (behavior == '+') good++;
    else bad++;
  }
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if(strcmp(array[i],array[j])>0){
	char tmp[21];
	strcpy(tmp,array[i]);
	strcpy(array[i],array[j]);
	strcpy(array[j],tmp);
      }
    }
  }
  
  for (int i=0;i<N;i++)printf("%s\n",array[i]);
  printf("Se comportaram: %d | Nao se comportaram: %d\n",good,bad);
  return 0;
}
