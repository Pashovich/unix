#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond;
pthread_mutex_t mutex;


void *provider(void*) {
    while(true) {
        pthread_mutex_lock(&mutex);
        std::cout << "provider\n";
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void *consumer(void*) {
    while(true) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        std::cout << "consumer\n\n";
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t thread1, thread2;

    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread2, nullptr, consumer, nullptr);
    pthread_create(&thread1, nullptr, provider, nullptr);
    

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}