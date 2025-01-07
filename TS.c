#include "TS.h"

#define NUM_CONSTS 2
#define NUM_FUNCTS 13



char* constantes[] = {"pi", "e"};
double valores_constantes[] = {3.141592, 2.718281};

char* funciones[] = {"acos", "asin", "atan", "cos", "sin", "exp", "log", "log10", "sqrt", "ceil", "fabs", "floor", "tan"};
double (*funciones_math[])(double) = {acos, asin, atan, cos, sin, exp, log, log10, sqrt, ceil, fabs, floor, tan};

TS crear_e_inicializar_TS(TS tabla, int codigo){
    struct componente_lexico* componente = NULL;
    //Creamos la TS.
    tabla = crear_arbol();
    //Ahora insertamos todas las palabras reservadas
    if (codigo == FUNS){
        for (int i = 0; i< NUM_FUNCTS; i++){
            //Creamos el componente a insertar
            componente = (struct componente_lexico*) malloc(sizeof(struct componente_lexico));
            //+1 para que strncpy añada el \0 al final
            componente->cadena = (char*) malloc((strlen(funciones[i])+1) * sizeof(char));
            strncpy(componente->cadena, funciones[i], strlen(funciones[i]));
            componente->cadena[strlen(funciones[i])] = '\0';
            componente->funcion = funciones_math[i];

            //Ahora que ya tenemos creado el componente lo insertamos
            inserta_arbol(tabla, componente);
        }
    }
    else if (codigo == CONS){
        for (int i = 0; i< NUM_CONSTS; i++){
            //Creamos el componente a insertar
            componente = (struct componente_lexico*) malloc(sizeof(struct componente_lexico));
            //+1 para que strncpy añada el \0 al final
            componente->cadena = (char*) malloc((strlen(constantes[i])+1) * sizeof(char));
            strncpy(componente->cadena, constantes[i], strlen(constantes[i]));
            componente->cadena[strlen(constantes[i])] = '\0';
            componente->valor = valores_constantes[i];

            //Ahora que ya tenemos creado el componente lo insertamos
            inserta_arbol(tabla, componente);
        }
    }

    return tabla;

}

TS crear_TS(TS tabla){
    tabla = crear_arbol();
    return tabla;
}

struct componente_lexico* existe_o_inserta_TS(TS tabla, char* cadena){
    return busca_o_inserta_arbol(tabla, cadena);
}

void imprimir_TS(TS tabla){
    imprimir_arbol(tabla);
}

void eliminar_TS(TS tabla){
    destruir_arbol(tabla);
}

void vaciar_tabla(TS tabla){
    vaciar_arbol(tabla);
}

struct componente_lexico* buscar_TS(TS tabla, char* cadena){
    return buscar_arbol(tabla, cadena);
}
