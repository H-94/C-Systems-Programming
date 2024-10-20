#include <stdio.h>
#include <ctype.h>

#define BYTES_PER_LINE 16

int main(int argc,char *argv[]){
  //Check filename
  if(argc != 2){
    printf(" %s <filename>\n",argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1],"rb");
  if (file == NULL){
    perror("Error");
    return 1;
  }
  //Read file & print hexadecimal
  unsigned char buffer[BYTES_PER_LINE];
  size_t offset = 0;
  size_t bytesRead;
  while((bytesRead = fread(buffer,1,BYTES_PER_LINE,file)) > 0){
    printf("%08zx: ",offset);
    // Print hex
    for(size_t i = 0;i < BYTES_PER_LINE;i++){
      if(i < bytesRead) printf("%02x",buffer[i]);
      else printf("  ");
      if(i % 2 != 0) printf(" ");
    }
    printf(" ");
    // Print ASCII
    for(size_t i = 0;i < bytesRead;i++){
      if(isprint(buffer[i])) printf("%c", buffer[i]);
      else printf(".");
    }
    printf("\n");
    offset += BYTES_PER_LINE;
  }

  fclose(file);
  return 0;
}

