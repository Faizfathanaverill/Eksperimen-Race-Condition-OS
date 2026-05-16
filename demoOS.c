#include <stdio.h>
#include <pthread.h>

long long counter = 0; 
pthread_mutex_t lock;


void* tambah_sejuta_kali(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock); 
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);

    printf("Ekspektasi hasil akhir counter: 2000000\n");

    pthread_create(&thread1, NULL, tambah_sejuta_kali, NULL);
    pthread_create(&thread2, NULL, tambah_sejuta_kali, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Realita hasil akhir counter : %lld\n", counter);
    printf("Selisih data yang hilang karena tabrakan: %lld\n", 2000000 - counter);

    pthread_mutex_destroy(&lock);
    return 0;
}