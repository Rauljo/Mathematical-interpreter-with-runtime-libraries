#include "errores.h"

void imprimir_error_sintactico(int codigo, const char* error, char* cadena){
    switch(codigo)
    {
        case NO_FUNCION:
            printf("%sERROR: La función \"%s\" no existe en ninguna libreria\n", RED, cadena);
            break;
        case NO_LIBRERIA:
            printf("%sERROR: la libreria \"%s\" no existe. RECUERDA QUE HAY QUE PROPORCIOANR LA RUTA AUNQUE SEA AÑADIENDO ./ AL INICIO\n", RED, cadena);
            printf("%s\n", error);
            break;
        case NO_VARIABLE:
            printf("%sERROR: la variable \"%s\" no tiene valor asignado\n", RED, cadena);
            break;
        case OTRO:
            printf("%sERROR: %s\n", RED,error);
            break;
        case CAMBIO_CONSTANTE:
            printf("%sERROR: no es posible modificar el valor de \"%s\", ya que es una constante\n", RED, cadena);
            break;
        default:
            break;
    }
    printf("%s", RESET);

}

void imprimir_error_lexico(int codigo){

}

void imprimir_error_archivo(int codigo, char* archivo){
    printf("%sERROR: No se ha podido abrir el archivo %s. RECUERDA QUE SOLO SE ACEPTAN ARCHIVOS .TXT EN LOAD\n", RED, archivo);
    printf("%s", RESET);
}

void imprimir_warning(int codigo){
    switch(codigo){
        case INDET:
            printf("%sWARNING: La división 0 / 0 es una indeterminación. Se fija su valor a 0\n", BLUE);
            break;
        default:
            break;
    }
    printf("%s", RESET);

}
