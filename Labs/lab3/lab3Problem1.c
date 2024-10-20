#include <stdio.h>
#include <stdlib.h>

int main(){
  int n, *arr, i;
  //getting the size of array
  scanf("%d", &n);
  arr = (int*) malloc(n * sizeof(int));

  //getting the element of the array
  for(i = 0; i < n; i++){
      scanf("%d", arr + i);
  }

  //TODO: Write the logic to reverse the array "arr" here  

  //reversing array
  int temp;
  for(i = 0; i < n/2; i++){
    temp = arr[i];
    arr[i] = arr[n - 1 - i];
    arr[n - 1 - i] = temp;
  }
    
  //END TODO
      
  // Printing the resulting reversed array
  for(i = 0; i < n; i++)
    printf("%d ", *(arr + i));
  printf("\n");
  return 0;
}
