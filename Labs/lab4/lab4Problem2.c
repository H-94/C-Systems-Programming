#include <stdio.h>
#include <string.h>

#define MAX_LINE 256
#define DEFAULT_FILE "userdata.txt"

int main(int argc, char *argv[]){
  char username[MAX_LINE],password[MAX_LINE];
  char file_username[MAX_LINE],file_password[MAX_LINE];
  double balance;
  FILE *file;
  char *file_name;

  if(argc > 1) file_name = argv[1];
  else file_name = DEFAULT_FILE;

  file = fopen(file_name,"r");
  if(file == NULL){
    printf("Could not open file %s\n",file_name);
    return 1;
  }

  printf("Enter username: ");
  scanf("%s",username);
  printf("Enter password: ");
  scanf("%s",password);

  while(fscanf(file,"%s %s %lf",file_username,file_password,&balance) != EOF){
    if(strcmp(username,file_username) == 0 && strcmp(password,file_password) == 0){
      printf("Balance: %.2lf\n",balance);
      fclose(file);
      return 0;
    }
  }

  printf("username/password mismatch!!!\n");
  fclose(file);
  return 0;
}
