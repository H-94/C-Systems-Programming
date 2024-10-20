#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NUMBERS 100

void average(int numbers[],int count){
  double sum = 0;
  for(int i = 0;i < count;i++) sum += numbers[i];
  double average = sum / count;
  printf("The average value is %.2lf\n",average);
}

void minimum(int numbers[],int count){
  int min = numbers[0];
  for(int i = 1;i < count;i++) if(numbers[i] < min) min = numbers[i];
  printf("The minimum value is %d\n",min);
}

void maximum(int numbers[],int count){
  int max = numbers[0];
  for(int i = 1;i < count;i++) if(numbers[i] > max) max = numbers[i];
  printf("The maximum value is %d\n",max);
}

int main(int argc,char *argv[]){
  if (argc < 2){
    printf("Usage: %s <num1> <num2> ... <numN>\n",argv[0]);
    return 1;
  }

  int numbers[MAX_NUMBERS];
  int count = argc - 1;
  for(int i = 0;i < count;i++) numbers[i] = atoi(argv[i + 1]);

  pid_t avg,min,max;
  avg = fork();
  if(avg == 0){
    average(numbers,count);
    exit(0);
  }else wait(NULL);

  min = fork();
  if(min == 0){
    minimum(numbers,count);
    exit(0);
  }else wait(NULL);

  max = fork();
  if(max == 0){
    maximum(numbers,count);
    exit(0);
  }else wait(NULL);
  
  return 0;
}
