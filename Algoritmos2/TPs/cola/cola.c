//Entrega2 cola
//Corrector: Matías Cano
//Alumno: Agustín Cambiano
//Padrón: 102291


#include <stdlib.h>
#include "cola.h"

typedef struct nodo{
  void* dato;
  struct nodo* proximo;
}nodo_t;


typedef struct cola{
  nodo_t* primero;
  nodo_t* ultimo;

}cola_t;




nodo_t* crear_nodo(void* dato, nodo_t* proximo){


  nodo_t* nodo=malloc(sizeof(nodo_t));

  if (!nodo) {
    return NULL;
  }

  nodo->proximo=proximo;
  nodo->dato=dato;

  return nodo;

}



cola_t* cola_crear(void){

  cola_t* cola = malloc(sizeof(cola_t));

  if (!cola) {
    return NULL;
  }

  cola->primero= NULL;
  cola->ultimo= NULL;

  return cola;

}


void cola_destruir(cola_t *cola, void destruir_dato(void*)){

  void* dato;

  while (!cola_esta_vacia(cola)) {
    dato= cola_desencolar(cola);

    if (destruir_dato!=NULL) {
      destruir_dato(dato);
    }
  }

  free(cola);

}

bool cola_esta_vacia(const cola_t *cola){

  return !cola->primero;

}

bool cola_encolar(cola_t *cola, void* valor){

  nodo_t* nuevo_elemento=crear_nodo(valor, NULL);

  if (!nuevo_elemento) {
    return false;
  }

  if (!cola_esta_vacia(cola)) {
    cola->ultimo->proximo=nuevo_elemento;
  }else{
    cola->primero=nuevo_elemento;
  }

  cola->ultimo=nuevo_elemento;

  return true;
}



void* cola_ver_primero(const cola_t *cola){

  if (cola_esta_vacia(cola)) {
      return NULL;
  }

  return cola->primero->dato;

}

void* cola_desencolar(cola_t *cola){

  if (cola_esta_vacia(cola)) {
    return NULL;
  }

  nodo_t* nodo_a_desencolar=cola->primero;
  void* valor_de_retorno=nodo_a_desencolar->dato;

  cola->primero=cola->primero->proximo;

  free(nodo_a_desencolar);

  if (cola_esta_vacia(cola)) {
    cola->ultimo=NULL;
  }

  return valor_de_retorno;

}
