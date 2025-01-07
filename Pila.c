#include "Pila.h"

struct Pila* crear_pila(){
    struct Pila* pila = (struct Pila*)malloc(sizeof(struct Pila));
    if (pila == NULL){
        perror("No se ha podido crear la pila\n");
        exit(EXIT_FAILURE);
    }
    //pila->top = NULL;
    pila->top = (struct nodo_pila*)malloc(sizeof(struct nodo_pila));
    pila->top->data = stdin; //Con la entrada estandar como fondo de pila
    pila->top->siguiente = NULL;
    return pila;
}

FILE * leer(struct Pila* pila){
    if (es_vacia(pila)){
        return NULL;
    }
    return pila->top->data;
}

void push(struct Pila* pila, FILE* data){
    struct nodo_pila* nodo = (struct nodo_pila*)malloc(sizeof(struct nodo_pila));
    nodo->data = data;
    nodo->siguiente = pila->top;
    pila->top = nodo;
}

FILE* pop(struct Pila* pila){
    //Por ahora no añadimos comprobacion de pila vacia
    if (es_vacia(pila)){
        return NULL;
    }
    struct nodo_pila* temp = pila->top;
    FILE* data = temp->data;
    pila->top = temp->siguiente;
    free(temp);
    return data;
}

void eliminar_pila(struct Pila* pila){
    while (!es_vacia(pila)){
        pop(pila);
    }
    //pop(pila); //para sacar el símbolo de fondo de pila (0)
    free(pila->top);
    free(pila);
}

int es_vacia(struct Pila* pila){
    return (pila->top->data == stdin);
}


