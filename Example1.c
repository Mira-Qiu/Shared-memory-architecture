//File name: a.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
int thread_count;  
void *Hello(void* rank){
  printf("Hello from thread %ld of %d\n", (long)rank, thread_count);
  return NULL;
}

int main(){
  long thread;  /* Use long in case of a 64-bit system */
  pthread_t* thread_handles; 
  printf("How many threads? ");
  scanf("%d", &thread_count);
  thread_handles = malloc(thread_count*sizeof(pthread_t)); 
  for (thread = 0; thread < thread_count; thread++)  
    pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);  
  printf("Hello from the main thread\n");
  for (thread = 0; thread < thread_count; thread++) 
    pthread_join(thread_handles[thread], NULL); 
  free(thread_handles);
  return 0;
}

//To Compile: gcc -g -Wall a.c -lpthread
//To run: ./a.out
