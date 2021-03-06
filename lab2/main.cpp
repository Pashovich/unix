#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

int state = 0;
using namespace std;

void *provider(void*) {
    while(true) {
        pthread_mutex_lock(&mutex);
        if (state == 1){
            pthread_mutex_unlock(&mutex);
            continue;
        }
        state = 1;
        cout << "provided \n";
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void *consumer(void*) {
    while (true)
    {             
        pthread_mutex_lock(&mutex);
        while(state == 0) {
            pthread_cond_wait(&cond, &mutex);
            
        }
        state = 0;
        cout << "consumed \n\n";
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