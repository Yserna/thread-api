#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <malloc.h>

#define MAXLON 1000
typedef struct sumData {
    int * valores;
    int min;
    int max;
} sumData;

void * suma (void * );
void *vector (char *);

int main (int argc, char *argv[]) { 

    if (argc != 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }
    
    clock_t start = clock();
    vector(argv[1]);
    printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
    return 0;
}

void *vector (char *text) {
    int leidos, fd, cont = 0, i = 0, result = 0;
    int *sumHilo1 = NULL;
    int *sumHilo2 = NULL;
    char cadena[MAXLON];
    char texto[50] = ",";
    int *valores = malloc(sizeof(int));
    char* valor;
    sumData * sum1;
    sumData * sum2;

    fd = open(text ,O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON))!= 0) {
        strcat(texto, cadena);
        valor = strtok(texto, ",");
    }
    
    printf("Valores encontrados en el fichero: %s \n");
    while (valor != NULL) {
        valores = realloc(valores,(cont+1)*sizeof(int));
        valores[cont] = atoi(valor);
        cont++;
        valor = strtok(NULL, ",");
    }  

    sum1 = malloc(sizeof(*sum1));
    sum2 = malloc(sizeof(*sum2));
    sum1->valores = valores;
    sum1->min = 0;
    sum1->max = cont/2;
    sum2->valores =  valores;
    sum2->min = cont/2;
    sum2->max = cont;

    pthread_t hilo1, hilo2;
    pthread_create(&hilo1, NULL, suma, sum1);
    pthread_create(&hilo2, NULL, suma, sum2);
    
    pthread_join(hilo1, (void *)&sumHilo1);
    pthread_join(hilo2, (void *)&sumHilo2);

    result = *sumHilo1 + *sumHilo2;
    
    printf("Fichero %s: La suma de los valores es igual a: %d \n",text, result);
    close(fd);
}

void * suma (void * data) {
    sumData * info = data;
    int * valores = info->valores;
    int min = info->min;
    int max = info->max;
    int  result = 0;
    for(int i = min; i < max; i++){
        result = result + valores[i];
    }
    int *returnS = malloc(sizeof(returnS));
    *returnS = result;  
    return returnS;
}