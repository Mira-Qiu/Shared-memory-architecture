#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define m 6		//Number of rows
#define n 5		//Number of columns

int** a;
int *x, *y;
int thread_count = 3; //m must be divisible by this number

void read(int* a[], int x[]);
void *Pth_mat_vect(void* rank);
void print(int* a[], int x[], int y[]);

int main(){
  long thread;
  pthread_t* thread_handles;
  a=(int**) malloc(m*sizeof(int*));
  x = malloc(n * sizeof(int));
  y = malloc(n * sizeof(int));
  read(a, x);
  thread_handles = malloc(thread_count*sizeof(pthread_t));
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void*) thread);

  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);

  print(a, x, y);

  free(thread_handles);

  return 0;
}

void *Pth_mat_vect(void* rank){
  long my_rank = (long) rank;
  int i, j; 
  int local_m = m/thread_count; 
  int my_first_row = my_rank*local_m;
  int my_last_row = my_first_row + local_m;
  for (i = my_first_row; i < my_last_row; i++){
    y[i] = 0;
    for (j = 0; j < n; j++)
      y[i] += a[i][j] * x[j];
  }
  return NULL;
}



//create matrix, and vector
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

