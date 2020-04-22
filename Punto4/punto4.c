#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLON 1000

void *cuenta (char *);

int main (int argc, char *argv[]) { 
    pthread_t hilos[argc];

    if (argc < 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }

    for(int i=1; i<argc ;i++){
        pthread_create(&hilos[i], NULL, cuenta, argv[i]);
    } 
    srand(time(0)); 

    for(int i=1; i<argc ;i++){
        pthread_join(&hilos[i], NULL);
    }
    return 0;
}

void *cuenta (char *nombre) {
  int pos, cont= 0, leidos;
  char cadena[MAXLON];
  int fd;
  fd= open(nombre,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos < leidos; pos++) {
      if ((cadena[pos]== 'a') || (cadena[pos]== 'A')) {
        cont++;
      }
    }
  }
  printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
  close(fd);
}