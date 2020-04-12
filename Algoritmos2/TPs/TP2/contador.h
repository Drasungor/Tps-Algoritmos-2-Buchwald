#ifndef CONTADOR_H
#define  CONTADOR_H


#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct contador contador_t;


//Setea el maximo del contador y devuelve un puntero a ese contador
contador_t* contador_crear(size_t maximo);


//Aumenta en 1 el contador, devuelve false si tiene el
//mismo valor que el maximo
bool contador_aumentar(contador_t* contador);


//Devueve el valor actual del contador
size_t contador_ver_valor(contador_t* contador);


//Devuelve el maximo valor que podra tener el contador
size_t contardor_ver_maximo(contador_t* contador);


//Cambia el valor maximo del contador, si el contador
//tiene un valor mayor a este nuevo maximo entonces el asigna
//el nuevo maximo
void cambiar_maximo(contador_t* contador, size_t nuevo_maximo);


//Reinicia el valor del contador, lo convierte en 0
void reiniciar_contador(contador_t* contador);

//Destruye el contador
void contador_destruir(contador_t* contador);


#endif
