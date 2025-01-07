%option noyywrap
%option nounput
%option noinput
%option header-file="lex.yy.h"
%option outfile="lex.yy.c"

%{
#include <stdio.h>
#include "Pila.h"

#define YY_DECL int yylex()

void abrir_archivo(char* archivo);
void cerrar_archivo();
void inicializar_lexico();
void destruir_lexico();

#include "calc.tab.h"
#include "TS.h"
#include "definiciones.h"
#include "errores.h"

//para ir guardando los archivos y poder ejecutar un archivo desde la ejecucion de otro archivo
struct Pila* pila_archivos_pendientes;

%}

DIGIT [0-9]
INT_SIN_GUION {DIGIT}+
INT_CON_GUION {DIGIT}[{DIGIT}_]*{DIGIT}
INT_CON_O_SIN_GUION ({INT_SIN_GUION}|{INT_CON_GUION})
HEXADECIMAL 0[xX][0-9a-fA-F]+

EXTENSION_CIENTIFICO ([eE][+-]?{INT_CON_O_SIN_GUION})

FLOAT_ANTES_PUNTO {INT_CON_O_SIN_GUION}\.{INT_CON_O_SIN_GUION}?
FLOAT_DESPUES_PUNTO \.{INT_CON_O_SIN_GUION}
FLOTANTE ({FLOAT_ANTES_PUNTO}|{FLOAT_DESPUES_PUNTO})

LETRA_GUION [a-zA-Z_]
LETRA_GUION_NUM [a-zA-Z0-9_]
IDENTIFICADOR {LETRA_GUION}{LETRA_GUION_NUM}*

PATH (\.|{IDENTIFICADOR})*(\/{IDENTIFICADOR})*(\/{IDENTIFICADOR})


%%

"quit"     {return QUIT;}
"workspace"|"WORKSPACE" {return WORKSPACE;}
"clear" { return CLEAR; }
"load" { return LOAD; }
"help" { return HELP; }
"import" { return IMPORT; }
"print" { return PRINT; }
"on" { return ON; }
"off" { return OFF; }

[ \t] ; //Ignora espacios en blanco
{HEXADECIMAL} { yylval.val = atof(yytext); return NUM; }
{INT_CON_O_SIN_GUION}{EXTENSION_CIENTIFICO}? { yylval.val = atof(yytext); return NUM; }
{FLOTANTE}{EXTENSION_CIENTIFICO}? { yylval.val = atof(yytext); return NUM; }

({PATH}|{IDENTIFICADOR})".txt" { yylval.cadena = strdup(yytext); return ARCHIVO; }
{PATH}".so" {yylval.cadena = strdup(yytext); return LIBRERIA; }
{IDENTIFICADOR} {yylval.cadena = strdup(yytext); return VAR; }

\n		{return NEWLINE;}
"+"		{return PLUS;}
"-"		{return MINUS;}
"*"     {return MULT;}
"/"     {return DIV;}
"="     {return IGUAL;}
"=="    {return IGUALIGUAL;}
">="    {return MAYORIGUAL;}
"<="    {return MENORIGUAL;}
">"     {return MAYOR;}
"<"     {return MENOR;}
"!="    {return NOIGUAL;}
"("     {return ABRE;}
")"     {return CIERRA;}
";"     {return PUNTO_COMA;}

.
<<EOF>> {cerrar_archivo(); pop(pila_archivos_pendientes); FILE *fp = leer(pila_archivos_pendientes); if (fp == NULL) {yyrestart(stdin);} else {yyin = fp;} return NEWLINE;} //cuando llegamos al final del archivo, lo cerramos y buscamos el siguiente a abrir. Si no lo hay volvemos a la entrada estandar. 


%%

void inicializar_lexico(){
    pila_archivos_pendientes = crear_pila();
}

void destruir_lexico(){
    eliminar_pila(pila_archivos_pendientes);
    yylex_destroy();
}


//Abrimos el archivo, lo apilados y cambiamos yyin para que se empiece a leer del archivo en vez de la entrada estandar. 
void abrir_archivo(char* archivo){
    FILE * fp = fopen(archivo, "r");
    if (fp == NULL){
        imprimir_error_archivo(NO_ARCHIVO, archivo);
        yyin = stdin;
        return;
    }
    else{
        push(pila_archivos_pendientes, fp);
        yyin = fp;
    }
}

void cerrar_archivo(){
    if (yyin != stdin){
        fclose(yyin);
    }
}
