#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>

//función para iterador interno que imprime todos los elementos
//de la lista
bool imprimir_elementos(void* dato, void* extra){

  printf("%d\n", *(int*)dato);

  return true;

}



bool imprimir_hasta_primer_elemento_negativo(void* dato, void* extra){

  int valor_dato= *(int*)dato;

  if (valor_dato<0) {
    return false;
  }

  printf("%d\n", valor_dato);

  return true;

}


bool sumar_elementos(void* dato, void* extra){

  *(int*)extra+= *(int*)dato;

  return true;
}


bool crear_vectores_dinamicos(int* vectores_dinamicos[5]){

  vectores_dinamicos[0]=malloc(5*sizeof(int));

  if (!vectores_dinamicos[0]) {
    printf("Error al crear un vector dinamico\n");
    return false;
  }

  vectores_dinamicos[1]=malloc(5*sizeof(int));

  if (!vectores_dinamicos[1]) {
    free(vectores_dinamicos[0]);
    printf("Error al crear un vector dinamico\n");
    return false;
  }

  vectores_dinamicos[2]=malloc(5*sizeof(int));

  if (!vectores_dinamicos[2]) {
    free(vectores_dinamicos[0]);
    free(vectores_dinamicos[1]);
    printf("Error al crear un vector dinamico\n");
    return false;
  }

  vectores_dinamicos[3]=malloc(5*sizeof(int));

  if (!vectores_dinamicos[3]) {
    free(vectores_dinamicos[0]);
    free(vectores_dinamicos[1]);
    free(vectores_dinamicos[2]);
    printf("Error al crear un vector dinamico\n");
    return false;
  }

  vectores_dinamicos[4]=malloc(5*sizeof(int));

  if (!vectores_dinamicos[4]) {
    free(vectores_dinamicos[0]);
    free(vectores_dinamicos[1]);
    free(vectores_dinamicos[2]);
    free(vectores_dinamicos[3]);
    printf("Error al crear un vector dinamico\n");
    return false;
  }

  return true;

}


void inicializar_vectores_dinamicos(int* vectores_dinamicos[5]) {

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {

      (vectores_dinamicos[i])[j]=j;
    }
  }

}


void pruebas_lista_vacia_version_alumno(){
  printf("INICIO DE PRUEBAS CON LISTA DE TAMANIO 0\n");

  lista_t* lista1= lista_crear();

  print_test("crear lista vacia", lista_esta_vacia(lista1));
  print_test("ver primer elemento de la lista vacia", !lista_ver_primero(lista1));
  print_test("eliminar primer elemento de la lista vacia", !lista_borrar_primero(lista1));

  lista_destruir(lista1, NULL);
}


void pruebas_lista_con_1_elemento(){
  printf("INICIO DE PRUEBAS CON LISTA DE TAMANIO 1\n");

  lista_t* lista2= lista_crear();
  int elemento_a_agregar=5;

  print_test("enlistar un elemento", lista_insertar_primero(lista2, &elemento_a_agregar));

  //se asume que el elemento anterior fue alistado correctamente
  print_test("ver si la lista esta vacia teniendo 1 elemento", !lista_esta_vacia(lista2));
  print_test("ver que el largo es 1 teniendo 1 elemento", lista_largo(lista2)==1);
  print_test("ver primer elemento de la lista no vacia", lista_ver_primero(lista2)==&elemento_a_agregar);
  print_test("desenlistar un elemento", lista_borrar_primero(lista2)==&elemento_a_agregar);
  print_test("se desapilo el elemento y la lista está vacía", lista_esta_vacia(lista2));
  print_test("se ve que el largo de la lista sea 0 estando vacia", lista_largo(lista2)==0);
  print_test("se enlista el elemento NULL", lista_insertar_primero(lista2, NULL));
  print_test("el primer elemento es NULL y la lista no esta vacia", (!lista_esta_vacia(lista2))&&(!lista_ver_primero(lista2)));
  lista_destruir(lista2, NULL);

}

