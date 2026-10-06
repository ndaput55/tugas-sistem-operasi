#include <stdio.h>
#include <pthread.h>

int selesai = 0;
pthread_mutex_t mutex;

void* faktorial(void* arg) {
    int n = 5;
    int hasil = 1;

    for (int i = 1; i <= n; i++) {
        hasil *= i;
    }

    printf("Thread 1 - Faktorial: %d! = %d\n", n, hasil);

    pthread_mutex_lock(&mutex);
    selesai++;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* fibonacci(void* arg) {
    int n = 8;
    int a = 0, b = 1;

    printf("Thread 2 - Fibonacci: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", a);

        int berikutnya = a + b;
        a = b;
        b = berikutnya;
    }

    printf("\n");

    pthread_mutex_lock(&mutex);
    selesai++;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* baca_file(void* arg) {
    FILE* file = fopen("pesan.txt", "r");
    int karakter;

    if (file == NULL) {
        printf("Thread 3 - File tidak ditemukan.\n");
    } else {
        printf("Thread 3 - Isi file: ");

        while ((karakter = fgetc(file)) != EOF) {
            putchar(karakter);
        }

        printf("\n");
        fclose(file);
    }

    pthread_mutex_lock(&mutex);
    selesai++;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    pthread_mutex_init(&mutex, NULL);

    printf("Program dimulai\n");

    pthread_create(&t1, NULL, faktorial, NULL);
    pthread_create(&t2, NULL, fibonacci, NULL);
    pthread_create(&t3, NULL, baca_file, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nSemua thread selesai.\n");
    printf("Jumlah thread selesai: %d dari 3\n", selesai);

    pthread_mutex_destroy(&mutex);

    return 0;
}