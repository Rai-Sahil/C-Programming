#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int fuel = 0;
pthread_mutex_t lock;
pthread_cond_t check;

void* gasStation(void* a){
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&lock);
        fuel += 60;
        printf("Fuel is being filled up at the station. Now at: %d\n", fuel);
        //It only awakens one threads. Only one thread will be able to check.
        pthread_cond_broadcast(&check);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

void* car(void* a){
    pthread_mutex_lock(&lock);
    while(fuel < 40){
        printf("The car is waiting outside\n");
        pthread_cond_wait(&check, &lock);
    }
    fuel -= 40;
    printf("Car filled up. Fuel at %d\n", fuel);
    pthread_mutex_unlock(&lock);
}

int main(){
    pthread_t th[5];

    pthread_cond_init(&check, NULL);
    for(int i = 0; i < 5; i++){
        if(i == 4){
            pthread_create(&th[i], NULL, &gasStation, NULL);
        } else {
            pthread_create(&th[i], NULL, &car, NULL);
        }
    }

    for(int i = 0; i < 5; i++){
        pthread_join(th[i], NULL);
    }
    pthread_cond_destroy(&check);
}

/**
* When the tank is at 40 2 cars can fill up it's fuel but only one did. Also we cannot launch all the threads to check the condition
 * as they'll come up false together. In this condition we only awake 1 thread that's why only 1 car came up.
 *
 * For this condition we use broadcast. It's not it's starting them all together. This all is going one by one to check and execute.
*/
