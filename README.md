# Mathematical Interpreter with runtime libraries

## Description:

A tool has been built to interpret expressions and files with sequences of expressions of the form:

x = 3;

y = 2 * pi * x; 

z = x * sin(y + pi/6)

As a result of the execution, the values taken by the different variables that appear in the file are presented. The interpreter incorporates some of the arithmetic operations and functions typical of a scientific calculator (sin, cos, log, exp...), applied to both integers and real numbers in scientific notation. 

In addition, a series of game commands are incorporated, which facilitate the use of the interpreter (help, loading expression files, printing the content of the variables defined in the workspace, deleting the workspace, exiting the program...).

The tool has a lexical analysis stage and a syntactic analysis stage, using the flex and bison tools. A symbol table is used to store the variables that appear in the input file and the values they take throughout the calculation. 

In addition, the possibility of importing functions from user-defined libraries is incorporated through the use of the dlfcn library.

## Execution:

To execute the program:

    bash compila_ejecuta.sh
    
Using Valgrind:

    bash compila_ejecuta.sh valgrind

## Use:
The first thing that will appear is a short welcome message. If we run "help" we can get more information on how to use it.


Permitted operations include:
1. Calculations: 1 + 4
2. Assignments: a = 1 + 4
3. Logic Calculations: c = a == 1 + 4 (The results are 0 or 1, depending on whether False or True, respectively.)
4. Complex operations (just one parameter): a = cos(10)
    4.1 Available: acos, asin, atan, cos, sin, exp, log, log10, sqrt, ceil, fabs, floor, tan
5. Load files: load prueba_todo.txt (IT IS IMPORTANT THAT THE FILE IS .TXT AND THE EXTENSION IS INCLUDED AT THE END OF THE PATH.)
6. Extra functions:
   
    6.1 workspace: prints the tree of assigned variables
   
    6.2 help: prints a help message, which indicates a bit of the same thing I am writing here
   
    6.3 quit: to exit the programme
   
    6.4 clear: to delete all assigned variables from the tree. Clear the workspace.
   
    6.5 print on / print off: is used to activate or deactivate the automatic printing of results.
   
    6.6 operador ';': if we put it at the end of a calculation, an assignment or the use of a complex operation, we will make the printing behaviour be the opposite of the one indicated by the automatic printing (if it is activated or not).

## Uploading own libraries
There is the possibility to load functions dynamically at runtime. The following is used for this purpose:
    "import ./librerias/libprueba.so"     (IT IS VERY IMPORTANT TO INCLUDE THE PATH TO THE LIBRARY (EVEN IF IT IS ONLY ./).)
Two example libraries are included which can be loaded into the program libprueba and libprueba2. An example

    import ./librerias/libprueba.so
    a = suma_resta(10)
    import ./librerias/libprueba2.so
    a = divide_multiplica(10)

## Execution examples:
to run an example we use the file prueba_todo.txt, which contains assignments, use of complex operations, use of extra functions, complex operations, nested file loading and use of libraries:

    load ./archivos_prueba/prueba_todo.txt

Ejecutando archivo: ./archivos_prueba/prueba_todo.txt

1.000000

2.000000

#################################WORKSPACE ACTUAL############################

a --> 2.000000  

#############################################################################

3.000000

Reseteando workspace... 

0.000000

Ejecutando archivo: ./archivos_prueba/prueba.txt
 
3.000000

Ejecutando archivo: ./archivos_prueba/prueba2.txt

5.000000

Ejecutando archivo: ./archivos_prueba/prueba3.txt

6.000000

2.000000

3.000000

5.000000

Libreria ./librerias/libprueba.so cargada correctamente

-8.000000

Libreria ./librerias/libprueba2.so cargada correctamente

0.333333

#################################WORKSPACE ACTUAL############################

j --> 0.333333  d --> 2.000000  c --> 6.000000  b --> 5.000000  a --> 3.000000  x --> -8.000000  w --> 5.000000  q --> 3.000000  l --> 0.000000  

#############################################################################

ADIOS!!!!

