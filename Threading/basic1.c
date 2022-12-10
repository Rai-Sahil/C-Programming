#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *func(void *var){
    sleep(2);
    printf("Hello World With Thread\n");
    return NULL;
}

int main(){
    //We always need thread ID;
    pthread_t t_id;
    printf("Before Thr Thread\n");

    /**
     * Used to create a thread
     * @param thread ID it is a pointer
     * @param
     * @param function that is we called is doing it's own things
     * @param used to pass the arguments in the function we added before
     */
    pthread_create(&t_id, NULL, func, NULL);

    /**
     * Basically is the wait functions, it blocks/stops the thread until te first argument is met
     */
    pthread_join(t_id, NULL);

    printf("After The Thread\n");

    exit(0);
}
