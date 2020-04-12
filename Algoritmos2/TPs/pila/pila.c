
//Entrega 1 pila
//Corrector: Matías Cano
//Alumno: Agustín Cambiano
//Padrón:102291

#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL_PILA 10
#define FRACCION_PARA_ACHICAR_PILA 4
#define FRACCION_PILA_ACHICADA 2
#define PROPORCION_PILA_AGRANDADA 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};



bool pila_redimensionar(pila_t* pila, size_t capacidad_nueva){

  void** datos_auxiliar= realloc(pila->datos, capacidad_nueva*sizeof(void*));

  if ((capacidad_nueva>0)&&(datos_auxiliar==NULL)) {
    return false;
  }

  pila->datos=datos_auxiliar;
  pila->capacidad=capacidad_nueva;
  return true;

}





/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

bool pila_esta_vacia(const pila_t *pila){

  return pila->cantidad==0;

}



void pila_destruir(pila_t *pila){

  free(pila->datos);
  free(pila);

}


pila_t* pila_crear(void){

  pila_t* pila= malloc(sizeof(pila_t));

  if (pila==NULL) {
    return NULL;
  }

  pila->datos=malloc(CAPACIDAD_INICIAL_PILA*(sizeof(void*)));

  if (pila->datos==NULL) {
    free(pila);
    return NULL;
  }

  pila->capacidad=CAPACIDAD_INICIAL_PILA;
  pila->cantidad=0;

  return pila;

}


void* pila_ver_tope(const pila_t *pila){


  if (pila->cantidad==0) {
    return NULL;
  }

  return pila->datos[(pila->cantidad)-1];

}

void* pila_desapilar(pila_t *pila){

  if (pila->cantidad==0) {
    return NULL;
  }

  pila->cantidad--;

  if (pila->cantidad==(pila->capacidad)/FRACCION_PARA_ACHICAR_PILA) {

    size_t capacidad_final= (pila->capacidad)/FRACCION_PILA_ACHICADA;

    if (capacidad_final<CAPACIDAD_INICIAL_PILA) {
      capacidad_final=CAPACIDAD_INICIAL_PILA;
    }


    if ((pila->capacidad)>CAPACIDAD_INICIAL_PILA) {
      pila_redimensionar(pila, capacidad_final);
    }
  }


  return pila->datos[pila->cantidad];

}


bool pila_apilar(pila_t *pila, void* valor){

  if (pila->cantidad==pila->capacidad) {
    if (!pila_redimensionar(pila, (pila->capacidad)*PROPORCION_PILA_AGRANDADA)) {
      return false;
    }
  }

  pila->datos[pila->cantidad]=valor;
  pila->cantidad++;

  return true;

}