void prueba_lista_con_algunos_elementos(){
  printf("INICIO DE PRUEBAS CON LISTA DE ALGUNOS ELEMENTOS\n");

  lista_t* lista3= lista_crear();

  int elementos[10]={7,64,-23,-769,1463,37,469,1,-1,10};
  bool se_enlisto_bien=true;
  bool se_desenlisto_bien=true;

  for (size_t i = 0; i < 10; i++) {
    if (!lista_insertar_ultimo(lista3, &elementos[i])) {
      se_enlisto_bien=false;
      break;
    }
  }

  print_test("enlistar elementos", se_enlisto_bien);
  print_test("la lista no esta vacia", !lista_esta_vacia(lista3));
  print_test("obtener primer valor de la lista", lista_ver_primero(lista3)==&elementos[0]);
  print_test("se tiene la cantidad correcta de elementos", lista_largo(lista3)==10);
  print_test("el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista3)==&elementos[9]);

  printf("se imprimen todos los elementos de  a lista con el iterador interno...\n");
  lista_iterar(lista3, imprimir_elementos, NULL);

  printf("se imprime hasta el primer elemento de la lista...\n");
  lista_iterar(lista3, imprimir_hasta_primer_elemento_negativo, NULL);

  int suma=0;
  lista_iterar(lista3, sumar_elementos, &suma);
  print_test("la suma total de los elementos de la lista es la correcta (usando iterador interno)", suma==1258);

  for (int i = 0; i <10; i++) {
    if (lista_borrar_primero(lista3)!=&elementos[i]) {
      se_desenlisto_bien=false;
      break;
    }

    if (i==5) {
      print_test("la lista no está vacía habiendo vaciado la mitad", !lista_esta_vacia(lista3));
    }

  }
  print_test("desenlistar elementos", se_desenlisto_bien);

  print_test("la lista esta vacía después de desenlistar", lista_esta_vacia(lista3));

  print_test("se recibe null cuando se intenta desenlistar la lista vacia", !lista_borrar_primero(lista3));
  print_test("se recibe null cuando se intenta leer el tope de la lista vacia", !lista_ver_primero(lista3));



  //se enlistan nuevamente los elementos para probar que
  //no se pierda información al usar lista_destruir con una
  //lista que no esta vacia
  se_enlisto_bien=true;
  for (size_t i = 0; i < 10; i++) {
    if (!lista_insertar_ultimo(lista3, &elementos[i])) {
      se_enlisto_bien=false;
      break;
    }
  }

  print_test("se enlista nuevamente", se_enlisto_bien);

  lista_destruir(lista3, NULL);

}


void prueba_de_volumen_lista(){
  printf("INICIO PRUEBAS DE VOLUMEN\n");

  int* vector_dinamico= malloc(100000*sizeof(int*));

  if (!vector_dinamico) {
    return;
  }

  lista_t* lista4= lista_crear();

  bool se_apilo_bien=true;
  bool se_desapilo_bien=true;

  for (int i = 0; i < 100000; i++) {
      vector_dinamico[i]=i;

      if ((!lista_insertar_ultimo(lista4, &vector_dinamico[i]))||(lista_ver_ultimo(lista4)!=&vector_dinamico[i])) {
        se_apilo_bien=false;
        break;
      }

      if (i%25000==0) {
        print_test("la lista no esta vacía teniendo algunos elementos", !lista_esta_vacia(lista4));
      }
  }

  print_test("se enlistaron todos los elementos", se_apilo_bien);
  print_test("se tiene la cantidad adecuada de elementos", lista_largo(lista4)==100000);

  print_test("el primer valor de la lista es el primer elemento alistado", lista_ver_primero(lista4)==&vector_dinamico[0]);


  for (int i = 0; i < 100000; i++) {

    if ((i%25000==0)&&(i!=0)) {
      print_test("la lista no esta vacía teniendo algunos elementos", !lista_esta_vacia(lista4));

      print_test("el primer valor de la lista es el correcto", lista_ver_primero(lista4)==&vector_dinamico[i]);
    }

    if (lista_borrar_primero(lista4)!=&vector_dinamico[i]) {
      se_desapilo_bien=false;
      break;
    }
  }

  print_test("se desenlistaron correctamente los elementos que habían sido enlistados", se_desapilo_bien);
  print_test("la lista esta vacía", lista_esta_vacia(lista4));

  lista_destruir(lista4, NULL);
  free(vector_dinamico);

}


void pruebas_lista_almacenando_vector_dinamico(){
  printf("INICIO PRUEBAS ALMACENANDO VECTORES DINAMICOS\n");

  int *vector_dinamico1=NULL, *vector_dinamico2=NULL, *vector_dinamico3=NULL, *vector_dinamico4=NULL, *vector_dinamico5=NULL;

  int* vectores_dinamicos[5]={vector_dinamico1, vector_dinamico2, vector_dinamico3, vector_dinamico4, vector_dinamico5};

  if (!crear_vectores_dinamicos(vectores_dinamicos)) {
    return;
  }

  inicializar_vectores_dinamicos(vectores_dinamicos);

  lista_t* lista4= lista_crear();

  bool se_apilo_bien=true;

  for (size_t i = 0; i < 5; i++) {
    se_apilo_bien=lista_insertar_primero(lista4, vectores_dinamicos[i]);
  }

  print_test("se introdujeron los vectores dinamicos en la lista", se_apilo_bien);
  print_test("el primer elemento de la lista es el ultimo elemento introducido", lista_ver_primero(lista4)==vectores_dinamicos[4]);

  lista_destruir(lista4, free);

}





void prueba_iterador_externo_lista_vacia(){

  printf("PRUEBAS USANDO ITERADOR EXTERNO EN LISTA VACÍA:\n");

  lista_t* lista5= lista_crear();

  lista_iter_t* iter= lista_iter_crear(lista5);

  print_test("el actual en la lista vacía devuelve NULL", !lista_iter_ver_actual(iter));
  print_test("no se puede avanzar en la lista vacía", !lista_iter_avanzar(iter));
  print_test("no se puede eliminar un elemento en la lista vacía", !lista_iter_borrar(iter));
  print_test("el iterador esta al final de la lista", lista_iter_al_final(iter));

  lista_destruir(lista5, NULL);
  lista_iter_destruir(iter);

}


void prueba_iterador_externo_lista_con_1_elemento(){

  printf("INICIO PRUEBAS ITERADOR EXTERNO EN LISTA DE 1 ELEMENTO\n");

  int elemento=3;

  lista_t* lista6=lista_crear();
  lista_iter_t* iter= lista_iter_crear(lista6);

  print_test("se inserta un elemento en la lista vacía usando el iterador", lista_iter_insertar(iter, &elemento));
  print_test("no se esta al final de la lista con el iterador estando en el ultimo elemento", !lista_iter_al_final(iter));
  print_test("se puede avanzar cuando se apunta al ultimo elemento de la lista", lista_iter_avanzar(iter));
  print_test("el iterador esta al final de la lista (actual apunta a NULL)", lista_iter_al_final(iter));
  print_test("no se puede avanzar porque esta el iterador al final de la lista", !lista_iter_avanzar(iter));
  print_test("no se puede borrar un elemento porque el iterador está al final de la lista", !lista_iter_borrar(iter));
  print_test("la lista tiene 1 elemento", lista_largo(lista6)==1);

  lista_iter_destruir(iter);

  iter=lista_iter_crear(lista6);

  print_test("se puede borrar el elemento de la lista con el iterador", lista_iter_borrar(iter)==&elemento);
  print_test("la lista esta vacia", lista_esta_vacia(lista6));


  lista_iter_destruir(iter);
  lista_destruir(lista6, NULL);
}


void prueba_iterador_externo_lista_con_algunos_elementos(){
  printf("INICIO DE PRUEBAS DE ITERADOR EXTERNO CON LISTA DE ALGUNOS ELEMENTOS\n");

  lista_t* lista7= lista_crear();

  lista_iter_t* iter= lista_iter_crear(lista7);

  int elementos[10]={7,64,-23,-769,1463,37,469,1,-1,10};
  bool se_enlisto_bien=true;

  for (size_t i = 0; i < 10; i++) {
    if (!lista_iter_insertar(iter,&elementos[i])) {
      se_enlisto_bien=false;
      break;
    }
  }

  print_test("se enlistan elementos con el iterador externo estando en el primer elemento", se_enlisto_bien);
  print_test("la lista no esta vacia", !lista_esta_vacia(lista7));
  print_test("la lista tiene la cantidad adecuada de elementos", lista_largo(lista7)==10);
  print_test("el primer elemento de la lista es el adecuado", lista_ver_primero(lista7)==&elementos[9]);


  for (size_t i = 0; i < 5; i++) {
    lista_iter_avanzar(iter);
  }

  print_test("se elimina un elemento y devuelve el valor correcto", lista_iter_borrar(iter)==&elementos[4]);
  print_test("la lista no está vacía", !lista_esta_vacia(lista7));
  print_test("la cantidad de elementos en la lista es la correcta", lista_largo(lista7)==9);


  //se lleva el iterador al principio de la lista
  lista_iter_destruir(iter);
  iter=lista_iter_crear(lista7);

  bool lista_esta_bien=true;

  for (size_t i = 0; i < 9; i++) {
    if (!lista_iter_avanzar(iter)) {
      lista_esta_bien=false;
      break;
    }
  }

  print_test("la lista sigue enlazada", lista_esta_bien);

  int elemento= 9;

  print_test("se agrega un elemento en medio de la lista con el iterador", lista_iter_insertar(iter, &elemento));

  print_test("el elemento enlistado es el correcto y el iterador apunta a el", lista_iter_ver_actual(iter)==&elemento);


  //se lleva el iterador al principio de la lista
  lista_iter_destruir(iter);
  iter=lista_iter_crear(lista7);

  lista_esta_bien=true;
  for (size_t i = 0; i < 10; i++) {
    if (!lista_iter_avanzar(iter)) {
      lista_esta_bien=false;
      break;
    }
  }

  print_test("la lista sigue enlazada", lista_esta_bien);
  print_test("la cantidad de elementos es la correcta", lista_largo(lista7)==10);
  print_test("el iterador esta al final", lista_iter_al_final(iter));


  lista_iter_destruir(iter);
  lista_destruir(lista7, NULL);

}



void pruebas_lista_alumno(){
  pruebas_lista_vacia_version_alumno();
  pruebas_lista_con_1_elemento();
  prueba_lista_con_algunos_elementos();
  prueba_de_volumen_lista();
  pruebas_lista_almacenando_vector_dinamico();

  prueba_iterador_externo_lista_vacia();
  prueba_iterador_externo_lista_con_1_elemento();
  prueba_iterador_externo_lista_con_algunos_elementos();
}
