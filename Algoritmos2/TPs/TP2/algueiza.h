//Entrega 1 TP2
//Correctora: Camila Dvorkin
//Grupo: G21
//Alumnos: Cambiano Agustín - Gualdieri Sofía



#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#include "strutil.h"
#include "hash.h"
#include "abb.h"
#include "vuelo.h"
#include "contador.h"
#include "heap.h"
#include "lista.h"
#include "auxiliares.h"




#define SEPARADOR_ENTRADA_ESTANDAR ' '
#define SEPARADOR_DATOS_VUELOS ','
#define AGREGAR_ARCHIVO "agregar_archivo"
#define VER_TABLERO "ver_tablero"
#define INFO_VUELO "info_vuelo"
#define PRIORIDAD_VUELOS "prioridad_vuelos"
#define BORRAR "borrar"




typedef int (*comando_t)(hash_t*, abb_t*, char**);


//Agrega los vuelos del archivo a las estructuras de información utilizadas
//para almacenarlos
int agregar_archivo(hash_t* hash, abb_t* abb, char** elementos_comando);


//Muestra por la salida estandar los vuelos entre el rango de fechas
//y con el orden especificado en los elementos del comando
int ver_tablero(hash_t* hash, abb_t* abb, char** elementos_comando);


//Muestra por la salida estandar toda la información del vuelo previamente
//proporcionada
int info_vuelo(hash_t* hash, abb_t* abb, char** elementos_comando);


//Muestra por la salida estandar una cantidad especificada de vuelos según
//su prioridad en orden descendente, si la prioridad es la misma para dos vuelos
//muestra primero el de menor codigo de vuelo
int prioridad_vuelos(hash_t* hash, abb_t* abb, char** elementos_comando);


//Elimina de las estructuras de información todos los vuelos cuyas fechas se
//encuentren dentro del rango especificado en los elementos del comando y los
//Muestra por la salida estandar
int borrar(hash_t* hash, abb_t* abb, char** elementos_comando);

//Devuelve un puneto a la función a ejecutar con el comando recibido, en
//caso de fallar devuelve NULL
comando_t obtener_comando_a_ejecutar(char** componentes_comando);

//Trabaja con el comando escrito y, de ser posible, lo ejecuta, indicando
//en ese caso que no hubo problemas e indicando que hubo un error en el otro
int procesar_comando(hash_t* hash, abb_t* abb);
