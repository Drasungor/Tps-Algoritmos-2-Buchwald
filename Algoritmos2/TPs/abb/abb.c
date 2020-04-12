//Entrega 1 abb
//Grupo: G21
//Alumnos: Cambiano Agustín - Gualdieri Sofía
//Correctora: Dvorkin Camila


#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"
#include "pila.h"


typedef struct nodo{
  struct nodo* izquierda;
  struct nodo* derecha;
  char* clave;
  void* dato;
}nodo_t;



struct abb{
  nodo_t* raiz;
  size_t cantidad;
  abb_comparar_clave_t comparar_clave;
  abb_destruir_dato_t destruir_dato;
};


struct abb_iter{
  pila_t* pila;
};


//Devuelve un puntero a un nodo inicializado con los valores pasados
nodo_t* crear_nodo(const char* clave, void* dato){

  nodo_t* nodo=malloc(sizeof(nodo_t));

  if (!nodo) {
    return NULL;
  }

  nodo->clave=strdup(clave);

  if (!nodo->clave) {
    free(nodo);
    return NULL;
  }

  nodo->dato=dato;
  nodo->izquierda=NULL;
  nodo->derecha=NULL;

  return nodo;

}


//libera la memoria asignada a la clave y al nodo y devuelve
//el dato almacenado
void* destruir_nodo(nodo_t* nodo){

  void* dato=nodo->dato;
  free(nodo->clave);
  free(nodo);

  return dato;

}


//Devuelve la cantidad de hijos que tiene un nodo
size_t cantidad_de_hijos(nodo_t* nodo){

  size_t cantidad=0;

  if (nodo->derecha!=NULL) {
    cantidad++;
  }

  if (nodo->izquierda!=NULL) {
    cantidad++;
  }

  return cantidad;

}



//Devuelve un puntero al nodo con la clave buscada
nodo_t* _buscar_nodo_y_padre(nodo_t** actual, nodo_t* padre , const char* clave, abb_comparar_clave_t comparar_clave){

  if (!(*actual)) {
    return padre;
  }

  if (!comparar_clave((*actual)->clave, clave)) {
    return padre;
  }

  padre=*actual;

  if (comparar_clave(clave, (*actual)->clave)>0) {
    *actual=(*actual)->derecha;
    return _buscar_nodo_y_padre(actual, padre, clave, comparar_clave);
  }

  *actual=(*actual)->izquierda;
  return _buscar_nodo_y_padre(actual, padre, clave, comparar_clave);

}


void intercambiar_nodos(nodo_t* nodo1, nodo_t* nodo2){

  nodo_t auxiliar=*nodo1;

  nodo1->clave=nodo2->clave;
  nodo1->dato=nodo2->dato;

  nodo2->clave=auxiliar.clave;
  nodo2->dato=auxiliar.dato;

}



nodo_t* buscar_nodo_y_padre(const abb_t* arbol, nodo_t** nodo, const char* clave){

  *nodo=arbol->raiz;

  return _buscar_nodo_y_padre(nodo, NULL, clave, arbol->comparar_clave);

}



void _abb_destruir(nodo_t* nodo, abb_destruir_dato_t destruir_dato){

  if (!nodo) {
    return;
  }

  _abb_destruir(nodo->izquierda, destruir_dato);
  _abb_destruir(nodo->derecha, destruir_dato);

  void* dato=destruir_nodo(nodo);

  if (destruir_dato!=NULL) {
    destruir_dato(dato);
  }

}


//Intercambia el hijo del padre pasado por un remplazante
//No detecta errores, por lo que se deberá pasar un nodo
//que sea realmente un hijo para que funcione bien
void remplazar_hijo(nodo_t* padre, nodo_t* a_remplazar, nodo_t* remplazante){

  if (padre->izquierda==a_remplazar) {
    padre->izquierda=remplazante;
  }else{
    padre->derecha=remplazante;
  }

}


//Devuelve un puntero al hijo de un nodo que solo tiene
//un hijo
nodo_t* obtener_hijo(nodo_t* nodo){

  if (nodo->izquierda!=NULL) {
    return nodo->izquierda;
  }

  return nodo->derecha;

}


//Devuelve el nodo mas chico de un arbol o subarbol
nodo_t* buscar_menor(nodo_t* nodo, nodo_t** padre){

  if (!nodo->izquierda) {
    return nodo;
  }

  *padre=nodo;

  return buscar_menor(nodo->izquierda,padre);

}


