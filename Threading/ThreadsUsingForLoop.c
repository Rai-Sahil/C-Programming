#include <stdio.h>
#include <pthread.h>

/**
 * Mutex
 * Using lock Only one thread can access the part at one specific given time until the first thread comes in and unlock it.
 * At the start we will lock the function and after the first thread is done it will unlock it.
 * Protect the part of code from other thread executing it.
 */

int mails = 0;

pthread_mutex_t lock;

void *routine(){
    pthread_mutex_lock( &lock );
    for( int i = 0; i < 1000000; i++ ) mails++;
    pthread_mutex_unlock( &lock );
}

int main() {

    pthread_t th[4];

    /**
     * You'll notice that at first the thread 1 starts and then only after it finished the thread 2 starts,
     * It kinda breaks the whole core of threads, that's because the way we have created threads (Using For Loop).
     * The first thread is created then system waits for the task to be finished in thread, right after that the thread
     * is joined and then for loop runs again.
     * 
     * Never have both create and join inside one for loop.
     */

    //For loop to create the thread
    for ( int i = 0; i < 4; i++) {
        if ( pthread_create(&th[i], NULL, &routine, NULL) ) {
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    
    //For loop to join the thread
    for( int i = 0; i < 4; i++ ){
        if( pthread_join(th[i], NULL) ){
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }

    printf("Number of threads %d", mails);

    return 0;
}
