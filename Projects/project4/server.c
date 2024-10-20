#include "csapp.h"
#include <pthread.h>

#define MAX_SIZE 1000
#define MAX_LENGTH 25

struct Clients{
  int connfd;
  char client_hostname[MAXLINE];       
  char client_port[MAXLINE];
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
  file = fopen("records.csv","r");
  if(file == NULL) printf("Unable to open the file.\n");
  // read records.csv
  while(fgets(line,sizeof(line),file)){
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
    n = read(connfd,buffer,MAXLINE);
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
      char Department[MAXLINE];
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
      sscanf(buffer,"%[^\n]",Department);
      bzero(buffer,MAXLINE);
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",salary);
      bzero(buffer,MAXLINE);
      pthread_mutex_lock(&mutex); 
      file = fopen("records.csv","a+");
      fprintf(file,"%s,%s,%s,%s,%s\n",firstName,lastName,zip_code,Department,salary);
      pthread_mutex_unlock(&mutex);  
      n = write(connfd,successMessage,strlen(successMessage));
      count = 0;  
      fclose(file);
      file = fopen("records.csv", "r");
      while(fgets(line,sizeof(line),file)) {
        sscanf(line,"%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName,employees[count].lastName,employees[count].zipCode,employees[count].department,&employees[count].salary);
        count++;
      }
      fclose(file); 
      bzero(buffer,MAXLINE);
    // search by name
    }else if(opt == 2){ 
      int new_counter = 0;
      file = fopen("records.csv","r");
      while(fgets(line,sizeof(line),file)) new_counter++;
      fclose(file); 
      file = fopen("records.csv","r");
      if(new_counter != count){
        count=0;
        while(fgets(line,sizeof(line),file)){
          sscanf(line,"%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName,employees[count].lastName,employees[count].zipCode,employees[count].department,&employees[count].salary);
          count++;
        }
      }
      fclose(file); 
      char lastName[MAXLINE];
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",firstName);
      bzero(buffer, MAXLINE);
      n = read(connfd, buffer, MAXLINE);
      sscanf(buffer,"%[^\n]",lastName);
      bzero(buffer,MAXLINE);
      int index = -1;
      for(int i = 0;i < count;i++){
        if((strcmp(employees[i].firstName,firstName)==0) && (strcmp(employees[i].lastName,lastName)==0)){
          index = i;
          snprintf(line,MAXLINE,"%s,%s,%s,%s,%d\n",employees[index].firstName,employees[index].lastName,employees[index].zipCode,employees[index].department,employees[index].salary);
          n = write(connfd,line,strlen(line));
          bzero(line, MAXLINE);     
          bzero(buffer,MAXLINE);
        }
      }
      if(index == -1){
        char n_line[MAXLINE];
        bzero(n_line,MAXLINE);    
        strcpy(n_line,"No record found!!\n");
        n = write(connfd,n_line,strlen(n_line));
      }
    // search by zip code
    }else if(opt == 3){
      bzero(line, MAXLINE);
      char zipcode[MAXLINE];
      int new_counter = 0;
      file = fopen("records.csv","r");
      while(fgets(line,sizeof(line),file)) new_counter++;
      fclose(file); 
      file = fopen("records.csv","r");
      if(new_counter != count){
        count = 0;
        while(fgets(line,sizeof(line),file)){
          sscanf(line,"%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName,employees[count].lastName,employees[count].zipCode,employees[count].department,&employees[count].salary);
          count++;
        }
      }
      fclose(file); 
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",zipcode);
      pthread_mutex_lock(&mutex);
      int index = -1;
      for(int i = 0;i < count;i++){
        if((strcmp(employees[i].zipCode,zipcode)==0)){
          index = i;
          bzero(line, MAXLINE);
          strcat(line,employees[index].firstName);
          strcat(line,",");
          strcat(line,employees[index].lastName);
          strcat(line,",");
          strcat(line,employees[index].zipCode);
          strcat(line,",");
          strcat(line,employees[index].department);
          strcat(line,",");
          char salary[MAX_LENGTH];
          snprintf(salary,sizeof(salary),"%d",employees[index].salary);
          strcat(line,salary);
          strcat(line,"\n");
          n = write(connfd,line,strlen(line));
        }   
      }
      pthread_mutex_unlock(&mutex);
      if(index == -1){ 
        char n_line[MAXLINE];
        bzero(n_line,MAXLINE);
        strcpy(n_line,"No record found!!\n");
        n = write(connfd,n_line,strlen(n_line));
      }
      else{
        bzero(line,MAXLINE);
        bzero(buffer,MAXLINE);
      }
    // search by salary
    }else if(opt == 4){
      char sal[MAXLINE];
      int new_counter = 0;
      file = fopen("records.csv","r");
      while(fgets(line, sizeof(line),file)) new_counter++;
      fclose(file); 
      file = fopen("records.csv","r");
      if(new_counter != count){
        count=0;
        while(fgets(line,sizeof(line),file)){
          sscanf(line,"%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName,employees[count].lastName,employees[count].zipCode,employees[count].department,&employees[count].salary);
          count++;
        }
      }
      fclose(file); 
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",sal);
      char comparison[MAXLINE];
      bzero(buffer,MAXLINE);
      n = read(connfd,buffer,MAXLINE);
      sscanf(buffer,"%[^\n]",comparison);
      int salary = atoi(sal);
      int index = -1;
      if((strcmp(comparison,">=")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary >= salary){
            index = i;
            bzero(line,MAXLINE);
            strcat(line,employees[index].firstName);
            strcat(line,",");
            strcat(line,employees[index].lastName);
            strcat(line,",");
            strcat(line,employees[index].zipCode);
            strcat(line,",");
            strcat(line,employees[index].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary,sizeof(salary),"%d",employees[index].salary);
            strcat(line,salary);
            strcat(line,"\n");
            n = write(connfd,line,strlen(line));
          }
        }
      }else if((strcmp(comparison,"<=")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary <= salary){
            index = i;
            bzero(line, MAXLINE);
            strcat(line,employees[index].firstName);
            strcat(line,",");
            strcat(line,employees[index].lastName);
            strcat(line,",");
            strcat(line,employees[index].zipCode);
            strcat(line,",");
            strcat(line,employees[index].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary,sizeof(salary),"%d",employees[index].salary);
            strcat(line,salary);
            strcat(line,"\n");
            n = write(connfd,line,strlen(line));
          }
        }
      }else if((strcmp(comparison,"<")==0)){
        for(int i = 0;i < count;i++){
          if(employees[i].salary < salary){
            index = i;
            bzero(line, MAXLINE);
            strcat(line,employees[index].firstName);
            strcat(line,",");
            strcat(line,employees[index].lastName);
            strcat(line,",");
            strcat(line,employees[index].zipCode);
            strcat(line,",");
            strcat(line,employees[index].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary,sizeof(salary),"%d",employees[index].salary);
            strcat(line,salary);
            strcat(line,"\n");
            n = write(connfd,line,strlen(line));
          }
        }
      }else if((strcmp(comparison,">")==0)){
        for(int i = 0; i < count; i++){
          if(employees[i].salary > salary){
            index = i;
            bzero(line,MAXLINE);
            strcat(line,employees[index].firstName);
            strcat(line,",");
            strcat(line,employees[index].lastName);
            strcat(line,",");
            strcat(line,employees[index].zipCode);
            strcat(line,",");
            strcat(line,employees[index].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary,sizeof(salary),"%d",employees[index].salary);
            strcat(line,salary);
            strcat(line,"\n");
            n = write(connfd,line,strlen(line));
          }
        }
      }else if((strcmp(comparison,"==")==0)){
        for(int i = 0; i < count; i++){
          if(employees[i].salary == salary){
            index = i;
            bzero(line, MAXLINE);
            strcat(line,employees[index].firstName);
            strcat(line,",");
            strcat(line,employees[index].lastName);
            strcat(line,",");
            strcat(line,employees[index].zipCode);
            strcat(line,",");
            strcat(line,employees[index].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index].salary);
            strcat(line, salary);
            strcat(line, "\n");
            n = write(connfd,line,strlen(line));
          }
        }
      }
      if(index == -1){
      char n_line[MAXLINE];
      bzero(n_line,MAXLINE);
      strcpy(n_line,"No record found!!\n");
      n = write(connfd,n_line,strlen(n_line));
      }else{
        bzero(line,MAXLINE);
        bzero(buffer,MAXLINE);
      }
      if(n<0){
        perror("Error!!");
      }
    // disconnect
    }else if(opt==5) break;
  }
}

