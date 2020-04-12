
/*


#include"iterador_externo.h"
#include"lista.h"


typedef struct lista_iter{
  lista_t* lista;
  nodo_t* actual;
  nodo_t* anteior;
} lista_iter_t;




//Indica si el elemento actual del iterador es el primer elemento
//de la lista
bool iter_esta_en_primero(lista_iter_t* iter){

  return iter->actual==iter->lista->primero;

}



//Crea un puntero a un iterador e inicializa sus valores.
//actual se inicializa en el primer elemento de la lista
lista_iter_t *lista_iter_crear(lista_t *lista){

  lista_iter_t iter=malloc(sizeof(lista_iter_t));

  if (!iter) {
    return NULL;
  }

  iter->lista=lista;
  iter->actual=lista->primero;
  iter->actual=NULL;

  return iter;

}

//Si actual se encuentra en el ultimo elemento de la
//lista devuelve false, sino el iterador avanza al
//siguiente elemento y devuelve true
bool lista_iter_avanzar(lista_iter_t *iter){

  if (lista_iter_al_final(iter)) {
    return false;
  }

  iter->anterior=iter->actual;
  iter->actual=iter->actual->proximo;

  return true;

}

//Si actual esta fuera de la lista devuelve NULL, sino
//devuelve el valor almacenado en el nodo al que apunta
//actual
void *lista_iter_ver_actual(const lista_iter_t *iter){

  if (!iter->actual) {
    return NULL;
  }

  return iter->actual->dato;

}

//Indica si el iterador esta al final de la lista, es decir,
//si actual esta fuera de ella
bool lista_iter_al_final(const lista_iter_t *iter){

  return !iter->actual;

}

//Destruye el iterador de la lista para que no se pierda memoria
void lista_iter_destruir(lista_iter_t *iter){

  free(iter);

}


//Inserta un elemento entre los elementos actual y anterior de la lista,
//actual apuntará luego al nodo que contiene el elemento agregado y anterior
//no modificará su posición
bool lista_iter_insertar(lista_iter_t *iter, void *dato){

  if (iter_esta_en_primero(iter)) {
    if (lista_insertar_primero(iter->lista, dato)) {
      iter->actual=iter->lista->primero;
      return true;
    }
    return false;
  }

  if (lista_iter_al_final(iter)) {
    if (lista_insertar_ultimo(iter->lista, dato)) {
      iter->actual=iter->lista->ultimo;
      return true;
    }
    return false;
  }

  nodo_t* nodo_a_insertar= malloc(sizeof(nodo_t));

  if (!nodo_a_insertar) {
    return false;
  }


  nodo_a_insertar->dato=dato;
  nodo_a_insertar->proximo=iter->actual;

  if (!iter_esta_en_primero(iter)) {
    iter->anterior->proximo=nodo_a_insertar;
  }

  return true;

}



//Elimina el elemento actual al que apunta el iterador y devuelve
//el elemento que este estaba almacenando, si actual esta fuera
//de la lista devuelve NULL y no borra elementos.
void *lista_iter_borrar(lista_iter_t *iter){

  void* dato_de_retorno;

  if (lista_iter_al_final(iter)) {
    return NULL;
  }

  if (iter_esta_en_primero(iter)) {
    dato_de_retorno=lista_borrar_primero(iter->lista);
    iter->actual=iter->lista->primero;
    return dato_de_retorno;
  }

  dato_de_retorno= lista_iter_ver_actual(iter);

  iter->actual=iter->actual->proximo;
  free(iter->anterior->proximo);
  iter->anterior->proximo=iter->actual;

  if (!iter->actual) {
    iter->lista->ultimo=iter->anterior;
  }

  return dato_de_retorno;

}


*/
