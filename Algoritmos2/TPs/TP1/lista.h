#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include<stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct lista;
typedef struct lista lista_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/


 //Devuelve un puntero a una lista vacía inicializada, si el pedido de memoria
 //falla devuelve NULL
 lista_t *lista_crear(void);


 //Si la lista está vacía devuelve true, sino
 //devuelve false
 bool lista_esta_vacia(const lista_t *lista);


 //Inserta el dato pasado antes del primer elemento de la lista,
 //si falla la asignación de memoria para poder almacenar el dato
 //entonces se devuelve false, sino se devuelve true
 bool lista_insertar_primero(lista_t *lista, void *dato);


 //Inserta el dato pasado luego del último elemento de la lista
 //si la asignación de memoria falla devuelve false, en otro caso
 //devuelve true
 bool lista_insertar_ultimo(lista_t *lista, void *dato);


 //Libera el primer nodo de la lista y devuelve el dato
 //que este almacenaba, si la lista está vacía devuelve NULL
 void *lista_borrar_primero(lista_t *lista);


 //Devuelve el elemento almacenado en el primer nodo
 //de la lista, si la lista está vaciade vuelve NULL
 void *lista_ver_primero(const lista_t *lista);


 //Devuelve el elemento almacenado en el ultimo nodo
 //de la lista, si la lista está vacía devuelve NULL
 void *lista_ver_ultimo(const lista_t* lista);


 //Devuelve el largo de la lista, es decir, la cantidad
 //de elementos que tiene almacenada
 size_t lista_largo(const lista_t *lista);


 //Libera todos los nodos de la lista, si se pasa una función
 //por referencia entonces se utiliza para  destruir todos los
 //datos almacenados
 void lista_destruir(lista_t *lista, void destruir_dato(void *));


 //Iterador interno de la lista, recorre la lista mientras que se cumpla la condición
 //impuesta por viritar()
 void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);




//iterador externo de la lista
 typedef struct lista_iter lista_iter_t;


 //Crea un puntero a un iterador e inicializa sus valores.
 //actual se inicializa en el primer elemento de la lista,
 //si se pasa NULL en vez de una lista se devuelve NULL
 lista_iter_t *lista_iter_crear(lista_t *lista);


 //Si el iterador se encuentra en el ultimo elemento de la
 //lista devuelve false, sino el iterador avanza al
 //siguiente elemento y devuelve true
 bool lista_iter_avanzar(lista_iter_t *iter);


 //Si actual esta fuera de la lista devuelve NULL, sino
 //devuelve el valor almacenado en el nodo al que apunta
 //actual
 void *lista_iter_ver_actual(const lista_iter_t *iter);


 //Indica si el iterador esta al final de la lista, devuelve
 //true si lo está, en caso contrario devuelve false
 bool lista_iter_al_final(const lista_iter_t *iter);


 //Destruye el iterador de la lista para que no se pierda memoria
 void lista_iter_destruir(lista_iter_t *iter);


 //Inserta un elemento en la lista y el iterador apuntará a este una vez insertado
 //en caso de un fallo en la inserción deuvelve false, sino devolverá true
 bool lista_iter_insertar(lista_iter_t *iter, void *dato);

 //Elimina el elemento actual al que apunta el iterador y devuelve
 //el elemento que este estaba almacenando, si el iterador esta fuera
 //de la lista devuelve NULL y no borra elementos.
 void *lista_iter_borrar(lista_iter_t *iter);



/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en cola.h
// (esto es, las pruebas no pueden acceder a los miembros del struct cola).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // COLA_H