bool _abb_in_order(nodo_t* actual, bool visitar(const char *, void *, void *), void *extra){

  if (!actual) {
    return true;
  }

  if (!_abb_in_order(actual->izquierda, visitar, extra)) {
    return false;
  }

  if (!visitar(actual->clave, actual->dato, extra)) {
    return false;
  }

  if (!_abb_in_order(actual->derecha, visitar, extra)) {
    return false;
  }

  return true;

}


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

  abb_t* arbol=malloc(sizeof(abb_t));

  if (!arbol) {
    return NULL;
  }

  arbol->raiz=NULL;
  arbol->comparar_clave=cmp;
  arbol->destruir_dato=destruir_dato;
  arbol->cantidad=0;

  return arbol;

}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

  nodo_t* nodo;
  nodo_t* padre=buscar_nodo_y_padre(arbol, &nodo, clave);

  if (!nodo) {
    nodo=crear_nodo(clave, dato);

    if (!nodo) {
      return false;
    }

    arbol->cantidad++;

    if (!arbol->raiz) {
      arbol->raiz=nodo;
      return true;
    }

    if (arbol->comparar_clave(nodo->clave, padre->clave)>0) {
      padre->derecha=nodo;
    }else{
      padre->izquierda=nodo;
    }

    return true;
  }

  if (arbol->destruir_dato!=NULL) {
    arbol->destruir_dato(nodo->dato);
  }
  nodo->dato=dato;

  return true;

}


void *abb_borrar(abb_t *arbol, const char *clave){

  nodo_t* a_borrar;

  nodo_t* padre=buscar_nodo_y_padre(arbol, &a_borrar, clave);

  if (!a_borrar) {
    return NULL;
  }

  arbol->cantidad--;

  size_t cantidad_hijos = cantidad_de_hijos(a_borrar);
  if (cantidad_hijos==0) {

    if (!padre) {
      arbol->raiz=NULL;
    }else{
      remplazar_hijo(padre, a_borrar, NULL);
    }

  }else if(cantidad_hijos==1){

    if (!padre) {
      arbol->raiz=obtener_hijo(a_borrar);
    }else{
      remplazar_hijo(padre, a_borrar, obtener_hijo(a_borrar));
    }

  }else{

    //en caso de que el remplazante sea hijo del nodo a borrar
    nodo_t* padre_remplazante=a_borrar;

    nodo_t* remplazante=buscar_menor(a_borrar->derecha, &padre_remplazante);

    intercambiar_nodos(a_borrar, remplazante);

    a_borrar=remplazante;
    remplazar_hijo(padre_remplazante, a_borrar, a_borrar->derecha);

  }

  return destruir_nodo(a_borrar);

}


void *abb_obtener(const abb_t *arbol, const char *clave){

  if (!clave) {
    return NULL;
  }

  nodo_t* a_buscar;
  buscar_nodo_y_padre(arbol, &a_buscar, clave);

  if (!a_buscar) {
    return NULL;
  }

  return a_buscar->dato;

}


bool abb_pertenece(const abb_t *arbol, const char *clave){

  nodo_t* a_buscar;
  buscar_nodo_y_padre(arbol, &a_buscar, clave);

  return a_buscar!=NULL;

}


size_t abb_cantidad(abb_t *arbol){

  return arbol->cantidad;

}


void abb_destruir(abb_t *arbol){

  _abb_destruir(arbol->raiz, arbol->destruir_dato);
  free(arbol);

}



void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

  _abb_in_order(arbol->raiz, visitar,extra);

}


bool apilar_izquierdos(pila_t* pila, nodo_t* nodo){

  if (!nodo) {
    return true;
  }

  return pila_apilar(pila, nodo)&&apilar_izquierdos(pila, nodo->izquierda);

}



abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

  abb_iter_t* iter = malloc(sizeof(abb_iter_t));

  if(iter == NULL){
    return NULL;
  }

  iter->pila = pila_crear();

  if(!iter->pila){
    free(iter);
    return NULL;
  }

  if(arbol->raiz!=NULL){
    if (!apilar_izquierdos(iter->pila, arbol->raiz)) {
      abb_iter_in_destruir(iter);
      return NULL;
    }
  }

  return iter;

}


bool abb_iter_in_avanzar(abb_iter_t *iter){

  if (abb_iter_in_al_final(iter)) {
    return false;
  }

  nodo_t* actual = pila_desapilar(iter->pila);
  if(actual->derecha!=NULL){
    if (!apilar_izquierdos(iter->pila, actual->derecha)) {
      return false;
    }
  }

  return true;
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

  if (abb_iter_in_al_final(iter)) {
    return NULL;
  }

  return ((nodo_t*)pila_ver_tope(iter->pila))->clave;

}


bool abb_iter_in_al_final(const abb_iter_t *iter){

  return pila_esta_vacia(iter->pila);

}



void abb_iter_in_destruir(abb_iter_t* iter){

  pila_destruir(iter->pila);
	free(iter);

}
