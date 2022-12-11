#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

/**
 * Mutex
 * Using lock Only one thread can access the part at one specific given time until the first thread comes in and unlock it.
 * At the start we will lock the function and after the first thread is done it will unlock it.
 * Protect the part of code from other thread executing it.
 */

int mails = 0;

pthread_mutex_t lock;

void *routine(){
    pthread_mutex_lock(&lock);
    for(int i = 0; i < 1000000; i++) mails++;
    pthread_mutex_unlock(&lock);
}

int main() {

    pthread_t p1, p2;

    if(pthread_create(&p1, NULL, &routine, NULL) != 0) return 1;
    if(pthread_create(&p2, NULL, &routine, NULL) != 0) return 2;
    if(pthread_join(p1, NULL) != 0) return 3;
    if(pthread_join(p2, NULL) != 0) return 4;

    printf("Number of threads %d", mails);

    return 0;
}
