#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

/**
 * Giving parameters to the thread functions.
 *
 */

//TODO ASK JEE HO

int primes[10] ={ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg){
    int index = *(int *)arg;
    int sum = 0;
    for(int i = 0;i < 5; i++){
        sum += primes[index + i];
    }
    *(int*)arg = sum;
    return arg;
}

int main(int argc, char** argv) {
    pthread_t th[10];

    for( int i = 0; i < 2; i++ ) {
        //Always pass the malloced memory pointer in to pthread in c.
        int *a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to create threads");
        }
    }
    int globalSum = 0;
    for( int i = 0; i < 2; i++ ){
        int *r;
        if(pthread_join(th[i], &r) != 0){
            perror("Failed to join threads");
        }
        globalSum += *r;
        free(r);
    }
    printf("%d", globalSum);
    return 0;
}
