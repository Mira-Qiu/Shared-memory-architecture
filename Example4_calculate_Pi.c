//File name: a.c
#include <stdio.h>
#include <stdlib.h>

#define n 1000000

int main(){
  double factor = 1, sum = 0, pi;
  int i;
  for(i = 0; i < n; i++){
    sum += factor/(2*i+1);
    factor = -factor;
  }
  pi = 4 * sum;
  printf("pi = %f\n", pi);
  return 0;
}
