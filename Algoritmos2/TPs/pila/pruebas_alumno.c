#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


void pruebas_pila_vacia_version_alumno(){
  printf("INICIO DE PRUEBAS CON PILA DE TAMANIO 0\n");


  pila_t* pila1= pila_crear();

  print_test("crear pila vacia", pila_esta_vacia(pila1));
  print_test("ver tope de la pila vacia", !pila_ver_tope(pila1));
  print_test("desapilar tope de la pila vacia", !pila_desapilar(pila1));
  pila_destruir(pila1);
}


void pruebas_pila_con_1_elemento(){
  printf("INICIO DE PRUEBAS CON PILA DE TAMANIO 1\n");

  pila_t* pila2= pila_crear();
  int elemento_a_agregar=5;

  print_test("apilar un elemento", pila_apilar(pila2, &elemento_a_agregar));

  //se asume que el elemento anterior fue apilado correctamente
  print_test("ver si la pila esta vacia teniendo 1 elemento", !pila_esta_vacia(pila2));
  print_test("ver tope de la pila no vacia", pila_ver_tope(pila2)==&elemento_a_agregar);
  print_test("desapilar un elemento", pila_desapilar(pila2)==&elemento_a_agregar);
  print_test("se desapiló el elemento y la pila está vacía", pila_esta_vacia(pila2));
  pila_destruir(pila2);

}

void prueba_pila_con_algunos_elementos(){
  printf("INICIO DE PRUEBAS CON PILA DE ALGUNOS ELEMENTOS\n");

  pila_t* pila3= pila_crear();

  int elementos[10]={7,64,-23,-769,1463,37,469,1,-1,10};
  bool se_apilo_bien=true;
  bool se_desapilo_bien=true;

  for (size_t i = 0; i < 10; i++) {
    if (!pila_apilar(pila3, &elementos[i])) {
      se_apilo_bien=false;
      break;
    }
  }

  print_test("apilar elementos", se_apilo_bien);
  print_test("la pila no esta vacia", !pila_esta_vacia(pila3));
  print_test("obtener tope de la pila", pila_ver_tope(pila3)==&elementos[9]);


  for (int i = 9; i > -1; i--) {
    if (pila_desapilar(pila3)!=&elementos[i]) {
      se_desapilo_bien=false;
      break;
    }

    if (i==5) {
      print_test("la pila no está vacía habiendo vaciado la mitad", !pila_esta_vacia(pila3));
    }

  }
  print_test("desapilar elementos", se_desapilo_bien);

  print_test("la pila esta vacía después de desapilar", pila_esta_vacia(pila3));

  print_test("se recibe null cuando se intenta desapilar la pila vacia", !pila_desapilar(pila3));
  print_test("se recibe null cuando se intenta leer el tope de la pila vacia", !pila_ver_tope(pila3));

  pila_destruir(pila3);

}


void prueba_de_volumen_pila(){
  printf("INICIO PRUEBAS DE VOLUMEN\n");

  int* vector_dinamico=malloc(100000*sizeof(int));
  pila_t* pila4= pila_crear();

  bool se_apilo_bien=true;
  bool se_desapilo_bien=true;

  for (int i = 0; i < 100000; i++) {
      vector_dinamico[i]=i;

      if (!pila_apilar(pila4, &vector_dinamico[i])) {
        se_apilo_bien=false;
        break;
      }

      if (i%25000==0) {
        print_test("la pila no esta vacía teniendo algunos elementos", !pila_esta_vacia(pila4));
        print_test("el tope de la pila es el ultimo elemento apilado", pila_ver_tope(pila4)==&vector_dinamico[i]);
      }
  }

  print_test("se apilaron todos los elementos", se_apilo_bien);
  print_test("el tope de la pila es el ultimo elemento apilado", pila_ver_tope(pila4)==&vector_dinamico[100000-1]);


  for (int i = 100000-1; i > -1; i--) {

    if ((i%25000==0)&&(i!=0)) {
      print_test("la pila no esta vacía teniendo algunos elementos", !pila_esta_vacia(pila4));
      print_test("el tope de la pila es el correcto", pila_ver_tope(pila4)==&vector_dinamico[i]);
    }

    if (pila_desapilar(pila4)!=&vector_dinamico[i]) {
      se_desapilo_bien=false;
      break;
    }
  }

  print_test("se desapilaron todos los elementos correctamente", se_desapilo_bien);
  print_test("la pila esta vacía", pila_esta_vacia(pila4));

  pila_destruir(pila4);
  free(vector_dinamico);

}



void pruebas_pila_alumno() {
  pruebas_pila_vacia_version_alumno();
  pruebas_pila_con_1_elemento();
  prueba_pila_con_algunos_elementos();
  prueba_de_volumen_pila();
}
