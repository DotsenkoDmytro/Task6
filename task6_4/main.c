#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadArgs {
    int n;
    unsigned long long *catalanNumbers;
};

unsigned long long calculateCatalan(int n) {
    if (n <= 1) {
        return 1;
    }
    unsigned long long result = 0;
    for (int i = 0; i < n; i++) {
        result += calculateCatalan(i) * calculateCatalan(n - i - 1);
    }
    return result;
}

int isPrime(int number) {
    if (number <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}

void *catalanThreadFunction(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    for (int i = 0; i <= args->n; i++) {
        args->catalanNumbers[i] = calculateCatalan(i);
    }
    pthread_exit(NULL);
}

void *primeThreadFunction(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int primeCount = 0;
    for (int j = 2; j <= args->catalanNumbers[args->n]; j++) {
        if (isPrime(j)) {
            primeCount++;
        }
    }
    printf("Thread: Count of Prime Numbers for Catalan Number %llu: %d\n",
           args->catalanNumbers[args->n], primeCount);
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the number 'N' of Catalan Numbers to calculate: ");
    scanf("%d", &n);

    unsigned long long *catalanNumbers = malloc((n + 1) * sizeof(unsigned long long));

    if (catalanNumbers == NULL) {
        fprintf(stderr, "Failed to allocate memory for Catalan numbers.\n");
        return 1;
    }

     struct ThreadArgs args = {n, catalanNumbers};

    pthread_t catalan_thread, prime_thread;
    pthread_create(&catalan_thread, NULL, catalanThreadFunction, &args);
    pthread_join(catalan_thread, NULL);
    pthread_create(&prime_thread, NULL, primeThreadFunction, &args);
    pthread_join(prime_thread, NULL);
    free(catalanNumbers);
    return 0;
}
