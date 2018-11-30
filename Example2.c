#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	int rank,a,b;
} record_type;

int thread_count = 4;
void *Thread_add(void* args);

int main(){
	int thread,x = 1;
	pthread_t* thread_handles;
	record_type data[4];
	thread_handles = malloc(thread_count*sizeof(pthread_t));
	for(thread = 0; thread< thread_count;thread++){
		data[thread].rank =thread;
		data[thread].a = x++;
		data[thread].b = x++;
		pthread_create(&thread_handles[thread],	NULL,Thread_add,&data[thread]);
	}

	for(thread =0; thread < thread_count;thread++)
		pthread_join(thread_handles[thread],NULL);
	free(thread_handles);
	return 0;
}

void *Thread_add(void* args){
	record_type *data = (record_type*) args;
	printf("In thread %d sum of %d and %d is %d\n", data->rank,data->a,data->b,data->a + data->b);
	return NULL;
}

/* output:
* In thread 3 sum of 7 and 8 is 15
* In thread 2 sum of 5 and 6 is 11
* In thread 1 sum of 3 and 4 is 7
* In thread 0 sum of 1 and 2 is 3
*/
