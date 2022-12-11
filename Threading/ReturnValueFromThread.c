#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
/**
 * Getting the return value from thread.
 * To get value from return function to main method, we use second parameter of join.
 */

void* roll_dice(){
    int value = (rand() % 6) + 1;
    int *result = (malloc)(sizeof(int));
    *result = value;
    return (void*)result;
}


int main(int argc, char** argv) {
    srand(time(NULL));
    pthread_t thread1;

    if( pthread_create(&thread1, NULL, &roll_dice, NULL) != 0) return 1;

    int *returnValue;
    if(pthread_join(thread1, (void**)&returnValue) != 0) return 2;

    printf("The returned value is %d", *returnValue);
    free(returnValue);
    return 0;
}
