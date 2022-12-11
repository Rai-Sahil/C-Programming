#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * TryLock
 * When you have a lot of threads and you want all these threads to use functions and many threads can use the same functions. 
 * at the same time. Just use tryLock function using iteration of each thread. 
 */

// No. of chefs = thread;
// Stove = shared data(Mutex)

pthread_mutex_t stoveMutex[4];

int fuel[4] = { 100, 100, 100, 100};

void* routine() {
    for (int i = 0; i < 4; i++){
        //Basically it is saying that the first stove is full you cannot use this. Hence go to next one.
        if( pthread_mutex_trylock(&stoveMutex[i]) == 0 ){
            int fuelRequired = (rand() % 30);
            if(fuel[i] - fuelRequired < 0){
                printf("No Fuel Left...\n");
            }
            else{
                fuel[i] -= fuelRequired;
                usleep(500000);
                printf("Cooking Is Done. Fuel Left in the Stove is %d\n", fuel[i]);
            }
            pthread_mutex_unlock(&stoveMutex[i]);
            break;
        } else {
            if( i == 3 ){
                //if it's the last thread iteration all the four threads will lock the thread.
                //Hence at the end only 4 chefs will be able to cook. and trylock will continue
                //the program without doing anything. Since other 6 threads won't do anything.
                printf("Waiting\n");
                usleep(300000);
                i = 0;
            }
        }
    }
}

int main(){
    srand( time(NULL));
    pthread_t th[10];

    for (int i = 0; i < 10; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0) perror("Failed to connect the thread");
    }

    for (int i = 0; i < 10; i++){
        if(pthread_join(th[i], NULL) != 0) perror("Failed to Join the thread");
    }
}
