#ifndef PILA_H
#define PILA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif

//Un nodo contiene unicamente un número entero, que indicara según lo que busquemos.
struct nodo_pila{
    FILE *data;
    struct nodo_pila* siguiente;
};

struct Pila{
    struct nodo_pila* top;
};

/**
 * Funcion para crear la pila
 * @return
 */
struct Pila* crear_pila();

/**
 * Funcion para leer la cima de la pila sin desapilarla
 * @param pila
 * @return
 */
FILE* leer(struct Pila* pila);

/**
 * Funcion para introducir un nuevo elemento en la cima de la pila
 * @param pila
 * @param data
 */
void push(struct Pila* pila, FILE* data);

/**
 * Funcion para devolver el elemento que esta en la cima de la pila y eliminarlo
 * @param pila
 * @return
 */
FILE* pop(struct Pila* pila);

/**
 * Funcion para eliminar la pila y todos sus elementos.
 * @param pila
 */
void eliminar_pila(struct Pila* pila);

/**
 * Funcion para saber si la cima de la pila es NULL o no, lo que indica que está o no vacía.
 * @param pila
 * @return
 */
int es_vacia(struct Pila* pila);
