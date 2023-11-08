#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *childThreadFunction() {
    for (int i = 1; i <= 10; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
    return NULL;
}
int main() {
    pthread_t cThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&cThread, &attr,
                   childThreadFunction, NULL);

    for (int i = 1; i <= 10; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
    pthread_join(cThread, NULL);
    return 0;
}

