//File name: a.c
#include <stdio.h>
#include <stdlib.h>

#define m 6		//Rows
#define n 5		//Columns

int** a;
int *x, *y;

void read(int* a[], int x[]);
void multiply(int* a[], int x[], int y[]);
void print(int* a[], int x[], int y[]);

int main(){
  a=(int**) malloc(m*sizeof(int*));
  x = malloc(n * sizeof(int));
  y = malloc(n * sizeof(int));
  read(a, x);
  multiply(a, x, y);
  print(a, x, y);
  return 0;
}

void multiply(int* a[], int x[], int y[]){
  int i, j;
  for(i = 0; i < m; i++){
    y[i] = 0;
    for(j = 0; j < n; j++)
      y[i] += a[i][j] * x[j];
  }
}

void read(int* a[], int x[]){
  int i, j, k = 0;
  for(i = 0; i < m; i++)
    a[i] = malloc(n * sizeof(int));

  for(i = 0; i < m; i++)
    for(j = 0; j < n; j++)
       a[i][j] = k++;
 
    for(i = 0; i<n; i++)
      x[i] = -i;
}

void print(int* a[], int x[], int y[]){
  int i, j;
  printf("Matrix\n");
  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++)
      printf("%d	", a[i][j]);
    printf("\n");
  }
  printf("Vector\n");
  for(i = 0; i<n; i++)
    printf("%d	", x[i]);
  printf("\nResult\n");

  for(i = 0; i<n; i++)
    printf("%d	", y[i]);
  printf("\n");
}

