#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

/**
 * Race Conditions
 * When we use same function between threads. There can be a race conditions
 * But race condition will only happen if one or more thread takes longer than time.
 * Each thread will overlap each other data.
 */

int mails = 0;

void *routine(){
    for(int i = 0; i < 1000000; i++) mails++;
    // Read the value in mails
    // Increment the values
    // Write it back to the memory
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
