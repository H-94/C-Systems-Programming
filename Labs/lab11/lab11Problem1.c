#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

struct Stats{
  double average;
  int maximum;
  int minimum;
};

int *numbers;
int count;
struct Stats stats;

void *calculate_average(void *arg){
  double sum = 0.0;
  for (int i = 0;i < count;i++) sum += numbers[i];
  stats.average = sum / count;
  pthread_exit(NULL);
}

void *calculate_maximum(void *arg){
  int max = numbers[0];
  for(int i = 1;i < count;i++){
    if(numbers[i] > max) max = numbers[i];
  }
  stats.maximum = max;
  pthread_exit(NULL);
}

void *calculate_minimum(void *arg){
  int min = numbers[0];
  for(int i = 1;i < count;i++){
    if(numbers[i] < min) min = numbers[i];
  }
  stats.minimum = min;
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if(argc < 2){
    fprintf(stderr,"Usage: %s <num1> <num2> ... <numN>\n",argv[0]);
    return 1;
  }

  count = argc - 1;
  numbers = (int *)malloc(count * sizeof(int));
  if(numbers == NULL){
    fprintf(stderr,"Memory allocation failed.\n");
    return 1;
  }

  for(int i = 1;i < argc;i++) numbers[i - 1] = atoi(argv[i]);

  pthread_t threads[NUM_THREADS];
  pthread_create(&threads[0],NULL,calculate_average,NULL);
  pthread_create(&threads[1],NULL,calculate_maximum,NULL);
  pthread_create(&threads[2],NULL,calculate_minimum,NULL);

  for(int i = 0;i < NUM_THREADS;i++) pthread_join(threads[i], NULL);

  printf("The average value is %.2lf\n",stats.average);
  printf("The minimum value is %d\n",stats.minimum);
  printf("The maximum value is %d\n",stats.maximum);

  free(numbers);
  return 0;
}

