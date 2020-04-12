//Entrega 2 hash
//Grupo:G21
//Integrantes: Cambiano Agustín - Gualdieri Sofía
//Correctora: Dvorkin Camila


#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>

#include "hash.h"
#include "lista.h"

#define LARGO_INICIAL 59
#define FACTOR_DE_REDIMENSION_AGRANDAR 3
#define FACTOR_DE_REDIMENSION_ACHICAR 1
#define FRACCION_REDIMENSION_ACHICAR 2

typedef void (*hash_destruir_dato_t)(void *);

typedef struct hash_campo {
    char *clave;
    void *valor;
}hash_campo_t;



struct hash {
    size_t cantidad;
    size_t largo;
    lista_t** tabla;
    hash_destruir_dato_t destruir_dato;
};


struct hash_iter{
  const hash_t* hash;
  lista_iter_t* lista_iter;
  size_t posicion;
};

//Fuente: https://codereview.stackexchange.com/questions/85556/simple-string-hashing-algorithm-implementation
size_t hashing(const char* cp)
{
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }
    return hash;
}


//libera la memoria tomada por el campo
//y devuelve el dato almacenado
void* destruir_campo(hash_campo_t* campo){
  void* dato=campo->valor;
  free(campo->clave);
  free(campo);
  return dato;
}


//Destruye la lista y todos los campos de esta
void destruir_lista_de_campos(lista_t* lista, hash_destruir_dato_t destruir_dato){

  void* dato;

  while (!lista_esta_vacia(lista)) {

    dato=destruir_campo(lista_borrar_primero(lista));

    if (destruir_dato!=NULL) {
      destruir_dato(dato);
    }

  }
  lista_destruir(lista, NULL);
}


//Crea un vector de listas del largo pasado por parametro
lista_t** crear_tabla(size_t largo){

  lista_t** tabla=malloc(sizeof(lista_t*)*largo);

  for (size_t i = 0; i < largo; i++) {

    tabla[i]=lista_crear();

    if (!tabla[i]) {
      for (size_t j = 0; j < i; j++) {
        lista_destruir(tabla[j], NULL);
      }
      return NULL;
    }

  }

  return tabla;

}


bool redimensionar_hash(hash_t* hash, size_t tamanio_nuevo){

  lista_t** nueva_tabla=crear_tabla(tamanio_nuevo);

  if (!nueva_tabla) {
    hash_destruir(hash);
    return false;
  }

  size_t largo_hash=hash->largo;
  hash_campo_t* actual;

  for (size_t i = 0; i < largo_hash; i++) {
    while (!lista_esta_vacia(hash->tabla[i])) {
      actual=lista_borrar_primero(hash->tabla[i]);

      if (!lista_insertar_ultimo(nueva_tabla[hashing(actual->clave)%tamanio_nuevo], actual)) {
        for (size_t j = 0; j < tamanio_nuevo; j++) {
            destruir_lista_de_campos(nueva_tabla[j], hash->destruir_dato);
        }
        free(nueva_tabla);
        hash_destruir(hash);
        return false;
      }

    }
  }

  for (size_t i = 0; i < largo_hash; i++) {
    lista_destruir(hash->tabla[i], NULL);
  }
  free(hash->tabla);
  hash->tabla=nueva_tabla;
  hash->largo=tamanio_nuevo;

  return true;

}


//Crea un campo con la clave y dato pasados
hash_campo_t* crear_campo(const char* clave, void* dato){

  hash_campo_t* campo=malloc(sizeof(hash_campo_t));

  if (!campo) {
    return NULL;
  }

  campo->clave=strdup(clave);

  if (!clave) {
    free(campo);
    return NULL;
  }

  campo->valor=dato;

  return campo;

}





//Busca la primera lista no vacia del hash
int hash_buscar_primera_lista(const hash_t* hash, lista_t** lista){

  size_t largo_hash=hash->largo;

  for (int i = 0; i < largo_hash; i++) {
    if (!lista_esta_vacia(hash->tabla[i])) {
      *lista=hash->tabla[i];
      return i;
    }
  }

  return -1;

}





//Busca el elemento con la clave pasada en la lista proporcionada,
//si se indica, el elemento sera borrado de la lista
hash_campo_t* buscar_en_la_lista(lista_t* lista,const char* clave, bool borrar){


    lista_iter_t* iter=lista_iter_crear(lista);

    if (!iter) {
      return NULL;
    }

    hash_campo_t* campo;

    size_t largo_lista=lista_largo(lista);

    for (size_t i = 0; i < largo_lista; i++) {
      campo=lista_iter_ver_actual(iter);
      if (!strcmp(campo->clave,clave)) {
        if (borrar) {
          campo=lista_iter_borrar(iter);
        }
        lista_iter_destruir(iter);
        return campo;
      }
      lista_iter_avanzar(iter);
    }

    lista_iter_destruir(iter);

    return NULL;


}






hash_t *hash_crear(hash_destruir_dato_t destruir_dato){

  hash_t* hash=malloc(sizeof(hash_t));

  if (!hash) {
    return NULL;
  }

  hash->tabla= crear_tabla(LARGO_INICIAL);

  if (!hash->tabla) {
    free(hash);
    return NULL;
  }


  hash->largo=LARGO_INICIAL;
  hash->cantidad=0;
  hash->destruir_dato=destruir_dato;

  return hash;
}





