#include "csapp.h"

#define MAX_SIZE 1000
#define MAX_LENGTH 25

typedef struct {
  char firstName[MAX_LENGTH];
  char lastName[MAX_LENGTH];
  char zipCode[MAX_LENGTH];
  char department[MAX_LENGTH];
  int salary;
} Struct_Employee_Info;

void serverFunction(int connfd){
  FILE *file;
  Struct_Employee_Info employees[MAX_SIZE];
  char line[MAXLINE];
  int count = 0;

  // open records.csv
  file = fopen("records.csv","r");
  if(file == NULL) printf("Unable to open the file.\n");

  // read records.csv
  while(fgets(line, sizeof(line),file)){
    sscanf(line,"%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName,employees[count].lastName,employees[count].zipCode,employees[count].department,&employees[count].salary);
    count++;
  }

  fclose(file);

  char buffer[MAXLINE];
  char successMessage[MAXLINE] = "Record added Sucessfully!!\n";

  size_t n;
  if(n<0) perror("Error!!");
  while(1){
    bzero(buffer,MAXLINE);
    n = read(connfd, buffer, MAXLINE);
    int opt;
    char firstName[MAXLINE];
    char option[MAXLINE];
    sscanf(buffer,"%[^\n]",option);
    opt = atoi(option);
    bzero(buffer,MAXLINE);
    // add record
    if(opt == 1){
      char firstName[MAXLINE];
      char lastName[MAXLINE];
      char zip_code[MAXLINE];
      char department[MAXLINE];
      char salary[MAXLINE];
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",firstName);
      bzero(buffer,MAXLINE);
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",lastName);
      bzero(buffer,MAXLINE);
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",zip_code);
      bzero(buffer,MAXLINE);
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",department);
      bzero(buffer,MAXLINE);
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",salary);
      bzero(buffer,MAXLINE);
      file = fopen("records.csv","a+");
      fprintf(file,"%s,%s,%s,%s,%s\n",firstName,lastName,zip_code,department,salary);
      n = write(connfd,successMessage,strlen(successMessage));
      count = 0;  
      fclose(file);
      file = fopen("records.csv","r");
      while(fgets(line,sizeof(line),file)){
        sscanf(line,"%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName,employees[count].lastName,employees[count].zipCode,employees[count].department,&employees[count].salary);
        count++;
      }
      bzero(buffer,MAXLINE);
      fclose(file);
    // search by name
    }else if(opt == 2){ 
      char lastName[MAXLINE];
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",firstName);
      n = read(connfd, buffer,MAXLINE);
      sscanf(buffer, "%[^\n]",lastName);
      int temp = -1;
      for(int i = 0;i < count;i++){
        if((strcmp(employees[i].firstName,firstName)==0) && (strcmp(employees[i].lastName,lastName)==0)){
          temp = i;
          sprintf(line,"%s,%s,%s,%s,%d\n",employees[temp].firstName,employees[temp].lastName,employees[temp].zipCode,employees[temp].department,employees[temp].salary);
          n = write(connfd,line,strlen(line));
          bzero(line, MAXLINE);          
          bzero(buffer,MAXLINE);
        }
      }
      if(temp == -1){
        char n_line[MAXLINE];
        bzero(n_line,MAXLINE);    
        strcpy(n_line,"No record found!!\n");
        n = write(connfd,n_line,strlen(n_line));
      }
    // search by zip code
    }else if(opt == 3){
      bzero(line, MAXLINE);
      char zip[MAXLINE];
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",zip);
      int temp = -1;
      for(int i = 0;i < count;i++){
        if((strcmp(employees[i].zipCode,zip)==0)){
          temp = i;
          strcat(line,employees[temp].firstName);
          strcat(line,",");
          strcat(line,employees[temp].lastName);
          strcat(line,",");
          strcat(line,employees[temp].zipCode);
          strcat(line,",");
          strcat(line,employees[temp].department);
          strcat(line,",");
          char salary[MAX_LENGTH];
          snprintf(salary,sizeof(salary),"%d",employees[temp].salary);
          strcat(line,salary);
          strcat(line,"\n");
        }   
      }
      if(temp == -1){ 
        char n_line[MAXLINE];
        bzero(n_line,MAXLINE);
        strcpy(n_line,"No record found!!\n");
        n = write(connfd,n_line,strlen(n_line));
      }else{
        n = write(connfd,line,strlen(line));
        bzero(line,MAXLINE);
        bzero(buffer,MAXLINE);
      }
    // search by salary
    }else if(opt == 4){
      char sal[MAXLINE];
      n = read(connfd, buffer,MAXLINE);
      sscanf(buffer, "%[^\n]",sal);
      char comparison[MAXLINE];
      bzero(buffer,MAXLINE);
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer," %[^\n]",comparison);
      int salary = atoi(sal);
      int temp = -1;
      if((strcmp(comparison,">=")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary >= salary){
            temp = i;
            strcat(line,employees[temp].firstName);
            strcat(line,",");
            strcat(line,employees[temp].lastName);
            strcat(line,",");
            strcat(line,employees[temp].zipCode);
            strcat(line,",");
            strcat(line,employees[temp].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary,sizeof(salary),"%d",employees[temp].salary);
            strcat(line,salary);
            strcat(line,"\n");
          }
        }
      }else if((strcmp(comparison,"<=")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary <= salary){
            temp = i;
            strcat(line,employees[temp].firstName);
            strcat(line,",");
            strcat(line,employees[temp].lastName);
            strcat(line,",");
            strcat(line,employees[temp].zipCode);
            strcat(line,",");
            strcat(line,employees[temp].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary,sizeof(salary),"%d",employees[temp].salary);
            strcat(line,salary);
            strcat(line,"\n");
          }
        }
      }else if((strcmp(comparison,"<")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary < salary){
            temp = i;
            strcat(line,employees[temp].firstName);
            strcat(line,",");
            strcat(line,employees[temp].lastName);
            strcat(line,",");
            strcat(line,employees[temp].zipCode);
            strcat(line,",");
            strcat(line,employees[temp].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary,sizeof(salary),"%d",employees[temp].salary);
            strcat(line,salary);
            strcat(line,"\n");
          }
        }
      }else if((strcmp(comparison,">")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary > salary){
            temp = i;
            strcat(line,employees[temp].firstName);
            strcat(line,",");
            strcat(line,employees[temp].lastName);
            strcat(line,",");
            strcat(line,employees[temp].zipCode);
            strcat(line,",");
            strcat(line,employees[temp].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary),"%d",employees[temp].salary);
            strcat(line,salary);
            strcat(line,"\n");
          }
        }
      }else if((strcmp(comparison,"==")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary == salary){
            temp = i;
            strcat(line,employees[temp].firstName);
            strcat(line,",");
            strcat(line,employees[temp].lastName);
            strcat(line,",");
            strcat(line,employees[temp].zipCode);
            strcat(line,",");
            strcat(line,employees[temp].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary),"%d",employees[temp].salary);
            strcat(line,salary);
            strcat(line,"\n");
          }
        }
      }
      if(temp == -1){
        char n_line[MAXLINE];
        bzero(n_line,MAXLINE);
        strcpy(n_line,"No record found!!\n");
        n = write(connfd,n_line,strlen(n_line));
      }else{
        n = write(connfd,line,strlen(line));
        bzero(line,MAXLINE);
        bzero(buffer,MAXLINE);
      }
      if(n<0) perror("Error!!");
    // disconnect
    }else if(opt==5){ 
      break;
    }
  }
}

int main(int argc,char *argv[]){
  int listenfd;
  int connfd; //file descriptor to communicate with the client
  socklen_t clientlen;
  struct sockaddr_storage clientaddr; /* Enough space for any address */
  char client_hostname[MAXLINE],client_port[MAXLINE];
   
  if(argc != 2){
	  fprintf(stderr,"usage: %s <port>\n",argv[0]);
	  exit(0);
  }
  
  listenfd = Open_listenfd(argv[1]); //wrapper function that calls getadderinfo, socket, bind, and listen functions in the server side

  //Server runs in the infinite loop.
  //To stop the server process, it needs to be killed using the Ctrl+C key.
  while(1){               
  	clientlen = sizeof(struct sockaddr_storage);

    // wait for the connection from the client.
  	connfd = Accept(listenfd,(SA *)&clientaddr,&clientlen);
    Getnameinfo((SA *) &clientaddr,clientlen,client_hostname,MAXLINE,client_port,MAXLINE,0);
    printf("Connected to (%s, %s)\n",client_hostname,client_port);

    //function to interact with the client
    serverFunction(connfd);

    Close(connfd);
    printf("(%s, %s) disconnected\n",client_hostname,client_port);
  }
  exit(0);
}