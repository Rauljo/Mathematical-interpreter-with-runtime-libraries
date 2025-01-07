%{

#define MAX_LIBRERIAS_IMPORTADAS 100

#include <stdio.h>
#include <stdlib.h>
#include "TS.h"
#include "lex.yy.h"
#include "errores.h"
#include "definiciones.h"
#include <dlfcn.h>

struct componente_lexico* componente;

//Lista de librerias:
char* librerias_importadas[MAX_LIBRERIAS_IMPORTADAS];
int num_librerias_importadas = 0;

TS tabla_vars;
TS tabla_funct;
TS tabla_const;
int print_activo=1;
int print_activo_temp=1;
int hubo_error = 0;

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void inicializar_bison();
void destruir_bison();
void empty_workspace();
void imprimir_ayuda();
double encuentra_var(char* $1);
void gestionar_impresion(double $1);
void eliminar_lista_libs();

void abrir_archivo(char* $2);
void inicializar_lexico();
void destruir_lexico();

void yyerror(const char* s);
%}

%union {
    double val; //Float value
    char* cadena;
}

%type <val> expr asign functs

%token <cadena> VAR ARCHIVO LIBRERIA
%token <val> NUM

%token NEWLINE QUIT WORKSPACE CLEAR LOAD HELP IMPORT PRINT ON OFF PUNTO_COMA
%right IGUAL
%token ABRE CIERRA
%left IGUALIGUAL MAYORIGUAL MAYOR MENOR MENORIGUAL NOIGUAL 
%left PLUS MINUS 
%left DIV MULT 
%left NEG






%start input



%%

input:          { printf(">> "); }
    | input line
;

line: NEWLINE {printf("\n>> ");}
    | expr NEWLINE { if (hubo_error == 0) {gestionar_impresion($1);} else {hubo_error = 0; print_activo_temp = print_activo; {printf("\n>> ");} } }
    | expr PUNTO_COMA NEWLINE { if (print_activo == 1) {print_activo_temp = 0;} else{print_activo_temp = 1;} gestionar_impresion($1); }
    | QUIT NEWLINE { printf("%s\tADIOS!!!!\n", GREEN); printf("%s", RESET); destruir_bison(); exit(0); }
    | WORKSPACE NEWLINE { printf("%s#################################WORKSPACE ACTUAL############################\n", GREEN); imprimir_TS(tabla_vars); printf("#############################################################################\n"); printf("%s>> ", RESET);}
    | CLEAR NEWLINE { printf("%sReseteando workspace... \n", GREEN); printf("%s>> ", RESET); empty_workspace(); }
    | LOAD ARCHIVO {
                        printf("%sEjecutando archivo: %s\n", GREEN, $2); printf("%s>> ", RESET);
                        abrir_archivo($2); //abrimos y apilamos el archivo
                        free($2);
                    }
    | HELP NEWLINE { imprimir_ayuda(); }
    | IMPORT LIBRERIA                    { void *libreria = dlopen($2, RTLD_LAZY); //probamos a abrir la libreria para ver si existe y guardamos la cadena para abrirla en la lista
                                          if (libreria) {
                                            dlclose(libreria);
                                            librerias_importadas[num_librerias_importadas] = $2;
                                            num_librerias_importadas++;
                                            printf("%sLibreria %s cargada correctamente\n", GREEN, $2); printf("%s>> ", RESET);
                                          }
                                          else{
                                            imprimir_error_sintactico(NO_LIBRERIA, dlerror(), $2);
                                          }
                                        }
    | PRINT ON { print_activo = 1; print_activo_temp = 1; }
    | PRINT OFF { print_activo = 0; print_activo_temp = 0;}
    | error {}
;

expr:  NUM                               { $$ = $1; }
    | VAR                               { $$ = encuentra_var($1); componente = NULL; free($1); } //buscamos la variable y devolvemos su valor
    | expr PLUS expr                    { $$ = $1 + $3; }
    | expr MINUS expr                   { $$ = $1 - $3; }
    | expr MULT expr                    { $$ = $1 * $3; }
    | expr DIV expr                     { if ($1 == 0 && $3 == 0) { $$ = 0.0; imprimir_warning(INDET); } else {$$ = $1 / $3;} }
    | expr IGUALIGUAL expr              { $$ = $1 == $3; }
    | expr MAYORIGUAL expr              { $$ = $1 >= $3; }
    | expr MENOR expr                   { $$ = $1 < $3; }
    | expr MAYOR expr                   { $$ = $1 > $3; }
    | expr NOIGUAL expr                 { $$ = $1 != $3; }
    | expr MENORIGUAL expr              { $$ = $1 <= $3; }
    | MINUS expr %prec NEG		{ $$ = -$2; }
    | ABRE expr CIERRA			{ $$ = $2; }
    | functs
    | asign

;

asign: VAR IGUAL expr                    {
                                             if (hubo_error == 1){ //alguna variable de la expresion no existia. 
                                                free($1);
                                             }
                                             else{
                                                componente = buscar_TS(tabla_const, $1); //buscamos si es una constante
                                                 if (componente != NULL){
                                                     //En ese caso, intentamos cambiar el valor de una constante
                                                     imprimir_error_sintactico(CAMBIO_CONSTANTE, NULL, $1);
                                                     free($1);
                                                 }
                                                 else{
                                                     componente = existe_o_inserta_TS(tabla_vars,$1); //buscamos la variable o la insertamos
                                                     componente->valor = $3; //ajustamos el valor
                                                     $$ = $3;
                                                     componente = NULL;
                                                 }
                                             }

                                         }
;

