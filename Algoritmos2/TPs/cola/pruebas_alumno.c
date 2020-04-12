#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


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


void pruebas_cola_vacia_version_alumno(){
  printf("INICIO DE PRUEBAS CON COLA DE TAMANIO 0\n");

  cola_t* cola1= cola_crear();

  print_test("crear cola vacia", cola_esta_vacia(cola1));
  print_test("ver primer elemento de la cola vacia", !cola_ver_primero(cola1));
  print_test("desencolar primer elemento de la cola vacia", !cola_desencolar(cola1));
  cola_destruir(cola1, NULL);

}


void pruebas_cola_con_1_elemento(){
  printf("INICIO DE PRUEBAS CON COLA DE TAMANIO 1\n");

  cola_t* cola2= cola_crear();
  int elemento_a_agregar=5;

  print_test("encolar un elemento", cola_encolar(cola2, &elemento_a_agregar));

  //se asume que el elemento anterior fue acolado correctamente
  print_test("ver si la cola esta vacia teniendo 1 elemento", !cola_esta_vacia(cola2));
  print_test("ver primer elemento de la cola no vacia", cola_ver_primero(cola2)==&elemento_a_agregar);
  print_test("desencolar un elemento", cola_desencolar(cola2)==&elemento_a_agregar);
  print_test("se desencolo el elemento y la cola está vacía", cola_esta_vacia(cola2));
  print_test("se encola el elemento NULL", cola_encolar(cola2, NULL));
  print_test("el primer elemento es NULL y la cola no esta vacia", (!cola_esta_vacia(cola2))&&(!cola_ver_primero(cola2)));
  cola_destruir(cola2, NULL);

}

void prueba_cola_con_algunos_elementos(){
  printf("INICIO DE PRUEBAS CON COLA DE ALGUNOS ELEMENTOS\n");

  cola_t* cola3= cola_crear();

  int elementos[10]={7,64,-23,-769,1463,37,469,1,-1,10};
  bool se_encolo_bien=true;
  bool se_desencolo_bien=true;

  for (size_t i = 0; i < 10; i++) {
    if (!cola_encolar(cola3, &elementos[i])) {
      se_encolo_bien=false;
      break;
    }
  }

  print_test("encolar elementos", se_encolo_bien);
  print_test("la cola no esta vacia", !cola_esta_vacia(cola3));
  print_test("obtener primer valor de la cola", cola_ver_primero(cola3)==&elementos[0]);


  for (int i = 0; i <10; i++) {
    if (cola_desencolar(cola3)!=&elementos[i]) {
      se_desencolo_bien=false;
      break;
    }

    if (i==5) {
      print_test("la cola no está vacía habiendo vaciado la mitad", !cola_esta_vacia(cola3));
    }

  }
  print_test("desencolar elementos", se_desencolo_bien);

  print_test("la cola esta vacía después de desacolar", cola_esta_vacia(cola3));

  print_test("se recibe null cuando se intenta desacolar la cola vacia", !cola_desencolar(cola3));
  print_test("se recibe null cuando se intenta leer el tope de la cola vacia", !cola_ver_primero(cola3));



  //se encolan nuevamente los elementos para probar que
  //no se pierda información al usar cola_destruir con una
  //cola que no esta vacia
  se_encolo_bien=true;
  for (size_t i = 0; i < 10; i++) {
    if (!cola_encolar(cola3, &elementos[i])) {
      se_encolo_bien=false;
      break;
    }
  }

  print_test("se encola nuevamente", se_encolo_bien);

  cola_destruir(cola3, NULL);

}


void prueba_de_volumen_cola(){
  printf("INICIO PRUEBAS DE VOLUMEN\n");

  int* vector_dinamico= malloc(100000*sizeof(int*));

  if (!vector_dinamico) {
    return;
  }

  cola_t* cola4= cola_crear();

  bool se_encolo_bien=true;
  bool se_desencolo_bien=true;

  for (int i = 0; i < 100000; i++) {
      vector_dinamico[i]=i;

      if (!cola_encolar(cola4, &vector_dinamico[i])) {
        se_encolo_bien=false;
        break;
      }

      if (i%25000==0) {
        print_test("la cola no esta vacía teniendo algunos elementos", !cola_esta_vacia(cola4));
      }
  }

  print_test("se acolaron todos los elementos", se_encolo_bien);

  print_test("el primer valor de la cola es el primer elemento acolado", cola_ver_primero(cola4)==&vector_dinamico[0]);


  for (int i = 0; i < 100000; i++) {

    if ((i%25000==0)&&(i!=0)) {
      print_test("la cola no esta vacía teniendo algunos elementos", !cola_esta_vacia(cola4));

      print_test("el primer valor de la cola es el correcto", cola_ver_primero(cola4)==&vector_dinamico[i]);
    }

    if (cola_desencolar(cola4)!=&vector_dinamico[i]) {
      se_desencolo_bien=false;
      break;
    }
  }

  print_test("se desencolaron correctamente los elementos que habían sido encolados", se_desencolo_bien);
  print_test("la cola esta vacía", cola_esta_vacia(cola4));

  cola_destruir(cola4, NULL);
  free(vector_dinamico);

}


void pruebas_cola_almacenando_vector_dinamico(){
  printf("INICIO PRUEBAS ALMACENANDO VECTORES DINAMICOS\n");

  int *vector_dinamico1=NULL, *vector_dinamico2=NULL, *vector_dinamico3=NULL, *vector_dinamico4=NULL, *vector_dinamico5=NULL;

  int* vectores_dinamicos[5]={vector_dinamico1, vector_dinamico2, vector_dinamico3, vector_dinamico4, vector_dinamico5};

  if (!crear_vectores_dinamicos(vectores_dinamicos)) {
    return;
  }

  inicializar_vectores_dinamicos(vectores_dinamicos);

  cola_t* cola4= cola_crear();

  bool se_encolo_bien=true;

  for (size_t i = 0; i < 5; i++) {
    se_encolo_bien=cola_encolar(cola4, vectores_dinamicos[i]);
  }

  print_test("se introdujeron los vectores dinamicos en la cola", se_encolo_bien);
  print_test("el primer elemento de la cola es el primer elemento introducido", cola_ver_primero(cola4)==vectores_dinamicos[0]);

  cola_destruir(cola4, free);

}


void pruebas_cola_alumno(){
  pruebas_cola_vacia_version_alumno();
  pruebas_cola_con_1_elemento();
  prueba_cola_con_algunos_elementos();
  prueba_de_volumen_cola();
  pruebas_cola_almacenando_vector_dinamico();
}
