//Entrega 2 lista
//Corrector: Matías Cano
//Alumno: Agustín Cambiano
//Padrón: 102291


#include <stdlib.h>
#include "lista.h"

typedef struct nodo{
  void* dato;
  struct nodo* proximo;
}nodo_t;


struct lista{
  nodo_t* primero;
  nodo_t* ultimo;
  size_t largo;
};



struct lista_iter{
  lista_t* lista;
  nodo_t* actual;
  nodo_t* anterior;
};


static nodo_t* crear_nodo(void* dato,  nodo_t* proximo){

  nodo_t* nodo=malloc(sizeof(nodo_t));

  if (!nodo) {
    return NULL;
  }

  nodo->dato=dato;
  nodo->proximo=proximo;

  return nodo;

}




//Devuelve un puntero a una lista vacía inicializada, si el pedido de memoria
//falla devuelve NULL
lista_t *lista_crear(void){

  lista_t* lista=malloc(sizeof(lista_t));

  if (!lista) {
    return NULL;
  }

  lista->primero=NULL;
  lista->ultimo=NULL;
  lista->largo=0;

  return lista;

}


//Si la lista está vacía devuelve true, sino
//devuelve false
bool lista_esta_vacia(const lista_t *lista){

  return lista->largo==0;

}



//Inserta el dato pasado antes del primer elemento de la lista,
//si falla la asignación de memoria para poder almacenar el dato
//entonces se devuelve false, sino se devuelve true
bool lista_insertar_primero(lista_t *lista, void *dato){

  nodo_t* nodo_a_agregar=crear_nodo(dato, lista->primero);

  if (!nodo_a_agregar) {
    return false;
  }

  lista->primero=nodo_a_agregar;

  if (lista_esta_vacia(lista)) {
    lista->ultimo=lista->primero;
  }

  lista->largo++;

  return true;

}


//Inserta el dato pasado luego del último elemento de la lista
//si la asignación de memoria falla devuelve false, en otro caso
//devuelve true
bool lista_insertar_ultimo(lista_t *lista, void *dato){

  nodo_t* nodo_a_agregar=crear_nodo(dato, NULL);

  if (!nodo_a_agregar) {
    return false;
  }

  if (!lista_esta_vacia(lista)) {
    lista->ultimo->proximo=nodo_a_agregar;
  }else{
    lista->primero=nodo_a_agregar;
  }
  lista->ultimo=nodo_a_agregar;
  lista->largo++;

  return true;

}

//libera el primer nodo de la lista y devuelve el dato
//que este almacenaba, si la lista está vacía devuelve NULL
void *lista_borrar_primero(lista_t *lista){

  if (lista_esta_vacia(lista)) {
    return NULL;
  }

  nodo_t* auxiliar=lista->primero;
  void* dato_a_retornar=auxiliar->dato;

  lista->primero=lista->primero->proximo;

  free(auxiliar);
  lista->largo--;

  if (lista_esta_vacia(lista)) {
    lista->ultimo=NULL;
  }

  return dato_a_retornar;

}


//Devuelve el elemento almacenado en el primer nodo
//de la lista, si la lista está vaciade vuelve NULL
void *lista_ver_primero(const lista_t *lista){

  if (lista_esta_vacia(lista)) {
    return NULL;
  }

  return lista->primero->dato;

}


//Devuelve el elemento almacenado en el ultimo nodo
//de la lista, si la lista está vacía devuelve NULL
void *lista_ver_ultimo(const lista_t* lista){

  if (lista_esta_vacia(lista)) {
    return NULL;
  }

  return lista->ultimo->dato;

}



//Devuelve el largo de la lista, es decir, la cantidad
//de elementos que tiene almacenada
size_t lista_largo(const lista_t *lista){

  return lista->largo;

}


//libera todos los nodos de la lista, si se pasa una función
//por referencia entonces se utiliza para  destruir todos los
//datos almacenados
void lista_destruir(lista_t *lista, void destruir_dato(void *)){

  void* dato;

  while (!lista_esta_vacia(lista)) {
    dato=lista_borrar_primero(lista);
    if (destruir_dato!=NULL) {
      destruir_dato(dato);
    }
  }

  free(lista);

}

//Iterador interno de la lista, recorre la lista mientras que se cumpla la condición
//impuesta por viritar()
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){

  nodo_t* actual= lista->primero;

  while ((actual!=NULL)&&(visitar(actual->dato, extra))) {
    actual=actual->proximo;
  }

}



//ITERADOR EXTERNO






//Indica si el elemento actual del iterador es el primer elemento
//de la lista
bool lista_iter_esta_en_primero(lista_iter_t* iter){

  return iter->actual==iter->lista->primero;

}



//Crea un puntero a un iterador e inicializa sus valores.
//actual se inicializa en el primer elemento de la lista,
//si se pasa NULL en vez de una lista se devuelve NULL
lista_iter_t *lista_iter_crear(lista_t *lista){

  if (!lista) {
    return NULL;
  }

  lista_iter_t* iter=malloc(sizeof(lista_iter_t));

  if (!iter) {
    return NULL;
  }

  iter->lista=lista;
  iter->actual=lista->primero;
  iter->anterior=NULL;

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

  if (lista_iter_al_final(iter)) {
    return NULL;
  }

  return iter->actual->dato;

}

//Indica si el iterador esta al final de la lista, es decir,
//si actual esta fuera de ella
bool lista_iter_al_final(const lista_iter_t *iter){

  //return iter->actual==iter->lista->ultimo;

  return iter->actual==NULL;

}

//Destruye el iterador de la lista para que no se pierda memoria
void lista_iter_destruir(lista_iter_t *iter){

  free(iter);

}


//Inserta un elemento en la lista y el iterador apuntará a este una vez insertado,
//en caso de un fallo en la inserción deuvelve false, sino devolverá true
bool lista_iter_insertar(lista_iter_t *iter, void *dato){

  nodo_t* nodo_a_insertar= crear_nodo(dato, iter->actual);

  if (!nodo_a_insertar) {
    return false;
  }

  if (lista_iter_esta_en_primero(iter)) {
    iter->lista->primero=nodo_a_insertar;
  }else if(lista_iter_al_final(iter)){
    iter->anterior->proximo=nodo_a_insertar;
    iter->lista->ultimo=nodo_a_insertar;
  }else{
    iter->anterior->proximo=nodo_a_insertar;
  }

  iter->actual=nodo_a_insertar;

  if (lista_esta_vacia(iter->lista)) {
    iter->lista->primero=nodo_a_insertar;
    iter->lista->ultimo=nodo_a_insertar;
  }

  iter->lista->largo++;

  return true;

}



//Elimina el elemento actual al que apunta el iterador y devuelve
//el elemento que este estaba almacenando, si el iterador esta fuera
//de la lista devuelve NULL y no borra elementos.
void *lista_iter_borrar(lista_iter_t *iter){

  void* dato_de_retorno;

  if (lista_iter_al_final(iter)) {
    return NULL;
  }

  dato_de_retorno= lista_iter_ver_actual(iter);

  nodo_t* siguiente=iter->actual->proximo;

  if (!lista_iter_esta_en_primero(iter)) {
    free(iter->actual);
    iter->anterior->proximo=siguiente;
  }else{
    free(iter->lista->primero);
    iter->lista->primero=siguiente;
  }

  iter->actual=siguiente;

  if (!iter->actual) {
    iter->lista->ultimo=iter->anterior;
  }

  iter->lista->largo--;

  return dato_de_retorno;

}
