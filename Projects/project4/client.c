#include "csapp.h"

// display menu options
void displayMenu(){
  printf("(1) Add record\n");
  printf("(2) Search by Name\n");
  printf("(3) Search by Zip Code\n");
  printf("(4) Search by Salary\n");
  printf("(5) Terminate\n");
  printf("Select an option [1,2,3,4 or 5]: ");
}

int main(int argc,char *argv[]){
  int clientfd;  //file descriptor to communicate with the server
  char *host, *port;
  size_t n;

  char buffer [MAXLINE]; //MAXLINE = 8192 defined in csapp.h
  char input  [MAXLINE];

  bzero(buffer,MAXLINE); 
  if (argc != 3)
  {
      fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	  exit(0);
  }

  host = argv[1];
  port = argv[2];

  clientfd = Open_clientfd(host, port);

  int option;

  displayMenu();

  // Read option
  fgets(input,sizeof(input),stdin);
  sscanf(input,"%d",&option);

  // main loop to handle user interation
  while(1){
    // add record
    if(option == 1){ 
      printf("\n");
      char first_name[MAXLINE];
      char last_name[MAXLINE];
      char department[MAXLINE];
      char zip_code[MAXLINE];
      char salary[MAXLINE];
      char option[] = "1";    
      n = write(clientfd,option,strlen(option));
      printf("Enter First Name: ");
      fgets(first_name,sizeof(first_name),stdin);  // Read first name
      strtok(first_name,"\n");
      n = write(clientfd,first_name,strlen(first_name));
      printf("Enter Last Name: ");
      fgets(last_name,sizeof(last_name),stdin);  // Read last name
      strtok(last_name,"\n");
      n = write(clientfd,last_name,strlen(last_name));
      printf("Enter Zip Code: ");
      fgets(zip_code,sizeof(zip_code),stdin);  // Read zip code
      strtok(zip_code,"\n");
      n = write(clientfd,zip_code,strlen(zip_code));
      printf("Enter department: ");
      fgets(department,sizeof(department),stdin);  // Read department
      strtok(department,"\n");
      n = write(clientfd,department,strlen(department));
      printf("Enter Salary: ");
      fgets(salary,sizeof(salary),stdin);  // Read salary
      strtok(salary,"\n");
      n = write(clientfd,salary,strlen(salary));
      printf("Message from the server:\n");
      n = read(clientfd,buffer,MAXLINE);
      printf("%s\n",buffer);
      bzero(buffer,MAXLINE);
      if(n<0) perror("Error!!");
    // search by name
    }else if(option == 2){
      printf("\n");
      char first_name [MAXLINE];
      char last_name [MAXLINE];
      char option[] = "2";
      n = write(clientfd,option,strlen(option));
      printf("Enter First Name: ");
      scanf("%s",first_name);
      getchar();
      n = write(clientfd,first_name,strlen(first_name));
      printf("Enter Last Name: ");
      scanf("%s",last_name);
      getchar();
      n = write(clientfd,last_name,strlen(last_name));
      if(n<0) perror("Error!!");
      printf("Message from the server: \n");
      n = read(clientfd,buffer,MAXLINE);
      printf("%s\n",buffer);
      bzero(buffer,MAXLINE);
    // search by zip code
    }else if(option == 3){
      printf("\n");
      char zip_code[MAXLINE];
      char option[] = "3";
      n = write(clientfd,option,strlen(option));
      printf("Enter Zip Code: ");
      scanf("%s",zip_code);
      getchar();
      n = write(clientfd,zip_code,strlen(zip_code));
      if(n<0) perror("Error!!");
      printf("Message from the server:\n");
      n = read(clientfd,buffer,MAXLINE);
      printf("%s\n",buffer);
      bzero(buffer,MAXLINE);
    // search by salary
    }else if(option == 4){
      printf("\n");
      char comparison[MAXLINE];
      char salary[MAXLINE];
      char option[] = "4";
      n = write(clientfd,option,strlen(option));
      printf("Enter Salary: ");
      scanf("%s",salary);
      getchar();                                     
      n = write(clientfd,salary,strlen(salary));
      printf("Enter Comparison Type [’>’,’<’,’==’,’>=’,’<=’]: ");
      scanf("%s",comparison);
      getchar();
      n = write(clientfd,comparison,strlen(comparison));
      if(n<0) perror("Error!!");  
      printf("Message from the server:\n");
      n = read(clientfd,buffer,MAXLINE);
      printf("%s\n",buffer);
      bzero(buffer,MAXLINE);
    // terminate
    }else if(option == 5){
      char option[] = "5";
      n = write(clientfd,option,strlen(option));
      break;
    }
    displayMenu();
    option = 0;

    fgets(input,sizeof(input),stdin);
    sscanf(input,"%d",&option);
  }
  
  printf("Connection Closed!!\n");
  return 0;
}