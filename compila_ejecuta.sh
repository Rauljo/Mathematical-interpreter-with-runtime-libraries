#!/bin/bash

lex calc.l 
bison -d calc.y
gcc -o interprete errores.c Arbol.c calc.tab.c lex.yy.c main.c Pila.c TS.c -lm -Wall

# Verifica si el primer argumento es "valgrind"
if [ "$1" == "valgrind" ]; then
    # Ejecuta el comando "valgrind ./interprete"
    valgrind ./interprete
else
    # Ejecuta solo "./interprete"
    ./interprete
fi
