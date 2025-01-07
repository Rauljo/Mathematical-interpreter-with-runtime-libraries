#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Es el elemento que se guardará en cada nodo del arbol, contiene el lexema y código (componente léxico).
struct componente_lexico {
    char* cadena;
    double valor;
    double (*funcion)(double);
};

//Un nodo tendrá, además de su componente léxico (su valor), un hijo a izquierda y otro a derecha, ambos nodos igual que el.
struct nodo{
    struct componente_lexico* componente;
    struct nodo* izquierda;
    struct nodo* derecha;
};

//La estrctura de arbol comienza en un nodo cabeza.
struct arbol{
    struct nodo* cabeza;
};

/**
 * Funcion utilizada para crear un arbol, reservando la memoria y asignando su cabeza a NULL.
 * @return puntero al arbol.
 */
struct arbol* crear_arbol();

/**
 * Funcion utilizada para destruir todos los nodos del arbol, y el propio arbol en sí.
 * @param abin
 */
void destruir_arbol(struct arbol* abin);

/**
 * Funcion utilizada para saber si un árbol está vacio o contiene algún nodo.
 * @param abin
 * @return
 */
int esVacio_arbol(struct arbol* abin);

/**
 * Función que recorre el arbol recursivamente imprimiendo sus nodos.
 * @param abin
 */
void imprimir_arbol(struct arbol* abin);

/**
 * Esta la uso en el funcionamiento normal de la TS, para no tener que buscar e insertar por separado y aprovechar que ya sé la posición de inserción en la búsqueda
 * @param abin
 * @param componente
 * @return el componente lexico encontrado o insertado. En caso de encontrarlo, liberará la memoria del que se le ha enviado, y devolvera una referencia al que esta
 * en la TS.
 */
struct componente_lexico* busca_o_inserta_arbol(struct arbol* abin, char* cadena);

/**
 * Esta la utilizo durante la inicializacion de la TS, para insertar las palabras reservadas sin pararme a mirar si existen o no (buscar) porque doy por hecho que no existen
 * y así ahorro tiempo de condicionales.
 * @param abin
 * @param componente
 */
void inserta_arbol(struct arbol* abin, struct componente_lexico* componente);

void vaciar_arbol(struct arbol* abin);

struct componente_lexico* buscar_arbol(struct arbol* abin, char* cadena);