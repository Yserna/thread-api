#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
#include <pthread.h>

void* factorial (void *arg);

int main (int argc, char *argv[]) {
    pthread_t hilos[argc-1];
    void* resultado1;

    if (argc < 2){
        printf ("Ingrese al menos un números entero.\n");
        exit(0);
    }

    for(int i=1; i<argc ;i++){
        pthread_create (&hilos[i], NULL, factorial, argv[i]);
    } 
    srand(time(0)); 

    for(int i=1; i<argc ;i++){
        pthread_join(hilos[i], (void *) &resultado1);
        printf ("El factorial de %s es %d\n", argv[i], resultado1);
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
        //sleep (random()%3);
    }
    printf("Identificador del hilo que ha finalizado: %lu \n", pthread_self());
    return (void*)resultado;
}