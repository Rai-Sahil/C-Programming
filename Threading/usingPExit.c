#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
/**
 * Another way of getting the return value from the threads
 */

void* roll_dice(){
    int value = (rand() % 6) + 1;
    int *result = (malloc)(sizeof(int));
    *result = value;
    printf("The return value from the helper function is %d\n", *result);
    pthread_exit((void*)result);
}


/**
 * Some times you just wanna end the main functions even tho the threads are running. We can use exit for it.
 * before joining it. Like just end in the middle of the execution. exit will first complete the execution the threads
 * and only then before joining it will kill the threads
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    pthread_t th[4];

    for (int i = 0; i < 3; i++){
        if( pthread_create(&th[i], NULL, &roll_dice, NULL) != 0) return 1;
    }

    //we cannot do this because we are actually ending the whole process not just the threads, since we still want the threads execution till here.
    //return 0;

    //Use pthread_exit instead. It will finish the execution of the threads and will destroy them before joining.
    pthread_exit(0);

    int *returnValue;

    for (int i = 0; i < 3; i++){
        if(pthread_join(th[i], (void**)&returnValue) != 0) return 2;
        printf("The returned value from thread %d is %d\n", i, *returnValue);
    }
    free(returnValue);
    return 0;
}
