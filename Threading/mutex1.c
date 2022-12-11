#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
* Doing multiple operation on one thread is very dangerous.
 * That's why we use Mutex
 * Mutex: are used to block the thread until the thing is done
*/

pthread_mutex_t locked;

int a;

void process(void* x){
    pthread_mutex_lock(&locked);

    int i = 0;
    a++;

    while(i < 6){
        printf("%d", a);
        sleep(1);
        i++;

    }
    printf("...Finished...");

    pthread_mutex_unlock(&locked);
}

void print(){
    pthread_mutex_lock(&locked);
    printf("Hello World");
    pthread_mutex_unlock(&locked);
}

int main(){
    pthread_t thread1, thread2;

    if(pthread_mutex_init(&locked, NULL) != 0){
        printf("Mutex Not Created Successfully...");
        exit(1);
    }

    a = 0;

    pthread_create(&thread1, NULL, process, NULL);
    pthread_create(&thread1, NULL, print, NULL);
    pthread_create(&thread2, NULL, process, NULL);

    //To stop the thread for a bit
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    exit(0);
}
