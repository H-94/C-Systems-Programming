#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//define macro for limits
#define MAX_WORDS 50
#define MAX_WORD_LENGTH 20

//capitalize word
void capitalizeWord(char *word){
  for(int i=0;word[i]!='\0';i++){
    word[i] = toupper(word[i]);
  }
}
//compare strings for qsort
int compareStrings(const void *a,const void *b){
  return strcmp(*(const char **)a,*(const char **)b);
}

int main(){
  char input[500];
  char *words[MAX_WORDS];
  int wordCount = 0;

  //reading text from user
  printf("Enter a line of text: ");
  fgets(input,sizeof(input),stdin);

  //input into words
  char *token = strtok(input," \t\n");
  while(token != NULL && wordCount < MAX_WORDS){
    if(strlen(token)<=MAX_WORD_LENGTH){
      words[wordCount] = strdup(token);
      capitalizeWord(words[wordCount]);
      wordCount++;
    }else{
      printf("exceeding maximum word length\n");
      return 0;
    }
    token = strtok(NULL," \t\n");
  }

  //sorting in ascending order
  qsort(words,wordCount,sizeof(char *),compareStrings);

  //print vowels
  printf("Words starting with vowels:\n");
  for(int i=0;i<wordCount;i++){
    if(strchr("AEIOUaeiou",words[i][0]) != NULL){
      printf("%s\n",words[i]);
    }
    free(words[i]);
  }

  return 0;
}
