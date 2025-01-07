#include "Arbol.h"

/**
 * Funcion auxiliar de imprimir_arbol, para la impresión iterativa.
 * @param nodo
 */
void _imprimir_subs(struct nodo* nodo);

/**
 * Funcion auxiliar de destrui_arbol, para la destrucción iterativa.
 * @param nodo
 */
void _destruir_subs(struct nodo* nodo);

struct arbol* crear_arbol(){
    //Primero reservamos memoria para el arbol
    struct arbol* abin = (struct arbol*) malloc(sizeof(struct arbol));
    abin->cabeza = NULL; //Asignamos la cabeza a NULL.
    return abin;
}

void destruir_arbol(struct arbol* abin){
    if (abin->cabeza != NULL){
        _destruir_subs(abin->cabeza); //Destruimos todos los subarboles a derecha e izquierda.
    }

    //Al final destruimos el abrol, ya destruimos todos sus nodos
    free(abin);
}

void _destruir_subs(struct nodo* nodo){
    if (nodo != NULL){
        _destruir_subs(nodo->izquierda);
        _destruir_subs(nodo->derecha);

        free(nodo->componente->cadena);
        free(nodo->componente);
        free(nodo);

    }
}

int esVacio_arbol(struct arbol* abin){
    return (abin->cabeza == NULL);
}


void imprimir_arbol(struct arbol* abin){
    if (abin->cabeza == NULL){
        printf("VACÍO\n");
    }
    else{
        _imprimir_subs(abin->cabeza); //Imprimos todos los subarboles, a izquierda y derecha.
    }

    printf("\n");
}

void _imprimir_subs(struct nodo* nodo){
    if (nodo != NULL){
        _imprimir_subs(nodo->izquierda);
        _imprimir_subs(nodo->derecha);
        printf("%s --> %lf  ", nodo->componente->cadena, nodo->componente->valor);
    }
}

/*Al tener esta funcion para los dos propositos, conseguimos que no sea necesario primero buscarlo y despues insertarlo. Sino que si llegamos a
 * un nodo hoja NULL, significará que no existe, y ya lo insertamos en esa posición. No perdiendo tiempo en volver a buscar donde insertarlo
 * una vez ya se ha buscado para encontrarlo*/
struct componente_lexico* busca_o_inserta_arbol(struct arbol* abin, char* cadena){
    int comparacion = 0;
    struct nodo* nodo_actual = abin->cabeza;

    //Primero verificamos que el arbol no sea vacio y hay que crear la cabeza
    if (esVacio_arbol(abin)){
        abin->cabeza = (struct nodo*) malloc(sizeof(struct nodo));
        abin->cabeza->componente = (struct componente_lexico* ) malloc (sizeof(struct componente_lexico));
        abin->cabeza->componente->cadena=cadena;
        abin->cabeza->izquierda = NULL;
        abin->cabeza->derecha = NULL;

        return abin->cabeza->componente;

    }

    //Ya verificamos dentro del while si es null o no, asi que no hay que verificar nada al inicio. terminamos siempre en un return.
    while(1){
        //Comparamos el lexema del nodo donde estamos y el que buscamos.
        comparacion = strcmp(cadena, nodo_actual->componente->cadena);
        //Es menor.
        if (comparacion < 0){ //Nos movemos izquierda
            if (nodo_actual->izquierda == NULL){
                //En ese caso ya sabemos que no existe y que tenemos que insertar
                nodo_actual->izquierda = (struct nodo*) malloc(sizeof(struct nodo));
                nodo_actual->izquierda->componente = (struct componente_lexico* ) malloc (sizeof(struct componente_lexico));
                nodo_actual->izquierda->componente->cadena=cadena;
                nodo_actual->izquierda->izquierda = NULL;
                nodo_actual->izquierda->derecha = NULL;
                return nodo_actual->izquierda->componente;
            }
            else{
                //Seguimos buscando
                nodo_actual = nodo_actual->izquierda;
            }
        }
            //Es mayor.
        else if (comparacion > 0){ //Nos movemos derecha
            if (nodo_actual->derecha == NULL){
                //En ese caso ya sabemos que no existe y tenemos que insertar a la derecha
                nodo_actual->derecha = (struct nodo*) malloc(sizeof(struct nodo));
                nodo_actual->derecha->componente = (struct componente_lexico* ) malloc (sizeof(struct componente_lexico));
                nodo_actual->derecha->componente->cadena=cadena;
                nodo_actual->derecha->izquierda = NULL;
                nodo_actual->derecha->derecha = NULL;
                return nodo_actual->derecha->componente;
            }
            else{
                //Seguimos buscando
                nodo_actual = nodo_actual->derecha;
            }
        }
        else{ //Lo hemos encontrado
            //Liberamos el componente que nos han mandado
            free(cadena);

            //Devolvemos direccion a ese componente en la TS
            return nodo_actual->componente;
        }
    }


}

//En este caso, no verificamos si ya existe o no porque solo lo vamos a utilizar con las palabras reservadas, que no se repiten.
void inserta_arbol(struct arbol* abin, struct componente_lexico* componente){
    int comparacion =0;
    struct nodo* nodo_actual = abin->cabeza;

    if (esVacio_arbol(abin)){
        abin->cabeza = (struct nodo*) malloc(sizeof(struct nodo));
        abin->cabeza->componente = componente;
        abin->cabeza->izquierda = NULL;
        abin->cabeza->derecha = NULL;
    }
    else{
        while(1){
            comparacion = strcmp(componente->cadena, nodo_actual->componente->cadena);
            if (comparacion < 0){
                if (nodo_actual->izquierda == NULL){
                    //Llegamos al final, insertamos:
                    nodo_actual->izquierda = (struct nodo*) malloc(sizeof(struct nodo));
                    nodo_actual->izquierda->componente = componente;
                    nodo_actual->izquierda->izquierda = NULL;
                    nodo_actual->izquierda->derecha = NULL;
                    break;
                }
                else{
                    //Seguimos
                    nodo_actual = nodo_actual->izquierda;
                }
            }
            else{
                if (nodo_actual->derecha == NULL){
                    //Legamos el final, insertamos a derecha
                    nodo_actual->derecha = (struct nodo*) malloc(sizeof(struct nodo));
                    nodo_actual->derecha->componente = componente;
                    nodo_actual->derecha->izquierda = NULL;
                    nodo_actual->derecha->derecha = NULL;
                    break;
                }
                else{
                    //Seguimos
                    nodo_actual = nodo_actual->derecha;
                }
            }
        }
    }


}

void vaciar_arbol(struct arbol* abin){
    if (abin->cabeza != NULL){
        _destruir_subs(abin->cabeza); //Destruimos todos los subarboles a derecha e izquierda.
    }
    //Destruimos todos los subarboles. Pero no la cabeza.
    abin->cabeza = NULL;
}

struct componente_lexico* buscar_arbol(struct arbol* abin, char* cadena){
    int comparacion = 0;
    struct nodo* nodo_actual = abin->cabeza;

    if (esVacio_arbol(abin)){
        return NULL;
    }

    while(1){
        comparacion = strcmp(cadena, nodo_actual->componente->cadena);
        if (comparacion < 0 ){
            if (nodo_actual->izquierda == NULL){
                return NULL;
            }
            else{
                nodo_actual = nodo_actual->izquierda;
            }
        }
        else if (comparacion > 0 ){
            if (nodo_actual->derecha == NULL){
                return NULL;
            }
            else{
                nodo_actual = nodo_actual->derecha;
            }
        }
        else{
            return nodo_actual->componente;
        }
    }
}



