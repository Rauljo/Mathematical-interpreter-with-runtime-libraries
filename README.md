INTERPRETE CON BISON Y FLEX

EJECUCION:
Para ejecutar el archivo:
    "bash compila_ejecuta.sh"
Para utilizar valgrind:
    "bash compila_ejecuta.sh valgrind"

USO
Lo primero que aparecerá es un pequeño mensaje de bienvenida. Si ejecutamos "help" podremos obtener más información sobre el uso. 

Las operaciones que se pueden hacer incluyen:
1. Calculos: 1 + 4
2. Asignaciones: a = 1 + 4
3. Calculos lógicos: c = a == 1 + 4 (Los resultados son 0 o 1, según sea False o True, respectivamente)
4. Operaciones complejas (solo de un parametro): a = cos(10)
    4.1 Disponibles: acos, asin, atan, cos, sin, exp, log, log10, sqrt, ceil, fabs, floor, tan
5. Cargar archivos: load prueba_todo.txt (ES IMPORTANTE QUE EL ARCHIVO SEA .TXT Y SE INCLUYA LA EXTENSIÓN AL FINAL DE LA RUTA)
6. Funciones extra:
    6.1 workspace: imprime el arbol de variables asignadas
    6.2 help: imprime un mensaje de ayuda, que indica un poco lo mismo que estoy escribiendo aqui
    6.3 quit: para salir del programa
    6.4 clear: para borrar todas las variables asignadas del arbol. Limpiar el espacio de trabajo. 
    6.5 print on / print off: sirve para activar o desactivar la impresión automática de resultados
    6.6 operador ';': si lo ponemos al final de un cálculo, una asignación o el uso de una operacion compleja, haremos que el comportamiento de impresión sea el contrario al indicado por la impresión automática (si está activada o no)

VERSION PREMIUM:
Existe la posibilidad de cargar funciones en tiempo de ejecución dinámicamente. Para ello se utiliza lo siguiente:
    "import ./librerias/libprueba.so"     (ES MUY IMPORTANTE INCLUIR LA RUTA A LA LIBRERIA (AUNQUE SEA SOLO ./))
Se incluyen dos librerias de ejemplo que se pueden cargar en el programa libprueba y libprueba2. Un ejemplo

>> import ./librerias/libprueba.so
>> a = suma_resta(10)
>> import ./librerias/libprueba2.so
>> a = divide_multiplica(10)

EJEMPLOS DE EJECUCIÓN:
para ejecutar un ejemplo utilizamos el archivo prueba_todo.txt, que contiene asignaciones, uso de operaciones complejas, uso de funciones extra, operaciones complejas, carga de ficheros anidada y uso de librerias:

>> load ./archivos_prueba/prueba_todo.txt

Ejecutando archivo: ./archivos_prueba/prueba_todo.txt
>> 
>> 1.000000
>> 2.000000
>> #################################WORKSPACE ACTUAL############################
a --> 2.000000  
#############################################################################
>> 3.000000
>> Reseteando workspace... 
>> 0.000000
>> Ejecutando archivo: ./archivos_prueba/prueba.txt
>> 
>> 3.000000
>> Ejecutando archivo: ./archivos_prueba/prueba2.txt
>> 
>> 5.000000
>> Ejecutando archivo: ./archivos_prueba/prueba3.txt
>> 
>> 6.000000
>> 2.000000
>> 
>> 3.000000
>> 
>> 5.000000
>> Libreria ./librerias/libprueba.so cargada correctamente
>> 
>> -8.000000
>> Libreria ./librerias/libprueba2.so cargada correctamente
>> 
>> 0.333333
>> #################################WORKSPACE ACTUAL############################
j --> 0.333333  d --> 2.000000  c --> 6.000000  b --> 5.000000  a --> 3.000000  x --> -8.000000  w --> 5.000000  q --> 3.000000  l --> 0.000000  
#############################################################################
>> 	ADIOS!!!!

