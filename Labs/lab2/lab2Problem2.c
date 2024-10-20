#include <stdio.h>
#include <stdlib.h>

long long factorial(int n){
  long long fact = 1;
  for(int i=2;i<=n;i++) fact *= i;
  return fact;
}

long long permutation(int n,int r){
  return factorial(n)/factorial(n-r);
}

long long combination(int n,int r){
  return permutation(n,r)/factorial(r);
}

int main(int argc,char *argv[]){
  int n = atoi(argv[1]);
  int r = atoi(argv[2]);
  
  if(n<1||n>20||r<1||r>20){
    printf("1-20");
    return 1;
  }

  printf("P(%d,%d) = %llu\n",n,r,permutation(n,r));
  printf("C(%d,%d) = %llu\n",n,r,combination(n,r));

  return 0;
}
