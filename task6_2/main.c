#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    char *name;
    char *str;
    int num;
} threadParams;

void *threadFunction(void *arg) {
    threadParams *params = (threadParams *)arg;
    for (int i = 1; i <= params->num; i++) {
        printf("%s. %s %d\n", params->name, params->str, i);
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    threadParams params[4] = {
        {"Thread 1", "Iteration", 10},
        {"Thread 2", "Iteration", 10},
        {"Thread 3", "Iteration", 10},
        {"Thread 4", "Iteration", 10}
    };
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, threadFunction, (void *)&params[i]);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
