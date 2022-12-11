#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * Condition Variables
 */

//Both the functions are gonna work with it lets create the mutex so they don't overlap
int fuel = 0;
pthread_mutex_t lockFuel;

//Condition variable to make the car wait.
pthread_cond_t wait;

void* fuelFilling(void* arg){
    for ( int i = 0; i < 5; i++){
        pthread_mutex_lock(&lockFuel);
        fuel += 15;
        printf("Filled The Fuel %d\n", fuel);
        pthread_mutex_unlock(&lockFuel);
        pthread_cond_signal(&wait);
        sleep(1);
    }
}

void* car(void* arg){
    pthread_mutex_lock(&lockFuel);
    while(fuel < 40){
        printf("No Fuel. Waiting for the fuel\n");
        //sleep(1);
//        Instead of sleep here we can say condition variable to wait.
        pthread_cond_wait(&wait, &lockFuel);
        //It is going to wait for the signal from another thread to change the value.
        //This will keep on waiting until we send the fuel from another thread
    }
    fuel -= 40;
    printf("Got The Fuel. Now Fuel is: %d\n", fuel);
    pthread_mutex_unlock(&lockFuel);
}

int main(int argc, char** argv) {

    pthread_t th[2];

    pthread_cond_init(&wait, NULL);

    for (int i = 0; i < 2; i++){
        if(i == 1){
            if(pthread_create(&th[i], NULL, &fuelFilling, NULL) != 0 ){
                perror("Error While Creating Thread");
            }
        } else{
            if(pthread_create(&th[i], NULL, &car, NULL) != 0 ){
                perror("Error While Creating Thread");
            }
        }
    }

    for (int i = 0; i < 2; i++){
        if(pthread_join(th[i], NULL) != 0 ){
            perror("Error While Joining Thread");
        }
    }
    pthread_cond_destroy(&wait);
    return 0;
}

/**
* As you can see from the output the  first thread is first taking the fuel out from the variable even tho there is no no fuel.
 * Only then the second thread is working.
 * Hence we want the car to until the fuel in filled in gas station and then make its filling
*/

/**
* There are only 3 types of value in condition.
 * wait - should always be inside the while, as that's where the condition lies
 * signal
 * broadcast
 * To run the condition variable we always need mutex as well.
*/

/**
* In the middle of the gas station being filed you were able to check the fuel amount and fill it once it meet the condition,
 * Send the signal to first thread which is waiting. 
 * Basically you're starting the first and second thread, first thread didn't met the condition so wait here but until then
 * run the second thread, once the condition is met second thread will signal the first thread to run.
 * finish running it and then go back to second thread.
*/
