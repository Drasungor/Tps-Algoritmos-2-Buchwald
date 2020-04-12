#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>


typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);


//Devuelve un puntero a un arbol, si falla devuelve NULL
//Recibe la funcion que se usara para comparar las claves almacenadas
//y la que se usara para desturir los datos almacenados
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

//Guarda el dato con la clave pasada en el arbol,
//indica si la operacion de guardado pudo o no
//llevarse a cabo
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

//Borra del arbol el nodo con la clave pasada
//y devuelve el dato que este almacenaba,
//si la clave no se encuentra devuelve NULL
void *abb_borrar(abb_t *arbol, const char *clave);


//Devuelve el dato almacenado en el nodo con la clave pasada,
//si no se encuentra devuelve NULL
void *abb_obtener(const abb_t *arbol, const char *clave);

//Indica si la clave se encuentra o no en el arbol
bool abb_pertenece(const abb_t *arbol, const char *clave);


//Indica la cantidad de elementos almacenados en el arbol
size_t abb_cantidad(abb_t *arbol);


//Destruye el arbol y todos los datos que almacena
//con la funcion de destruccion pasada al crearlo
void abb_destruir(abb_t *arbol);


//Iterador interno del arbol, hace el recorrido in-order
//mientras se cumpla la condicion impuesta por visitar
void abb_in_order(abb_t *arbol, bool visitar(void *, void *), void *extra, char* desde, char* hasta, char* orden);




//Devuelve un puntero al iterador del arbol, si falla
//su creacion devuelve NULL
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);


//Pasa al siguiente elemento del arbol, en caso de estar al
//final devuelve false
bool abb_iter_in_avanzar(abb_iter_t *iter);


//Devuelve la clave del elemento al que apunta actualmente
//el iterador
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);


//Indica si el iterador se encuentra en el ultimo elemento
bool abb_iter_in_al_final(const abb_iter_t *iter);


//Destruye el iterador
void abb_iter_in_destruir(abb_iter_t* iter);



#endif
