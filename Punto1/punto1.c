#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
#include <pthread.h>

void* factorial (void *arg);

int main (int argc, char *argv[]) {
    void* resultado1;
    void* resultado2;

    if (argc == 3) {
        pthread_t hilo1, hilo2;
        pthread_create(&hilo1, NULL, factorial, argv[1]);
        pthread_create(&hilo2, NULL, factorial, argv[2]);
        
        pthread_join(hilo1, (void *) &resultado1);
        pthread_join(hilo2, (void *) &resultado2);

        printf ("El factorial de %s es %d\n", argv[1], resultado1);
        printf ("El factorial de %s es %d\n", argv[2], resultado2);

     } else {
        printf ("Ingrese los dos números enteros.\n");
        exit(0);
    }
    return 0;
}

void* factorial (void *arg) {
    long long int resultado= 1;
    int n = atoi(arg);
    int num;
    for (num= 2; num<= n; num++) {
        resultado= resultado*num;
        printf ("Factorial de %d, resultado parcial %lld\n", n, resultado);
        sleep (random()%3);
    }
    return (void*)resultado;
}