void *thread(void *vargp){
  struct Clients *data = (struct Clients *)vargp;
  int connfd = (*data).connfd;
  char *client_hostname = (*data).client_hostname;
  char *client_port = (*data).client_port;
  pthread_detach(pthread_self());
  free(vargp);
  serverFunction(connfd);
  Close(connfd);
  printf("(%s,%s) disconnected\n",client_hostname,client_port);
  return NULL;
}

int main(int argc,char *argv[]){
  int listenfd;
  int *connfd; //file descriptor to communicate with the client
  socklen_t clientlen;
  struct sockaddr_storage clientaddr; /* Enough space for any address */
  char client_hostname[MAXLINE], client_port[MAXLINE];
  pthread_t tid;
    
  if (argc != 2) {
	  fprintf(stderr, "usage: %s <port>\n", argv[0]);
	  exit(0);
  }

  listenfd = Open_listenfd(argv[1]);

  //Server runs in the infinite loop. 
  //To stop the server process, it needs to be killed using the Ctrl+C key. 
  while (1) {               
  	clientlen = sizeof(struct sockaddr_storage);
    connfd = malloc(sizeof(int));
  	*connfd = Accept(listenfd,(SA *) &clientaddr,&clientlen);
    Getnameinfo((SA *) &clientaddr,clientlen,client_hostname,MAXLINE,client_port,MAXLINE,0);
    printf("Connected to (%s, %s)\n", client_hostname, client_port);
    struct Clients *data = malloc(sizeof(struct Clients));
    (*data).connfd = *connfd;
    strcpy(data->client_hostname,client_hostname);
    strcpy(data->client_port,client_port);
    pthread_create(&tid,NULL,thread,data);
  }
        
  exit(0);
}