#include <stdlib.h>

#include "vuelo.h"
#include "strutil.h"


struct vuelo{
  char** informacion;
};


vuelo_t* vuelo_crear(char* datos, char sep){

  vuelo_t* vuelo=malloc(sizeof(vuelo_t));

  if (!vuelo) {
    return NULL;
  }

  vuelo->informacion=split(datos, sep);

  if (!vuelo->informacion) {
    free(vuelo);
    return NULL;
  }

  return vuelo;

}


const char* vuelo_codigo(vuelo_t* vuelo){

  return vuelo->informacion[0];

}

size_t vuelo_prioridad(vuelo_t* vuelo){

  return atoi(vuelo->informacion[5]);

}

const char* vuelo_fecha(vuelo_t* vuelo){

  return vuelo->informacion[6];

}


const char** vuelo_obtener_informacion(vuelo_t* vuelo){

  return (const char**)vuelo->informacion;

}


void vuelo_destruir(vuelo_t* vuelo){

  free_strv(vuelo->informacion);
  free(vuelo);

}
