//thread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long n = 100000;
long thread_count = 5; //n must be divisible by the value of this variable.
long double sum;

void *Thread_sum(void* rank);

int main(){	
  long thread;
  pthread_t* thread_handles;
  thread_handles = malloc(thread_count*sizeof(pthread_t));
  sum = 0;
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread);

  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);
  printf("pi = %Lf\n", 4 * sum);
  free(thread_handles);
  return 0;
}

void *Thread_sum(void* rank){
  long my_rank = (long) rank;
  double factor;
  long long i;
  long long my_n = n/thread_count;
  long long my_first_i = my_n*my_rank;
  long long my_last_i = my_first_i + my_n;
  if(my_first_i % 2 == 0) factor = 1;
  else factor = -1;                                  // factor = my_first_i % 2 == 0 ? 1 : -1;
  for(i = my_first_i; i < my_last_i; i++){
    sum += factor/(2*i+1);
    factor = -factor;
  }
  return NULL;
}




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
