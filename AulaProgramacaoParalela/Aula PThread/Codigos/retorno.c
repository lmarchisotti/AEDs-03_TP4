#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define numThread 10

void* resultado(void *index){
	int thread = *((int*) index);
	printf("Eu, thread %d vou elevar meu indice ao quadrado \\o/\n", thread);
	int *i = (int*)malloc(sizeof(int));
	*i = (thread*thread);
	return (void*) i;
}

int main(){
	int i;
	pthread_t threads[numThread];
	int id[numThread];
	void *retorno[numThread];
	for(i = 0; i < numThread; i++){
		id[i] = i;
		pthread_create(&(threads[i]),NULL, resultado, &(id[i]));
	}

	for(i = 0; i < numThread; i++){
		pthread_join(threads[i],&(retorno[i]));
	}
	for(i = 0; i < numThread; i++){
		printf("Thread %d: %d\n",i, *((int*)retorno[i]));
		free(retorno[i]);
	}
	return 0;
}