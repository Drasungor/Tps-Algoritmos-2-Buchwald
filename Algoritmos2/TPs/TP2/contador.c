#include <stdbool.h>

#include "contador.h"

struct contador{
  size_t valor_actual;
  size_t valor_maximo;
};


contador_t* contador_crear(size_t maximo){

  contador_t* contador=malloc(sizeof(contador_t));

  if (!contador) {
    return NULL;
  }

  contador->valor_actual=0;
  contador->valor_maximo=maximo;

  return contador;

}



bool contador_aumentar(contador_t* contador){

  if (contador->valor_actual==contador->valor_maximo) {
    return false;
  }

  contador->valor_actual++;

  return true;

}



size_t contador_ver_valor(contador_t* contador){

  return contador->valor_actual;

}



size_t contardor_ver_maximo(contador_t* contador){

  return contador->valor_maximo;

}



void cambiar_maximo(contador_t* contador, size_t nuevo_maximo){

  contador->valor_maximo=nuevo_maximo;

  if (contador->valor_actual>contador->valor_maximo) {
    contador->valor_actual=contador->valor_maximo;
  }

}



void reiniciar_contador(contador_t* contador){

  contador->valor_actual=0;

}




void contador_destruir(contador_t* contador){

  free(contador);

}
