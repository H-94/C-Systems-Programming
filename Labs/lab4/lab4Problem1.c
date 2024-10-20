#include <stdio.h>
#include <ctype.h>

int main(int argc,char *argv[]){
  if(argc != 2){
    printf("%s filename\n",argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1],"r");
  if(fp == NULL){
    printf("Error %s\n",argv[1]);
    return 2;
  }

  char arr[11];
  int count = 0;
  int flag = 0;
  char c = fgetc(fp);

  while(c != EOF){
    if(isprint(c)){
      arr[count] = c;
        count++;
        flag = 0;
    }else{
      if(flag == 0){
        arr[count] = '.';
        count++;
        flag = 1;
      }
    }
    if(count == 10){
      arr[count] = '\0';
      printf("%s\n", arr);
      count = 0;
    }
    c = fgetc(fp);
  }

  if(count > 0){
    arr[count] = '\0';
    printf("%s\n", arr);
  }

  fclose(fp);
  return 0;
}
