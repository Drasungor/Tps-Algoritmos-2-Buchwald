#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#define VOLUMEN 10000


int cmp (const void *a, const void *b){

  int na=*(int*)a;
  int nb=*(int*)b;

   if(na < nb) return -1;

   if(na > nb) return 1;

   return 0;

 }

 int cmp_1 (const void *a, const void *b){

   int na=*(int*)a;
   int nb=*(int*)b;

    if(na < nb) return 1;

    if(na > nb) return -1;

    return 0;

  }


void prueba_crear_heap_vacio(){


  heap_t* heap = heap_crear(cmp);

  print_test("Prueba heap crear heap vacio", heap);
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap ver maximo en heap vacio es NULL", !heap_ver_max(heap));
  print_test("Prueba heap desencolar en heap vacio es NULL", !heap_desencolar(heap));
  print_test("Prueba heap esta vacio en heap vacio es true", heap_esta_vacio(heap));

  printf("\n");
  heap_destruir(heap, NULL);
}

void prueba_crear_heap_con_elementos(){

  int arreglo[6] = {7,8,4,9,11,0};
  void* arr[6];

  for (size_t i = 0; i < 6; i++) {
    arr[i]=&arreglo[i];
  }

  heap_t* heap = heap_crear_arr(arr, 6, cmp);

  print_test("Prueba heap crear heap", heap);
  print_test("Prueba heap la cantidad de elementos es 6", heap_cantidad(heap) == 6);
  print_test("Prueba heap ver maximo en heap con elementos", arr[4]==heap_ver_max(heap));
  print_test("Prueba heap desencolar devuelve el mayor elemento", arr[4]==heap_desencolar(heap));
  print_test("Prueba heap no esta vacio en heap con elementos", !heap_esta_vacio(heap));

  printf("\n");
  heap_destruir(heap, NULL);
}

void prueba_heap_encolar(){

  heap_t* heap = heap_crear(cmp);

  int valor1 = 8;
  int valor2 = 4;
  int valor3 = 12;

  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("Prueba heap encolar en heap vacio es true", heap_encolar(heap, &valor1));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor2));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor3));
  print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
  print_test("Prueba heap ver maximo en heap con elementos", &valor3==heap_ver_max(heap));
  print_test("Prueba heap desencolar", heap_desencolar(heap)==&valor3);
  print_test("Prueba heap desencolar", heap_desencolar(heap)==&valor1);
  print_test("Prueba heap esta vacio en heap con elementos", !heap_esta_vacio(heap));

  printf("\n");
  heap_destruir(heap, NULL);

}

void prueba_heap_ver_maximo(){

  heap_t* heap = heap_crear(cmp);

  int valor1 = 8;
  int valor2 = 4;
  int valor3 = 12;
  int valor4 = 0;
  int valor5 = -3;
  int valor6 = 19;
  int valor7 = 24;
  int valor8 = 2;

  print_test("Prueba heap encolar en heap vacio es true", heap_encolar(heap, &valor1));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor2));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor3));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor4));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor5));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor6));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor7));
  print_test("Prueba heap encolar en heap con elementos es true", heap_encolar(heap, &valor8));

  print_test("Prueba heap, ver el maximo es 24", &valor7==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap, ver el maximo despues de desencolar es 19", &valor6==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap, ver el maximo despues de desencolar es 12", &valor3==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap, ver el maximo despues de desencolar es 8", &valor1==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap, ver el maximo despues de desencolar es 4", &valor2==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap, ver el maximo despues de desencolar es 2", &valor8==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap, ver el maximo despues de desencolar es 0", &valor4==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap, ver el maximo despues de desencolar es -3", &valor5==heap_ver_max(heap));
  heap_desencolar(heap);
  print_test("Prueba heap esta vacio en heap sin elementos", heap_esta_vacio(heap));

  print_test("Prueba heap destruir el heap", true);

  printf("\n");
  heap_destruir(heap, NULL);

}

void pruebas_heap_volumen(){

  heap_t* heap = heap_crear(cmp);

  print_test("Prueba heap crear heap vacio", heap);
  print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

  bool encolo=true;
  int valor;

  for(int i=0; i<VOLUMEN && encolo; i++){
    valor=i;
    encolo = encolo && heap_encolar(heap, &valor);
  }
  print_test("Prueba heap la cantidad de elementos es 10000", heap_cantidad(heap) == VOLUMEN);

  void* borrado;
  bool borro =true;
  for(int i=0; i<VOLUMEN && borro; i++){
    valor=i;
    borrado = heap_desencolar(heap);
    borro = borro && borrado==&valor;
  }
  print_test("Prueba heap borrar gran volumen de elementos", borro);

  print_test("Prueba heap destruir el heap", true);

  printf("\n");
  heap_destruir(heap, NULL);



}

void pruebas_heap_heapsort(){

  int arreglo[6] = {7,8,4,9,11,0};
  void* arr[6];

  for (size_t i = 0; i < 6; i++) {
    arr[i]=&arreglo[i];
  }

  heap_t* heap = heap_crear_arr(arr, 6, cmp_1);

  heap_sort(arr, 6, cmp_1);
  print_test("Prueba heap ordenar de mayor a menor", arr[5]==heap_ver_max(heap));
  
  print_test("Prueba heap ordenar de mayor a menor", arr[0]==&arreglo[4]);
  printf("%i\n",*(int*)heap_ver_max(heap));

  printf("\n");
  heap_destruir(heap, NULL);

//////////////////////////////////////////////////////////////////////////////////

  int arreglo_1[6] = {7,8,4,9,11,0};
  void* arr_1[6];

  for (size_t i = 0; i < 6; i++) {
    arr_1[i]=&arreglo_1[i];
  }

  heap_t* heap_1 = heap_crear_arr(arr_1, 6, cmp);

  heap_sort(arr_1, 6, cmp);
  print_test("Prueba heap ordenar de menor a mayor", arr_1[5]==heap_ver_max(heap_1) );
  //printf("%i\n",*(int*)heap_ver_max(heap_1));

  heap_destruir(heap_1, NULL);



}

void pruebas_heap_alumno(){
  prueba_crear_heap_vacio();
  prueba_crear_heap_con_elementos();
  prueba_heap_encolar();
  prueba_heap_ver_maximo();
  pruebas_heap_volumen();
  pruebas_heap_heapsort();
}
