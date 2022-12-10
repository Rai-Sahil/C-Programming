#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


void count() {
    int i = 0;
    while (i != 1000000000) {
        i++;
    }
}

int count2() {
    int i = 0;
    while (i != 1000000000) {
        i++;
    }
}

int main() {
    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, count, NULL);
    pthread_create(&thread2, NULL, count2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
//    count();
//    count2();

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;

    printf("Time measured: %.3f seconds.\n", elapsed);
}
