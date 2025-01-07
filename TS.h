//DE PRIMERAS VAMOS A CREAR LO MÁS SENCILLO DEL MUNDO, UNA PILA Y PUNTO, PARA VERIFICAR QUE TODO FUNCIONA CORRECTAMENTE
#include "Arbol.h"
#include "definiciones.h"
#include "math.h"

//TAD de manera que nuestra TS utilizará un arbol binario por detras en este caso. Arbol.h. Con tal de cambiar esto ya podríamos pasar de utilizar un abin a cualquier otra estructura.
//También habría que cambiar las funciones que se redigiren dentro de las funciones de la TS.
typedef struct arbol* TS;


/**
 * Esta función crea la TS (arbol) y la inicializa insertando todas las palabras reservadas que se definen en TS.c.
 * @return
 */
TS crear_e_inicializar_TS(TS tabla, int codigo);

/**
 * Esta función recurre a buscar_o_insertar del arbol para devolver el componente que ha sido insertado o que ya estaba en la TS.
 * @param tabla
 * @param componente
 * @return
 */
struct componente_lexico* existe_o_inserta_TS(TS tabla, char* cadena);

/**
 * Imprimimos la TS.
 * @param tabla
 */
void imprimir_TS(TS tabla);

/**
 * Eliminamos la TS y todos sus elementos.
 * @param tabla
 */
void eliminar_TS(TS tabla);

void vaciar_tabla(TS tabla);

TS crear_TS(TS tabla);

struct componente_lexico* buscar_TS(TS tabla, char* cadena);


