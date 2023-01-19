#include <stdio.h>
#include <stdlib.h> 
  
int main(void) 
{ 
   static int *p = (int*)malloc(sizeof(p)); 
   *p = 10; 
   printf("%d", *p); 
}