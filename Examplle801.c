#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define thread_count	5

long long sum = 0;
long long count = 0;
pthread_mutex_t mutex;

void *Brrier_with_busy_waiting_and_mutex(void* my_number);

int main(){
  pthread_t* thread_handles;
  long thread;
  thread_handles = malloc(thread_count*sizeof(pthread_t));
  pthread_mutex_init(&mutex, NULL);
  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread], NULL, Brrier_with_busy_waiting_and_mutex, (void*) thread); 
  
  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);
  printf("sum = %lld\n", sum);
  pthread_mutex_destroy(&mutex);
  free(thread_handles);
  return 0;
}

void *Brrier_with_busy_waiting_and_mutex(void* my_number){
  pthread_mutex_lock(&mutex);
  count++;
  sum += (long)my_number;
  pthread_mutex_unlock(&mutex);
  printf("I am waiting for my coworker\n");
  while(count < thread_count)
    ; //Do nothing. Just keep iterating
  printf("I am NOT waiting anymore\n");
  return NULL;
}
