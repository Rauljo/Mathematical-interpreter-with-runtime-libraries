#include "calc.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"

void inicializar_bison();
void destruir_bison();

int main(){
    printf("%sBienvenido a la calculadora de expresiones matemáticas\n", GREEN);
    printf("%sIngrese una expresión matemática para ser evaluada\n", GREEN);
    printf("%sEjemplo: a = 2 + 3 * 4\n", GREEN);
    printf("%sPara salir del programa, teclee \"quit\"\n", GREEN);
    printf("%sSi necesita ayuda, teclee \"help\"\n", GREEN);
    printf("%s", RESET);
    inicializar_bison();
    yyparse();
    destruir_bison();
    return 0;
}
