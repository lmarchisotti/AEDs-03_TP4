#include <stdio.h>
#include <pthread.h>

#define numThread 10

void hello(void *index){
    int thread = *((int*) index);
    printf("hello from %d thread\n", thread);
}

int main(){
    int i;
    pthread_t threads[numThread];
    int id[numThread];
    for(i = 0; i < numThread; i++){
        id[i] = i;
        pthread_create(&(threads[i]),NULL, (void*)hello, &(id[i]));
    }

    for(i = 0; i < numThread; i++){
        pthread_join(threads[i],NULL);
    }
    return 0;
}