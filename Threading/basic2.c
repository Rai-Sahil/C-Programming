#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * Multiple threads in C
 */

int a = 0;

void *func(void *var){
    int *id = (int *)var;
    static int b = 0;

    b = 7;
    a = 7;

    printf("The ID of the thread is %d\n The global variable is %d\nThe static variable value is %d\n\n", *id, a, b);
}

int main(){
    pthread_t threadID;
    //If you run loop 10 times you have 10 threads
    for(int i = 0; i < 4; i++){
        pthread_create(&threadID, NULL, func, (void*)&threadID);
    }
    //Used to exit the thread;
    pthread_exit(NULL);
    exit(0);
}
