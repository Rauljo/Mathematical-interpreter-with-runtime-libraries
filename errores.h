#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definiciones.h"

#define NO_LIBRERIA 1010
#define NO_FUNCION 1011
#define NO_VARIABLE 1012
#define OTRO 1013
#define NO_ARCHIVO 1014
#define CAMBIO_CONSTANTE 1015
#define INDET 1016

void imprimir_error_sintactico(int codigo, const char* error, char* cadena);
void imprimir_error_lexico(int codigo);
void imprimir_error_archivo(int codigo, char* archivo);
void imprimir_warning(int codigo);