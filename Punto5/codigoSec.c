#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define MAXLON 1000

void *suma (char *);

int main (int argc, char *argv[]) { 

    if (argc != 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }
    clock_t start = clock();
    suma(argv[1]);
    printf("Tiempo transcurrido: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
    return 0;
}

void *suma (char *text) {
  int leidos, fd, suma = 0;
  char cadena[MAXLON];
  char texto[50] = ",";
  char* valor;

  fd = open(text ,O_RDONLY);
  while ((leidos = read(fd, cadena, MAXLON))!= 0) {
      strcat(texto, cadena);
      valor = strtok(texto, ",");
  }

  printf("Valores encontrados en el fichero: %s \n");
  while (valor != NULL) {
      suma = suma + atoi(valor);
      valor = strtok(NULL, ",");
  }  
  printf("Fichero %s: La suma de los valores es igual a: %d \n",text, suma);
  close(fd);
}