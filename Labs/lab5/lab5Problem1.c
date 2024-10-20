#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 51

struct Struct_Student_Info{
  char StudentName[MAX_NAME_LENGTH];
  int ID;
  float Score;
};

void sortByScore(struct Struct_Student_Info studentsArray[],int n){
  int i,j;
  struct Struct_Student_Info temp;
  for(i = 0;i < n - 1;i++){
    for(j = 0;j < n - i - 1;j++){
      if(studentsArray[j].Score > studentsArray[j + 1].Score || (studentsArray[j].Score == studentsArray[j + 1].Score && strcmp(studentsArray[j].StudentName,studentsArray[j + 1].StudentName) > 0)){
        temp = studentsArray[j];
        studentsArray[j] = studentsArray[j + 1];
        studentsArray[j + 1] = temp;
      }
    }
  }
}

void display(struct Struct_Student_Info studentsArray[],int n){
  for(int i = 0;i < n;i++){
    printf("%s %d %.2f\n",studentsArray[i].StudentName,studentsArray[i].ID,studentsArray[i].Score);
  }
}

int main(){
  struct Struct_Student_Info studentsArray[MAX_STUDENTS];
  FILE *file = fopen("student.csv","r");
  if(file == NULL){
    printf("Error opening file.\n");
    return 1;
  }
  char line[100];
  fgets(line,sizeof(line),file);
  int count = 0;
  while(fgets(line,sizeof(line),file) && count < MAX_STUDENTS){
    char name[MAX_NAME_LENGTH];
    int id;
    float score;
    sscanf(line, "%[^,], %d, %f",name,&id,&score);
    strcpy(studentsArray[count].StudentName,name);
    studentsArray[count].ID = id;
    studentsArray[count].Score = score;
    count++;
  }
    fclose(file);
    sortByScore(studentsArray, count);
    display(studentsArray, count);

    return 0;
}

