//Entrega 1 heap
//Grupo: G21
//Alumnos: Cambiano Agustín - Gualdieri Sofía
//Correctora: Dvorkin Camila

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "heap.h"

#define TAMANIO_INICIAL 20


//ver si van a ser usadas estas constantes como en la pila
#define FRACCION_PARA_ACHICAR_HEAP 4
#define FRACCION_HEAP_ACHICADA 2
#define PROPORCION_HEAP_AGRANDADA 2

#define NO_TIENE_HIJOS_MAYORES -1

struct heap{
  cmp_func_t comparar_datos;
  size_t cantidad;
  size_t largo;
  void** arbol;
};



void swap(void** x, void** y){

  void* auxiliar=*x;
  *x=*y;
  *y=auxiliar;

}

//Devuelve la posicion del hijo que es mayor que el padre,
//En caso de que la posicion no exista o el conjunto padre-hijos
//no rompa la invariante del heap devuelve -1
int hijo_mayor(void** arbol, size_t indice_nodo, size_t cantidad, cmp_func_t comparar_datos){

  int indice_primer_hijo=(int)indice_nodo*2+1;
  int indice_segundo_hijo=(int)indice_nodo*2+2;

  int indice_max_hijo;

  if (indice_primer_hijo>=cantidad) {
    return NO_TIENE_HIJOS_MAYORES;
  }

  if (indice_segundo_hijo>=cantidad) {
    indice_max_hijo= indice_primer_hijo;
  }else{
    if (comparar_datos(arbol[indice_segundo_hijo], arbol[indice_primer_hijo])<0) {
      indice_max_hijo=indice_primer_hijo;
    }else{
      indice_max_hijo=indice_segundo_hijo;
    }
  }


  if (comparar_datos(arbol[indice_nodo], arbol[indice_max_hijo])<0) {
    return indice_max_hijo;
  }

  return NO_TIENE_HIJOS_MAYORES;

}

void upheap(heap_t* heap, size_t indice_nodo){

  if (indice_nodo==0) {
    return;
  }

  size_t indice_padre=(indice_nodo-1)/2;

  if (heap->comparar_datos(heap->arbol[indice_padre], heap->arbol[indice_nodo])<0) {
    swap(&heap->arbol[indice_padre], &heap->arbol[indice_nodo]);
    upheap(heap, indice_padre);
  }

}

void downheap(void** arbol, size_t indice_nodo, size_t cantidad, cmp_func_t comparar_datos){

  int mayor_hijo=hijo_mayor(arbol, indice_nodo, cantidad, comparar_datos);

  if (mayor_hijo==NO_TIENE_HIJOS_MAYORES) {
    return;
  }

  swap(&arbol[indice_nodo], &arbol[mayor_hijo]);

  downheap(arbol, mayor_hijo, cantidad, comparar_datos);

}


void heapify(void** arreglo, size_t n, cmp_func_t comparar_datos){

  for (size_t i = 0; i <= (n-2)/2; i++) {
    downheap(arreglo, (n-2)/2-i, n, comparar_datos);
  }

}


bool heap_redimensionar(heap_t* heap, size_t tamanio_nuevo){

  void** auxiliar=realloc(heap->arbol, sizeof(void*)*tamanio_nuevo);

  if ((!auxiliar)&&(tamanio_nuevo>0)) {
    return false;
  }

  heap->arbol=auxiliar;
  heap->largo=tamanio_nuevo;

  return true;

}


heap_t* alocar_heap(size_t n){

  heap_t* heap=malloc(sizeof(heap_t));

  if (!heap) {
    return NULL;
  }

  heap->arbol=malloc(sizeof(void*)*n);

  if (!heap->arbol) {
    free(heap);
    return NULL;
  }

  return heap;

}



/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){

  heap_t* heap = alocar_heap(TAMANIO_INICIAL);

  if (!heap) {
    return NULL;
  }

  heap->comparar_datos=cmp;
  heap->cantidad=0;
  heap->largo=TAMANIO_INICIAL;

  return heap;

}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){

  heap_t* heap=alocar_heap(n*PROPORCION_HEAP_AGRANDADA);

  if (!heap) {
    return NULL;
  }

  heap->cantidad=n;
  heap->largo=n*PROPORCION_HEAP_AGRANDADA;


  for (size_t i = 0; i < heap->cantidad; i++) {
    heap->arbol[i]=arreglo[i];
  }

  heap->comparar_datos=cmp;

  heapify(heap->arbol, heap->cantidad, heap->comparar_datos);


  return heap;

}



/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){

  if (destruir_elemento!=NULL) {
    for (size_t i = 0; i < heap->cantidad; i++) {
      if (heap->arbol[i]!= NULL) {
        destruir_elemento(heap->arbol[i]);
      }
    }
  }

  free(heap->arbol);
  free(heap);

}



/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){

  return heap->cantidad;

}




/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){

  return heap->cantidad==0;

}




/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){

  if (heap->cantidad==heap->largo) {
    if (!heap_redimensionar(heap, heap->largo*PROPORCION_HEAP_AGRANDADA)) {
      return false;
    }
  }

  heap->cantidad++;

  heap->arbol[heap->cantidad-1]=elem;
  upheap(heap, heap->cantidad-1);

  return true;

}




/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){

  if (heap_esta_vacio(heap)) {
    return NULL;
  }

  return heap->arbol[0];

}





/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap){

  if (heap_esta_vacio(heap)) {
    return NULL;
  }

  heap->cantidad--;

  if (heap->cantidad<=heap->largo/FRACCION_PARA_ACHICAR_HEAP) {

    size_t tamanio_nuevo=heap->largo/FRACCION_HEAP_ACHICADA;

    if (tamanio_nuevo<=TAMANIO_INICIAL) {
      tamanio_nuevo=TAMANIO_INICIAL;
    }

    if (!heap_redimensionar(heap, tamanio_nuevo)) {
      return NULL;
    }
  }

  swap(&heap->arbol[0],&heap->arbol[heap->cantidad]);

  downheap(heap->arbol, 0, heap->cantidad, heap->comparar_datos);

  return heap->arbol[heap->cantidad];

}





void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

  heapify(elementos, cant, cmp);

  for (size_t i = 0; i < cant; i++) {
    swap(&elementos[0], &elementos[cant-1-i]);
    downheap(elementos, 0, cant-i-1, cmp);
  }

}
