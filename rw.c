#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t wr, mutex;
int a = 0;
int readcount = 0; // Initialize readcount

void *reader(void *arg) {
    long int num;
    num = (long int)arg;

    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1) {
        pthread_mutex_lock(&wr);
    }
    pthread_mutex_unlock(&mutex);

    printf("The Reader %ld is in critical section\n", num);
    printf("The Reader %ld is reading data %d\n", num, ++a);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0) {
        pthread_mutex_unlock(&wr);
    }
    pthread_mutex_unlock(&mutex);

    printf("The Reader %ld left critical section\n", num);
}

void *writer(void *arg) {
    long int num;
    num = (long int)arg;

    pthread_mutex_lock(&wr);
    printf("Writer %ld have written data as %d\n", num, ++a);
    sleep(1);
    pthread_mutex_unlock(&wr);

    printf("Writer %ld left critical section\n", num);
}

int main() {
    pthread_t r[10], w[10];
    long int i, j;

    pthread_mutex_init(&wr, NULL); // Initialize mutex variable
    pthread_mutex_init(&mutex, NULL);

    printf("Enter readers and writers:\n");
    // Create reader and writer threads

    int nor, now;
    scanf("%d %d", &nor, &now);

    for (i = 0; i < nor; i++) {
        pthread_create(&r[i], NULL, reader, (void *)i);
    }

    for (j = 0; j < now; j++) {
        pthread_create(&w[j], NULL, writer, (void *)j);
    }

    for (i = 0; i < nor; i++) {
        pthread_join(r[i], NULL);
    }

    for (j = 0; j < now; j++) {
        pthread_join(w[j], NULL);
    }

    return 0;
}