bool hash_guardar(hash_t *hash, const char *clave, void *dato){

  if (hash->cantidad/hash->largo>FACTOR_DE_REDIMENSION_AGRANDAR) {
    if (!redimensionar_hash(hash, hash->cantidad)) {
      return false;
    }
  }


  size_t posicion_elemento=0;

  if (hash->largo!=0) {
    posicion_elemento=hashing((char*)clave)%hash->largo;
  }


  if (!hash_pertenece(hash, clave)) {
    hash_campo_t* campo=crear_campo(clave, dato);

    if (!campo) {
      return NULL;
    }

    if (!lista_insertar_ultimo(hash->tabla[posicion_elemento], campo)) {
      destruir_campo(campo);
      return false;
    }
    hash->cantidad++;
  }else{
    hash_campo_t* ya_guardado=buscar_en_la_lista(hash->tabla[posicion_elemento], clave, false);

    if (hash->destruir_dato!=NULL) {
      hash->destruir_dato(ya_guardado->valor);
    }
    ya_guardado->valor=dato;

  }

  return true;

}






void *hash_borrar(hash_t *hash, const char *clave){

  size_t posicion_elemento=hashing((char*)clave)%hash->largo;
  void* valor_a_retornar;


  hash_campo_t* campo_a_borrar=buscar_en_la_lista(hash->tabla[posicion_elemento], clave, true);

  if (!campo_a_borrar) {
    return NULL;
  }

  valor_a_retornar = destruir_campo(campo_a_borrar);
  hash->cantidad--;

  if ((hash->largo>LARGO_INICIAL)&&(hash->cantidad/hash->largo<FACTOR_DE_REDIMENSION_ACHICAR)) {
    size_t tamanio_nuevo=hash->cantidad/FRACCION_REDIMENSION_ACHICAR;

    if (tamanio_nuevo>=LARGO_INICIAL) {
      redimensionar_hash(hash, tamanio_nuevo);
    }

  }

  return valor_a_retornar;

}






void *hash_obtener(const hash_t *hash, const char *clave){

  size_t posicion_elemento=hashing((char*)clave)%hash->largo;

  if (!hash->tabla[posicion_elemento]) {
    return NULL;
  }

  hash_campo_t* campo=buscar_en_la_lista(hash->tabla[posicion_elemento], clave, false);

  if (!campo) {
    return NULL;
  }

  return campo->valor;

}





bool hash_pertenece(const hash_t *hash, const char *clave){

  size_t posicion_elemento;
  posicion_elemento=hashing((char*)clave)%hash->largo;

  if(hash->tabla[posicion_elemento]==NULL){
    return false;
  }

  return buscar_en_la_lista(hash->tabla[posicion_elemento], clave, false)!=NULL;

}





size_t hash_cantidad(const hash_t *hash){

  return hash->cantidad;

}




void hash_destruir(hash_t *hash){

  size_t largo_hash=hash->largo;

  for (size_t i = 0; i < largo_hash; i++) {
    destruir_lista_de_campos(hash->tabla[i], hash->destruir_dato);
  }

  free(hash->tabla);
  free(hash);

}






hash_iter_t *hash_iter_crear(const hash_t *hash){

  hash_iter_t* iter = malloc(sizeof(hash_iter_t));

  if(!iter){
    return NULL;
  }

  iter->hash = hash;

  int indice_primera_lista=0;

  if (hash->cantidad==0) {
    iter->lista_iter=NULL;
    iter->posicion=0;
    return iter;
  }else{
    lista_t* primera_lista;
    indice_primera_lista=hash_buscar_primera_lista(hash, &primera_lista);
    iter->lista_iter = lista_iter_crear(primera_lista);
  }

  if (!iter->lista_iter) {
    free(iter);
    return NULL;
  }

  iter->posicion=indice_primera_lista;

  return iter;

}



bool hash_iter_avanzar(hash_iter_t *iter){

  if (hash_iter_al_final(iter)) {
    return false;
  }

  if ((!lista_iter_avanzar(iter->lista_iter))||(lista_iter_al_final(iter->lista_iter))) {

    if (hash_iter_al_final(iter)) {
      return false;
    }

    lista_iter_destruir(iter->lista_iter);

    iter->posicion++;
    iter->lista_iter=lista_iter_crear(iter->hash->tabla[iter->posicion]);

    if (!iter->lista_iter) {
      return false;
    }

    while (lista_iter_al_final(iter->lista_iter)) {
      if (hash_iter_al_final(iter)) {
        return false;
      }
      lista_iter_destruir(iter->lista_iter);
      iter->posicion++;
      iter->lista_iter=lista_iter_crear(iter->hash->tabla[iter->posicion]);
      if (!iter->lista_iter) {
        return false;
      }
    }

  }

  return true;

}


const char *hash_iter_ver_actual(const hash_iter_t *iter){


  if (hash_iter_al_final(iter)) {
    return NULL;
  }

  hash_campo_t* actual=lista_iter_ver_actual(iter->lista_iter);

  return actual->clave;

}


bool hash_iter_al_final(const hash_iter_t *iter){

  if (!iter->lista_iter) {
    return true;
  }

  return (iter->posicion==(iter->hash->largo)-1)&&(lista_iter_al_final(iter->lista_iter));

}


void hash_iter_destruir(hash_iter_t* iter){

  lista_iter_destruir(iter->lista_iter);
  free(iter);

}
