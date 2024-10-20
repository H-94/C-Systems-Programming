#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
  int n = atoi(argv[1]);
  int length = 2*n-1;
  int minimum,minimum1,minimum2;

  if(n<1||n>9){
    printf("1-9\n");
    return 1;
  }

  for(int i=0;i<length;i++){
    for(int j=0;j<length;j++){
      minimum1=i<=length-i?i:length-i-1;
      minimum2=j<=length-j?j:length-j-1;
      minimum=minimum1<=minimum2?minimum1:minimum2;
      printf("%d ",n-minimum);
    }
    printf("\n");
  }

  return 0;
}
