#ifndef AUXILIARES_H
#define  AUXILIARES_H

#include <stdbool.h>

#include "heap.h"
#include "lista.h"
#include "contador.h"
#include "hash.h"

#define PROCESO_REALIZADO_CON_EXITO 0
#define ERROR_CON_MEMORIA_DINAMICA -1
#define CANTIDAD_DE_PARAMETROS_ERRONEA -2
#define TIPO_DE_PARAMETRO_INCORRECTO -3
#define NO_SE_PUDO_ABRIR_EL_ARCHIVO -4
#define SE_ACABO_EL_ARCHIVO -5
#define COMANDO_INVALIDO -6
#define VUELO_INEXISTENTE -7

#define ORDEN_ASCENDENTE "asc"
#define ORDEN_DESCENDENTE "desc"


struct auxiliar_ver_tablero{
  bool indicador;
  hash_t* hash;
  bool ascendente;
  contador_t* contador;
};

struct lista_e_indicador{
  lista_t* lista;
  bool indicador;
};


typedef struct lista_e_indicador lista_e_indicador_t;


typedef struct auxiliar_ver_tablero auxiliar_ver_tablero_t;



//Imprime todas las cadenas dentro de un arreglo de
//cadenas terminado en NULL
void imprimir_arreglo_de_cadenas(const char** cadenas);


//Devuelve un numero mayor a 0 si la prioridad de vuelo1
//es menor que la de vuelo2, si es mayor devuelve un numero
//menor a 0 y si son iguales devuelve 0
int mayor_prioridad_inversa(const void* vuelo1, const void* vuelo2);


//Indica la cantidad de elementos que tiene el
//arreglo de cadenas que forma el comando.
//No toma en cuenta el elemento NULL
size_t cantidad_elementos(const char** arr_cadenas);


//Libera la memoria asignada al vuelo
void destruir_vuelo(void* vuelo);


//Desencola todos los elementos del heap y los imprime de menor
//a mayor prioridad
void imprimir_elementos_heap(heap_t* heap);



//Funcion para iterador interno, guarda el vuelo en una lista
bool guardar_vuelos(void* dato, void* extra);


//Devuelve el entero que representa el string pasado
//No detecta errores
int obtener_entero(char* cadena);


//Indica si los componendes del comando son validos para ejecutar ver_tablero
bool ver_tablero_es_valido(char** componentes_comando, size_t cantidad_de_elementos);


//Indica si los componendes del comando son validos para ejecutar info_vuelo
bool info_vuelo_es_valido(size_t cantidad_de_elementos);


//Indica si los componendes del comando son validos para ejecutar agregar_archivo
bool agregar_archivo_es_valido(size_t cantidad_de_elementos);


//Indica si los componendes del comando son validos para ejecutar prioridad_vuelos
bool priodidad_vuelos_es_valido(char** componentes_comando, size_t cantidad_de_elementos);


//Indica si los componendes del comando son validos para ejecutar borrar
bool borrar_es_valido(char** componentes_comando, size_t cantidad_de_elementos);


//Función para el iterador interno para usar en ver_tablero
//imprime el codigo y la fecha del vuelo en el orden pedido
bool imprimir_en_orden(void* dato, void* extra);


//Destruye una lista que contiene elementos que no deben ser destruidos
void destruir_lista(void* lista);


#endif