functs: VAR ABRE expr CIERRA              {
                                             int encontrada = 0;
                                             componente = buscar_TS(tabla_funct, $1); //buscamos la funcion
                                             if (componente != NULL){
                                                free($1);
                                                $$ = componente->funcion($3); //calculamos
                                                componente=NULL;
                                             }

                                             else{ //No existe tal funcion, la buscamos:
                                                for (int i = 0; i < num_librerias_importadas; i++){ //La buscamos en todas las librerias disponibles
                                                    void *libreria = dlopen(librerias_importadas[i], RTLD_LAZY);
                                                    if (libreria){
                                                        double (*funcion)(double) = dlsym(libreria, $1); //buscamos la funcion
                                                        if (funcion){
                                                            componente = existe_o_inserta_TS(tabla_funct, $1); //introducimos la funcion en la tabla de funciones
                                                            componente->funcion = funcion;
                                                            $$ = componente->funcion($3); //calculamos y salimos
                                                            componente=NULL;
                                                            dlclose(libreria);
                                                            encontrada = 1;
                                                            break;
                                                        }
                                                        dlclose(libreria);
                                                    }
                                                }
                                                if (encontrada == 0){
                                                    imprimir_error_sintactico(NO_FUNCION, NULL, $1);
                                                }
                                             }

                                         }
;

%%

void yyerror(const char* s) {
	imprimir_error_sintactico(OTRO,s, NULL);
}

void inicializar_bison(){
    tabla_vars = crear_TS(tabla_vars);
    tabla_funct = crear_e_inicializar_TS(tabla_funct, FUNS);
    tabla_const = crear_e_inicializar_TS(tabla_const, CONS);
    inicializar_lexico();
}

void destruir_bison(){
    eliminar_TS(tabla_vars);
    eliminar_TS(tabla_funct);
    eliminar_TS(tabla_const);
    eliminar_lista_libs();
    destruir_lexico();
}

//Al terminar, eliminamos las librerias guardadas
void eliminar_lista_libs(){
    for (int i = 0; i < num_librerias_importadas; i++){
        if (librerias_importadas[i] != NULL){
            free(librerias_importadas[i]);
        }
    }
}

void empty_workspace(){
    vaciar_tabla(tabla_vars);
}

//Encontrar el valor de una variable buscando primero en la lista de constantes y despues en la de variables. 
double encuentra_var(char* $1){
    //primero buscamos en constantes
    componente = buscar_TS(tabla_const, $1);
    if (componente == NULL){
        componente = buscar_TS(tabla_vars, $1);
        if (componente == NULL){
            imprimir_error_sintactico(NO_VARIABLE, NULL, $1);
            hubo_error = 1;
            return 0.0;
        }
        else{
            return componente->valor;
        }
    }
    else{
        return componente->valor;
    }

}

// Para ver si es necesario imprimir teniendo en cuenta si aparece punto y coma
void gestionar_impresion(double $1){
    if (print_activo != print_activo_temp){
        if (print_activo_temp == 1){
            printf("%s%lf\n", GREEN, $1);
        }
        print_activo_temp = print_activo;
    }
    else{
        if (print_activo == 1){
            printf("%s%lf\n", GREEN, $1);
        }
    }
    printf("%s>> ", RESET);
}


void imprimir_ayuda(){
    printf("%sBienvenido a la calculadora!\n", BLUE);
        printf("%sOperaciones disponibles:\n", CYAN);
        printf("  %s+ : Suma\n", GREEN);
        printf("  %s- : Resta\n", GREEN);
        printf("  %s* : Multiplicación\n", GREEN);
        printf("  %s/ : División\n", GREEN);

        printf("%sOperaciones lógicas disponibles:\n", CYAN);
        printf("  %s== : Igual a\n", GREEN);
        printf("  %s<= : Menor o igual que\n", GREEN);
        printf("  %s>= : Mayor o igual que\n", GREEN);
        printf("  %s>  : Mayor que\n", GREEN);
        printf("  %s<  : Menor que\n", GREEN);
        printf("  %s!= : Diferente de\n", GREEN);

        printf("%sOperaciones complejas disponibles:\n", CYAN);
        printf("  %sacos, asin, atan, cos, sin, exp, log, log10, sqrt, ceil, fabs, floor, tan\n", GREEN);

        printf("%sCómo se lleva a cabo la asignación de variables:\n", CYAN);
        printf("  %sEjemplo: a = 3 + 4\n", GREEN);

        printf("%sCómo utilizar las operaciones complejas:\n", CYAN);
        printf("  %sEjemplo: sin(a)\n", GREEN);

        printf("%sFunciones extra:\n", CYAN);
        printf("  %squit : Para salir\n", GREEN);
        printf("  %sclear : Para liberar todas las variables del workspace\n", GREEN);
        printf("  %sworkspace : Para imprimir una lista de las variables usadas y sus valores\n", GREEN);
        printf("  %shelp : Para mostrar ayuda de la calculadora\n", GREEN);

        printf("%sPara cargar un archivo de ejemplo.txt, haz lo siguiente:\n", CYAN);
        printf("  %sload prueba.txt : Se ejecutarán las operaciones registradas en el archivo.\n", GREEN);

        printf("%sPara utilizar una libreria externa enlazándola dinámicamente utilizaremos la instrucción IMPORT de la siguiente manera:\n", CYAN);
        printf("  %simport ./libprueba.so : Así, se cargará la libreria. A partir de ese momento podremos utilizar cualquier función que incluya\n", GREEN);
        printf("%sES MUY IMPORTANTE INCLUIR EL PATH A LA LIBRERIA Y NO SOLO SU NOMBRE, YA QUE SINO NO FUNCIONARÁ\n", CYAN);

        printf("%s>> ", RESET); // Restablecer el color a los valores predeterminados

}

