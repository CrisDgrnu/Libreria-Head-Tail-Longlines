#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"

int main (int argc, char* argv[]){
    int n_lines;
    int opt;
    if (argc !=3)
    {
        fprintf(stderr,"Uso: %s opcion lineas\n",argv[0]);
        printf("Opcion 1 - 1 N - head(N) -> Muestra las N primeras lineas leidas por entrada estandar\n");
        printf("Opcion 2 - 2 N - tail(N) -> Muestra las N utlimas lineas leidas por entrada estandar\n");
        printf("Opcion 3 - 3 N - longlines(N) -> Muestra las N lineas mas largas leidas por entrada estandar\n");
        exit(EXIT_FAILURE);
    }

    opt = atoi(argv[1]);
    n_lines = atoi(argv[2]);

    if (opt == 1){
        head(n_lines);
    } else if (opt == 2){
        tail(n_lines);
    } else if (opt == 3){
        longlines(n_lines);
    } else{
        printf("Argumentos incorrectos\n");
    }
    
    return 0;
}