#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int numIterations;
int minRandomNumber;
int maxRandomNumber;
int targetRandomNumber;
int exitCondition = 0;

struct ChildThreadArgs {
    int thread_id;
    char *message;
};

void *printMessage(void *arg) {
    struct ChildThreadArgs *args = (struct ChildThreadArgs *)arg;
    for (int i = 0; i < numIterations; i++) {
        if (exitCondition) {
            printf("Thread %d: Exiting.\n", args->thread_id);
            break;
        }
        printf("Thread %d: %s - Iteration %d\n", args->thread_id, args->message, i+1);
        sleep(1);
    }
    return NULL;
}
void *generate_random_function(void *arg) {
    struct ChildThreadArgs *args = (struct ChildThreadArgs *)arg;
    srand(time(NULL) + args->thread_id);
    for (int i = 0; i < numIterations; i++) {
        if (exitCondition) {
            printf("Thread %d: Exiting.\n", args->thread_id);
            break;
        }
        int randomNumber = minRandomNumber + rand() % (maxRandomNumber - minRandomNumber + 1);
        printf("Thread %d: Generated random number %d\n", args->thread_id, randomNumber);
        if (randomNumber == targetRandomNumber) {
            printf("Thread %d: Target number %d generated. Setting exit condition.\n", args->thread_id, randomNumber);
            exitCondition = 1;
            break;
        }
        sleep(1);
    }
    return NULL;
}

int main() {
    printf("Enter the number of iterations: ");
    scanf("%d", &numIterations);
    printf("Enter the minimum random number: ");
    scanf("%d", &minRandomNumber);
    printf("Enter the maximum random number: ");
    scanf("%d", &maxRandomNumber);
    printf("Enter the target random number: ");
    scanf("%d", &targetRandomNumber);

    pthread_t threads[2];
    struct ChildThreadArgs args1 = {1, "Printed by thread"};
    struct ChildThreadArgs args2 = {2, "Random number by thread"};

    if (pthread_create(&threads[0], NULL, &printMessage, (void *)&args1)) {
        perror("Error creating thread 1");
        return 1;
    }
    if (pthread_create(&threads[1], NULL, &generate_random_function, (void *)&args2)) {
        perror("Error creating thread 2");
        return 1;
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: All child threads have completed.\n");
    return 0;
}
