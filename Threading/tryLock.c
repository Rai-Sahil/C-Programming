#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * Difference between trylock and lock
 * With trylock we are only trying to unlock the mutex;
 * @param argc
 * @param argv
 * @return
 */

pthread_mutex_t mutex;

void* routine(void* arg){
   if( pthread_mutex_trylock(&mutex) == 0){
       printf("Got the Lock\n");
       sleep(1);
       pthread_mutex_unlock(&mutex);
   } else {
       printf("Didn't Locked It...\n");
   }
}

/**
 * You can see only once it got the lock rest is just it didn't lock it because they are already locked.
 * Thats because tryLock only tries to lock as the thread 3 already locked the function it will just make other 3 threads
 * jump over it. So that only due to one length functions other thread don;t stop.
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char** argv) {

    pthread_t th[4];

    for (int i = 0; i < 4; i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0 ){
            perror("Error While Creating Thread");
        }
    }

    for (int i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL) != 0 ){
            perror("Error While Joining Thread");
        }
    }
    return 0;
}
