#include <stdio.h>

int main(){
  char startTemperatureScale,targetTemperatureScale;
  float temperature,convertedTemperature;

  printf("Enter starting temperature scale (F, C, or K): ");
  scanf(" %c",&startTemperatureScale);

  printf("Enter target temperature scale (F, C, or K): ");
  scanf(" %c",&targetTemperatureScale);

  printf("Enter temperature value: ");
  scanf("%f",&temperature);

  switch(startTemperatureScale){
    case 'F':
    case 'f':
      if(targetTemperatureScale == 'C' || targetTemperatureScale == 'c')
        convertedTemperature = (temperature - 32) * 5/9;
      else if(targetTemperatureScale == 'K' || targetTemperatureScale == 'k')
        convertedTemperature = (temperature - 32) * 5/9 + 273.15;
      break;
    case 'C':
    case 'c':
      if(targetTemperatureScale == 'F' || targetTemperatureScale == 'f')
        convertedTemperature = temperature * 9/5 + 32;
      else if(targetTemperatureScale == 'K' || targetTemperatureScale == 'k')
        convertedTemperature = temperature + 273.15;
      break;
    case 'K':
    case 'k':
      if(targetTemperatureScale == 'F' || targetTemperatureScale == 'f')
        convertedTemperature = (temperature - 273.15) * 9/5 + 32;
      else if(targetTemperatureScale == 'C' || targetTemperatureScale == 'c')
        convertedTemperature = temperature - 273.15;
      break;
    default:
      printf("Invalid scale\n");
      return 1;
  }
  
  printf("%.2f°%c is equivalent to %.2f°%c\n",temperature,startTemperatureScale,convertedTemperature,targetTemperatureScale);
  return 0;
}
