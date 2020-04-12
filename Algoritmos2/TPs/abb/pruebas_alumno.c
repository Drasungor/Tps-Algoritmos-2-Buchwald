/*
 * prueba_arbol.c
 * Pruebas para el tipo de dato abstracto Tabla de arbol
 * Copyright: (2011) Margarita Manterola, Maximiliano Curia
 * Licencia: CC-BY-SA 2.5 (ar) ó CC-BY-SA 3.0
 */
 //esto si queres lo dejamos

#include "abb.h"
#include "testing.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_crear_arbol_vacio(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones

  print_test("Prueba arbol crear arbol vacio", arbol);
  print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(arbol) == 0);
  print_test("Prueba arbol obtener clave A, es NULL, no existe", !abb_obtener(arbol, "A"));
  print_test("Prueba arbol pertenece clave A, es false, no existe", !abb_pertenece(arbol, "A"));
  print_test("Prueba arbol borrar clave A, es NULL, no existe", !abb_borrar(arbol, "A"));

  abb_destruir(arbol);
}

void prueba_iterar_arbol_vacio(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones
  abb_iter_t * iter = abb_iter_in_crear(arbol);

  print_test("Prueba arbol iter crear iterador arbol vacio", iter);
  print_test("Prueba arbol iter esta al final", abb_iter_in_al_final(iter));
  print_test("Prueba arbol iter avanzar es false", !abb_iter_in_avanzar(iter));
  print_test("Prueba arbol iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

  abb_iter_in_destruir(iter);
  abb_destruir(arbol);
}

void prueba_arbol_insertar(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones

  char *clave1 = "perro", *valor1 = "guau";
  char *clave2 = "gato", *valor2 = "miau";
  char *clave3 = "vaca", *valor3 = "mu";

  /* Inserta 1 valor y luego lo borra */
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1));
  print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1);
  print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));
  print_test("Prueba arbol borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
  print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

  /* Inserta otros 2 valores y no los borra (se destruyen con el arbol) */
  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2));
  print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2);
  print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3));
  print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(arbol) == 2);
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3);
  print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

  abb_destruir(arbol);
}

void prueba_arbol_reemplazar(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones

  char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";//podemos cambia los valores y las claves
  char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";//

  /* Inserta 2 valores y luego los reemplaza */
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

  print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
  print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
  print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

  abb_destruir(arbol);
}

void prueba_arbol_reemplazar_con_destruir(){

  abb_t* arbol = abb_crear(strcmp, free); //hay que asignarle las funciones


  char *clave1 = "perro", *valor1a, *valor1b;
  char *clave2 = "gato", *valor2a, *valor2b;

  /* Pide memoria para 4 valores */
  valor1a = malloc(10 * sizeof(char));
  valor1b = malloc(10 * sizeof(char));
  valor2a = malloc(10 * sizeof(char));
  valor2b = malloc(10 * sizeof(char));

  /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol obtener clave1 es valor1a", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol obtener clave2 es valor2a", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

  print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);
  print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);
  print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

  /* Se destruye el arbol (se debe liberar lo que quedó dentro) */
  abb_destruir(arbol);
}

void prueba_arbol_borrar(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones

  char *clave1 = "perro", *valor1 = "guau";
  char *clave2 = "gato", *valor2 = "miau";
  char *clave3 = "vaca", *valor3 = "mu";

  /* Inserta 3 valores y luego los borra */
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1));
  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2));
  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3));

  /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
  print_test("Prueba arbol pertenece clave3, es verdadero", abb_pertenece(arbol, clave3));
  print_test("Prueba arbol borrar clave3, es valor3", abb_borrar(arbol, clave3) == valor3);
  print_test("Prueba arbol borrar clave3, es NULL", !abb_borrar(arbol, clave3));
  print_test("Prueba arbol pertenece clave3, es falso", !abb_pertenece(arbol, clave3));
  print_test("Prueba arbol obtener clave3, es NULL", !abb_obtener(arbol, clave3));
  print_test("Prueba arbol la cantidad de elementos es 2", abb_cantidad(arbol) == 2);

  print_test("Prueba arbol pertenece clave1, es verdadero", abb_pertenece(arbol, clave1));
  print_test("Prueba arbol borrar clave1, es valor1", abb_borrar(arbol, clave1) == valor1);
  print_test("Prueba arbol borrar clave1, es NULL", !abb_borrar(arbol, clave3));
  print_test("Prueba arbol pertenece clave1, es falso", !abb_pertenece(arbol, clave1));
  print_test("Prueba arbol obtener clave1, es NULL", !abb_obtener(arbol, clave1));
  print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(arbol) == 1);

  print_test("Prueba arbol pertenece clave2, es verdadero", abb_pertenece(arbol, clave2));
  print_test("Prueba arbol borrar clave2, es valor2", abb_borrar(arbol, clave2) == valor2);
  print_test("Prueba arbol borrar clave2, es NULL", !abb_borrar(arbol, clave3));
  print_test("Prueba arbol pertenece clave2, es falso", !abb_pertenece(arbol, clave2));
  print_test("Prueba arbol obtener clave2, es NULL", !abb_obtener(arbol, clave2));
  print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

  abb_destruir(arbol);
}

void prueba_arbol_clave_vacia(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones

  char *clave = "", *valor = "";

  print_test("Prueba arbol insertar clave vacia", abb_guardar(arbol, clave, valor));
  print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
  print_test("Prueba arbol obtener clave vacia es valor", abb_obtener(arbol, clave) == valor);
  print_test("Prueba arbol pertenece clave vacia, es true", abb_pertenece(arbol, clave));
  print_test("Prueba arbol borrar clave vacia, es valor", abb_borrar(arbol, clave) == valor);
  print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

  abb_destruir(arbol);
}

void prueba_arbol_valor_null(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones

  char *clave = "", *valor = NULL;

  /* Inserta 1 valor y luego lo borra */
  print_test("Prueba arbol insertar clave vacia valor NULL", abb_guardar(arbol, clave, valor));
  print_test("Prueba arbol la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
  print_test("Prueba arbol obtener clave vacia es valor NULL", abb_obtener(arbol, clave) == valor);
  print_test("Prueba arbol pertenece clave vacia, es true", abb_pertenece(arbol, clave));
  print_test("Prueba arbol borrar clave vacia, es valor NULL", abb_borrar(arbol, clave) == valor);
  print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

  abb_destruir(arbol);
}

void prueba_arbol_volumen(size_t largo, bool debug){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones

  const size_t largo_clave = 10;
  char (*claves)[largo_clave] = malloc(largo * largo_clave);

  unsigned* valores[largo];

  /* Inserta 'largo' parejas en el arbol */
  bool ok = true;
  for (unsigned i = 0; i < largo; i++) {
      valores[i] = malloc(sizeof(int));
      sprintf(claves[i], "%08d", i);
      *valores[i] = i;
      ok = abb_guardar(arbol, claves[i], valores[i]);
      if (!ok) break;
  }


  if (debug) print_test("Prueba arbol almacenar muchos elementos", ok);
  if (debug) print_test("Prueba arbol la cantidad de elementos es correcta", abb_cantidad(arbol) == largo);

  /* Verifica que devuelva los valores correctos */
  for (size_t i = 0; i < largo; i++) {
      ok = abb_pertenece(arbol, claves[i]);
      if (!ok) break;
      ok = abb_obtener(arbol, claves[i]) == valores[i];
      if (!ok) break;
  }

  if (debug) print_test("Prueba arbol pertenece y obtener muchos elementos", ok);
  if (debug) print_test("Prueba arbol la cantidad de elementos es correcta", abb_cantidad(arbol) == largo);

  /* Verifica que borre y devuelva los valores correctos */
  for (size_t i = 0; i < largo; i++) {
      ok = abb_borrar(arbol, claves[i]) == valores[i];
      if (!ok) break;
  }

  if (debug) print_test("Prueba arbol borrar muchos elementos", ok);
  if (debug) print_test("Prueba arbol la cantidad de elementos es 0", abb_cantidad(arbol) == 0);

  /* Destruye el arbol y crea uno nuevo que sí libera */
  abb_destruir(arbol);
  arbol = abb_crear(strcmp, free); //hay que asignarle las funciones


  /* Inserta 'largo' parejas en el arbol */
  ok = true;
  for (size_t i = 0; i < largo; i++) {
      ok = abb_guardar(arbol, claves[i], valores[i]);
      if (!ok) break;
  }

  free(claves);

  /* Destruye el arbol - debería liberar los enteros */
  abb_destruir(arbol);

}

ssize_t buscar(const char* clave, char* claves[], size_t largo){

  for (size_t i = 0; i < largo; i++) {
      if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
  }
  return -1;
}

void prueba_arbol_iterar(){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones


  char *claves[] = {"perro", "gato", "vaca"};
  char *valores[] = {"guau", "miau", "mu"};

  /* Inserta 3 valores */
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, claves[0], valores[0]));
  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, claves[1], valores[1]));
  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, claves[2], valores[2]));

  // Prueba de iteración sobre las claves almacenadas.
  abb_iter_t * iter = abb_iter_in_crear(arbol);
  const char *clave;
  ssize_t indice;

  print_test("Prueba arbol iterador esta al final, es false", !abb_iter_in_al_final(iter));

  /* Primer valor */
  clave = abb_iter_in_ver_actual(iter);
  indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
  print_test("Prueba arbol iterador ver actual, es una clave valida", indice != -1);
  print_test("Prueba arbol iterador ver actual, no es el mismo puntero", clave != claves[indice]);
  print_test("Prueba arbol iterador avanzar es true", abb_iter_in_avanzar(iter));
  print_test("Prueba arbol iterador esta al final, es false", !abb_iter_in_al_final(iter));

  /* Segundo valor */
  clave = abb_iter_in_ver_actual(iter);
  indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
  print_test("Prueba arbol iterador ver actual, es una clave valida", indice != -1);
  print_test("Prueba arbol iterador ver actual, no es el mismo puntero", clave != claves[indice]);
  print_test("Prueba arbol iterador avanzar es true", abb_iter_in_avanzar(iter));
  print_test("Prueba arbol iterador esta al final, es false", !abb_iter_in_al_final(iter));

  /* Tercer valor */
  clave = abb_iter_in_ver_actual(iter);
  indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
  print_test("Prueba arbol iterador ver actual, es una clave valida", indice != -1);
  print_test("Prueba arbol iterador ver actual, no es el mismo puntero", clave != claves[indice]);
  /* Se anula esta prueba por diferencias de criterios */
  abb_iter_in_avanzar(iter);
  print_test("Prueba arbol iterador esta al final, es true", abb_iter_in_al_final(iter));

  /* Vuelve a tratar de avanzar, por las dudas */
  print_test("Prueba arbol iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
  print_test("Prueba arbol iterador avanzar es false", !abb_iter_in_avanzar(iter));
  print_test("Prueba arbol iterador esta al final, es true", abb_iter_in_al_final(iter));

  abb_iter_in_destruir(iter);
  abb_destruir(arbol);
}

void prueba_arbol_iterar_volumen(size_t largo){

  abb_t* arbol = abb_crear(strcmp, NULL); //hay que asignarle las funciones


  const size_t largo_clave = 10;
  char (*claves)[largo_clave] = malloc(largo * largo_clave);

  size_t valores[largo];

  /* Inserta 'largo' parejas en el arbol */
  bool ok = true;
  for (unsigned i = 0; i < largo; i++) {
      sprintf(claves[i], "%08d", i);
      valores[i] = i;
      ok = abb_guardar(arbol, claves[i], &valores[i]);
      if (!ok) break;
  }

  // Prueba de iteración sobre las claves almacenadas.
  abb_iter_t* iter = abb_iter_in_crear(arbol);
  print_test("Prueba arbol iterador esta al final, es false", !abb_iter_in_al_final(iter));

  ok = true;
  unsigned i;
  const char *clave;
  size_t *valor;

  for (i = 0; i < largo; i++) {
      if ( abb_iter_in_al_final(iter) ) {
          ok = false;
          break;
      }
      clave = abb_iter_in_ver_actual(iter);
      if ( clave == NULL ) {
          ok = false;
          break;
      }
      valor = abb_obtener(arbol, clave);
      if ( valor == NULL ) {
          ok = false;
          break;
      }
      *valor = largo;
      abb_iter_in_avanzar(iter);
  }
  print_test("Prueba arbol iteración en volumen", ok);
  print_test("Prueba arbol iteración en volumen, recorrio todo el largo", i == largo);
  print_test("Prueba arbol iterador esta al final, es true", abb_iter_in_al_final(iter));

  ok = true;
  for (i = 0; i < largo; i++) {
      if ( valores[i] != largo ) {
          ok = false;
          break;
      }
  }
  print_test("Prueba arbol iteración en volumen, se cambiaron todo los elementos", ok);

  abb_iter_in_destruir(iter);


  for (i = 0; i < largo/2; i++) {
      ok = abb_borrar(arbol, claves[i])== &valores[i];
      if (!ok) break;
  }

  free(claves);
  print_test("Se borro la mitad de los elementos correctamente", ok);

  abb_destruir(arbol);
}



void prueba_arbol_insertar_7_nodos_1(){

  abb_t* arbol = abb_crear(strcmp, NULL);

  char *clave1 = "ocho",    *valor1a = "8",  *valor1b = "08";
  char *clave2 = "cuatro",  *valor2a = "4",  *valor2b = "04";
  char *clave3 = "veinte",  *valor3a = "20", *valor3b = "020";
  char *clave4 = "doce",    *valor4a = "12", *valor4b = "012";
  char *clave5 = "quince",  *valor5a = "15",  *valor5b = "015";
  char *clave6 = "dos",     *valor6a = "2",  *valor6b = "02";
  char *clave7 = "nueve",   *valor7a = "9",  *valor7b = "09";


  // Inserta 7 valores y no lo borra
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));

  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3a));
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3a);
  print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

  print_test("Prueba arbol insertar clave4", abb_guardar(arbol, clave4, valor4a));
  print_test("Prueba arbol obtener clave es valor", abb_obtener(arbol, clave4) == valor4a);
  print_test("Prueba arbol pertenece clave4, es true", abb_pertenece(arbol, clave4));

  print_test("Prueba arbol insertar clave5", abb_guardar(arbol, clave5, valor5a));
  print_test("Prueba arbol obtener clave5 es valor5", abb_obtener(arbol, clave5) == valor5a);
  print_test("Prueba arbol pertenece clave5, es true", abb_pertenece(arbol, clave5));

  print_test("Prueba arbol insertar clave6", abb_guardar(arbol, clave6, valor6a));
  print_test("Prueba arbol obtener clave6 es valor6", abb_obtener(arbol, clave6) == valor6a);
  print_test("Prueba arbol pertenece clave6, es true", abb_pertenece(arbol, clave6));

  print_test("Prueba arbol insertar clave7", abb_guardar(arbol, clave7, valor7a));
  print_test("Prueba arbol obtener clave7 es valor7", abb_obtener(arbol, clave7) == valor7a);
  print_test("Prueba arbol pertenece clave7, es true", abb_pertenece(arbol, clave7));


  // Reemplazo los 7 valores
  print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);

  print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);

  print_test("Prueba arbol insertar clave3 con otro valor", abb_guardar(arbol, clave3, valor3b));
  print_test("Prueba arbol obtener clave3 es valor3b", abb_obtener(arbol, clave3) == valor3b);

  print_test("Prueba arbol insertar clave4 con otro valor", abb_guardar(arbol, clave4, valor4b));
  print_test("Prueba arbol obtener clave4 es valor4b", abb_obtener(arbol, clave4) == valor4b);

  print_test("Prueba arbol insertar clave5 con otro valor", abb_guardar(arbol, clave5, valor5b));
  print_test("Prueba arbol obtener clave5 es valor5b", abb_obtener(arbol, clave5) == valor5b);

  print_test("Prueba arbol insertar clave6 con otro valor", abb_guardar(arbol, clave6, valor6b));
  print_test("Prueba arbol obtener clave6 es valor6b", abb_obtener(arbol, clave6) == valor6b);

  print_test("Prueba arbol insertar clave7 con otro valor", abb_guardar(arbol, clave7, valor7b));
  print_test("Prueba arbol obtener clave7 es valor7b", abb_obtener(arbol, clave7) == valor7b);

  print_test("Prueba arbol la cantidad de elementos es 7", abb_cantidad(arbol) == 7);



  // Borro los 7 elementos
  print_test("Prueba arbol borrar clave1, es valor1b", abb_borrar(arbol, clave1) == valor1b);
  print_test("Prueba arbol borrar clave2, es valor2b", abb_borrar(arbol, clave2) == valor2b);
  print_test("Prueba arbol borrar clave3, es valor3b", abb_borrar(arbol, clave3) == valor3b);
  print_test("Prueba arbol borrar clave4, es valor4b", abb_borrar(arbol, clave4) == valor4b);
  print_test("Prueba arbol borrar clave5, es valor5b", abb_borrar(arbol, clave5) == valor5b);
  print_test("Prueba arbol borrar clave6, es valor6b", abb_borrar(arbol, clave6) == valor6b);
  print_test("Prueba arbol borrar clave7, es valor7b", abb_borrar(arbol, clave7) == valor7b);

  abb_destruir(arbol);
}

void prueba_arbol_insertar_7_nodos_2(){

  abb_t* arbol = abb_crear(strcmp, NULL);

  char *clave1 = "veinticuatro",    *valor1a = "24",  *valor1b = "024";
  char *clave2 = "diecisiete",  *valor2a = "17",  *valor2b = "017";
  char *clave3 = "tres",  *valor3a = "3", *valor3b = "03";
  char *clave4 = "cero",    *valor4a = "0", *valor4b = "00";
  char *clave5 = "cuarenta",  *valor5a = "40",  *valor5b = "040";
  char *clave6 = "veinticinco",     *valor6a = "25",  *valor6b = "025";
  char *clave7 = "setenta",   *valor7a = "70",  *valor7b = "070";


  // Inserta 7 valores y no lo borra
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));

  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3a));
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3a);
  print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

  print_test("Prueba arbol insertar clave4", abb_guardar(arbol, clave4, valor4a));
  print_test("Prueba arbol obtener clave es valor", abb_obtener(arbol, clave4) == valor4a);
  print_test("Prueba arbol pertenece clave4, es true", abb_pertenece(arbol, clave4));

  print_test("Prueba arbol insertar clave5", abb_guardar(arbol, clave5, valor5a));
  print_test("Prueba arbol obtener clave5 es valor5", abb_obtener(arbol, clave5) == valor5a);
  print_test("Prueba arbol pertenece clave5, es true", abb_pertenece(arbol, clave5));

  print_test("Prueba arbol insertar clave6", abb_guardar(arbol, clave6, valor6a));
  print_test("Prueba arbol obtener clave6 es valor6", abb_obtener(arbol, clave6) == valor6a);
  print_test("Prueba arbol pertenece clave6, es true", abb_pertenece(arbol, clave6));

  print_test("Prueba arbol insertar clave7", abb_guardar(arbol, clave7, valor7a));
  print_test("Prueba arbol obtener clave7 es valor7", abb_obtener(arbol, clave7) == valor7a);
  print_test("Prueba arbol pertenece clave7, es true", abb_pertenece(arbol, clave7));

  // Reemplazo los 7 valores
  print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);

  print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);

  print_test("Prueba arbol insertar clave3 con otro valor", abb_guardar(arbol, clave3, valor3b));
  print_test("Prueba arbol obtener clave3 es valor3b", abb_obtener(arbol, clave3) == valor3b);

  print_test("Prueba arbol insertar clave4 con otro valor", abb_guardar(arbol, clave4, valor4b));
  print_test("Prueba arbol obtener clave4 es valor4b", abb_obtener(arbol, clave4) == valor4b);

  print_test("Prueba arbol insertar clave5 con otro valor", abb_guardar(arbol, clave5, valor5b));
  print_test("Prueba arbol obtener clave5 es valor5b", abb_obtener(arbol, clave5) == valor5b);

  print_test("Prueba arbol insertar clave6 con otro valor", abb_guardar(arbol, clave6, valor6b));
  print_test("Prueba arbol obtener clave6 es valor6b", abb_obtener(arbol, clave6) == valor6b);

  print_test("Prueba arbol insertar clave7 con otro valor", abb_guardar(arbol, clave7, valor7b));
  print_test("Prueba arbol obtener clave7 es valor7b", abb_obtener(arbol, clave7) == valor7b);

  print_test("Prueba arbol la cantidad de elementos es 7", abb_cantidad(arbol) == 7);

  // Borro los 7 elementos
  print_test("Prueba arbol borrar clave1, es valor1b", abb_borrar(arbol, clave1) == valor1b);
  print_test("Prueba arbol borrar clave2, es valor2b", abb_borrar(arbol, clave2) == valor2b);
  print_test("Prueba arbol borrar clave3, es valor3b", abb_borrar(arbol, clave3) == valor3b);
  print_test("Prueba arbol borrar clave4, es valor4b", abb_borrar(arbol, clave4) == valor4b);
  print_test("Prueba arbol borrar clave5, es valor5b", abb_borrar(arbol, clave5) == valor5b);
  print_test("Prueba arbol borrar clave6, es valor6b", abb_borrar(arbol, clave6) == valor6b);
  print_test("Prueba arbol borrar clave7, es valor7b", abb_borrar(arbol, clave7) == valor7b);

  abb_destruir(arbol);
}

void prueba_arbol_insertar_7_nodos_3(){

  abb_t* arbol = abb_crear(strcmp, NULL);

  char *clave1 = "treinta y ocho",    *valor1a = "38",  *valor1b = "038";
  char *clave2 = "cuatro",  *valor2a = "4",  *valor2b = "04";
  char *clave3 = "diecinueve",  *valor3a = "19", *valor3b = "019";
  char *clave4 = "cien",    *valor4a = "100", *valor4b = "0100";
  char *clave5 = "sesenta y uno",  *valor5a = "61",  *valor5b = "061";
  char *clave6 = "dos",     *valor6a = "2",  *valor6b = "02";
  char *clave7 = "nueve",   *valor7a = "9",  *valor7b = "09";


  // Inserta 7 valores y no lo borra
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));

  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3a));
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3a);
  print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

  print_test("Prueba arbol insertar clave4", abb_guardar(arbol, clave4, valor4a));
  print_test("Prueba arbol obtener clave es valor", abb_obtener(arbol, clave4) == valor4a);
  print_test("Prueba arbol pertenece clave4, es true", abb_pertenece(arbol, clave4));

  print_test("Prueba arbol insertar clave5", abb_guardar(arbol, clave5, valor5a));
  print_test("Prueba arbol obtener clave5 es valor5", abb_obtener(arbol, clave5) == valor5a);
  print_test("Prueba arbol pertenece clave5, es true", abb_pertenece(arbol, clave5));

  print_test("Prueba arbol insertar clave6", abb_guardar(arbol, clave6, valor6a));
  print_test("Prueba arbol obtener clave6 es valor6", abb_obtener(arbol, clave6) == valor6a);
  print_test("Prueba arbol pertenece clave6, es true", abb_pertenece(arbol, clave6));

  print_test("Prueba arbol insertar clave7", abb_guardar(arbol, clave7, valor7a));
  print_test("Prueba arbol obtener clave7 es valor7", abb_obtener(arbol, clave7) == valor7a);
  print_test("Prueba arbol pertenece clave7, es true", abb_pertenece(arbol, clave7));

  // Reemplazo los 7 valores
  print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);

  print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);

  print_test("Prueba arbol insertar clave3 con otro valor", abb_guardar(arbol, clave3, valor3b));
  print_test("Prueba arbol obtener clave3 es valor3b", abb_obtener(arbol, clave3) == valor3b);

  print_test("Prueba arbol insertar clave4 con otro valor", abb_guardar(arbol, clave4, valor4b));
  print_test("Prueba arbol obtener clave4 es valor4b", abb_obtener(arbol, clave4) == valor4b);

  print_test("Prueba arbol insertar clave5 con otro valor", abb_guardar(arbol, clave5, valor5b));
  print_test("Prueba arbol obtener clave5 es valor5b", abb_obtener(arbol, clave5) == valor5b);

  print_test("Prueba arbol insertar clave6 con otro valor", abb_guardar(arbol, clave6, valor6b));
  print_test("Prueba arbol obtener clave6 es valor6b", abb_obtener(arbol, clave6) == valor6b);

  print_test("Prueba arbol insertar clave7 con otro valor", abb_guardar(arbol, clave7, valor7b));
  print_test("Prueba arbol obtener clave7 es valor7b", abb_obtener(arbol, clave7) == valor7b);

  print_test("Prueba arbol la cantidad de elementos es 7", abb_cantidad(arbol) == 7);

  // Borro los 7 elementos
  print_test("Prueba arbol borrar clave1, es valor1b", abb_borrar(arbol, clave1) == valor1b);
  print_test("Prueba arbol borrar clave2, es valor2b", abb_borrar(arbol, clave2) == valor2b);
  print_test("Prueba arbol borrar clave3, es valor3b", abb_borrar(arbol, clave3) == valor3b);
  print_test("Prueba arbol borrar clave4, es valor4b", abb_borrar(arbol, clave4) == valor4b);
  print_test("Prueba arbol borrar clave5, es valor5b", abb_borrar(arbol, clave5) == valor5b);
  print_test("Prueba arbol borrar clave6, es valor6b", abb_borrar(arbol, clave6) == valor6b);
  print_test("Prueba arbol borrar clave7, es valor7b", abb_borrar(arbol, clave7) == valor7b);

  abb_destruir(arbol);
}

void prueba_arbol_insertar_7_nodos_4(){

  abb_t* arbol = abb_crear(strcmp, NULL);

  char *clave1 = "setenta y dos",    *valor1a = "72",  *valor1b = "072";
  char *clave2 = "siete",  *valor2a = "7",  *valor2b = "07";
  char *clave3 = "noventa",  *valor3a = "90", *valor3b = "090";
  char *clave4 = "ochenta y siete",    *valor4a = "87", *valor4b = "087";
  char *clave5 = "veintiuno",  *valor5a = "21",  *valor5b = "021";
  char *clave6 = "noventa y cuatro",     *valor6a = "94",  *valor6b = "094";
  char *clave7 = "dieciseis",   *valor7a = "16",  *valor7b = "016";


  // Inserta 7 valores y no lo borra
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));

  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3a));
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3a);
  print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

  print_test("Prueba arbol insertar clave4", abb_guardar(arbol, clave4, valor4a));
  print_test("Prueba arbol obtener clave es valor", abb_obtener(arbol, clave4) == valor4a);
  print_test("Prueba arbol pertenece clave4, es true", abb_pertenece(arbol, clave4));

  print_test("Prueba arbol insertar clave5", abb_guardar(arbol, clave5, valor5a));
  print_test("Prueba arbol obtener clave5 es valor5", abb_obtener(arbol, clave5) == valor5a);
  print_test("Prueba arbol pertenece clave5, es true", abb_pertenece(arbol, clave5));

  print_test("Prueba arbol insertar clave6", abb_guardar(arbol, clave6, valor6a));
  print_test("Prueba arbol obtener clave6 es valor6", abb_obtener(arbol, clave6) == valor6a);
  print_test("Prueba arbol pertenece clave6, es true", abb_pertenece(arbol, clave6));

  print_test("Prueba arbol insertar clave7", abb_guardar(arbol, clave7, valor7a));
  print_test("Prueba arbol obtener clave7 es valor7", abb_obtener(arbol, clave7) == valor7a);
  print_test("Prueba arbol pertenece clave7, es true", abb_pertenece(arbol, clave7));

  // Reemplazo los 7 valores
  print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);

  print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);

  print_test("Prueba arbol insertar clave3 con otro valor", abb_guardar(arbol, clave3, valor3b));
  print_test("Prueba arbol obtener clave3 es valor3b", abb_obtener(arbol, clave3) == valor3b);

  print_test("Prueba arbol insertar clave4 con otro valor", abb_guardar(arbol, clave4, valor4b));
  print_test("Prueba arbol obtener clave4 es valor4b", abb_obtener(arbol, clave4) == valor4b);

  print_test("Prueba arbol insertar clave5 con otro valor", abb_guardar(arbol, clave5, valor5b));
  print_test("Prueba arbol obtener clave5 es valor5b", abb_obtener(arbol, clave5) == valor5b);

  print_test("Prueba arbol insertar clave6 con otro valor", abb_guardar(arbol, clave6, valor6b));
  print_test("Prueba arbol obtener clave6 es valor6b", abb_obtener(arbol, clave6) == valor6b);

  print_test("Prueba arbol insertar clave7 con otro valor", abb_guardar(arbol, clave7, valor7b));
  print_test("Prueba arbol obtener clave7 es valor7b", abb_obtener(arbol, clave7) == valor7b);

  print_test("Prueba arbol la cantidad de elementos es 7", abb_cantidad(arbol) == 7);

  // Borro los 7 elementos
  print_test("Prueba arbol borrar clave1, es valor1b", abb_borrar(arbol, clave1) == valor1b);
  print_test("Prueba arbol borrar clave2, es valor2b", abb_borrar(arbol, clave2) == valor2b);
  print_test("Prueba arbol borrar clave3, es valor3b", abb_borrar(arbol, clave3) == valor3b);
  print_test("Prueba arbol borrar clave4, es valor4b", abb_borrar(arbol, clave4) == valor4b);
  print_test("Prueba arbol borrar clave5, es valor5b", abb_borrar(arbol, clave5) == valor5b);
  print_test("Prueba arbol borrar clave6, es valor6b", abb_borrar(arbol, clave6) == valor6b);
  print_test("Prueba arbol borrar clave7, es valor7b", abb_borrar(arbol, clave7) == valor7b);

  abb_destruir(arbol);
}

void prueba_arbol_insertar_7_nodos_5(){

  abb_t* arbol = abb_crear(strcmp, NULL);

  char *clave1 = "treinta y tres",    *valor1a = "33",  *valor1b = "033";
  char *clave2 = "cincuenta y seis",  *valor2a = "56",  *valor2b = "056";
  char *clave3 = "diecisiete",  *valor3a = "17", *valor3b = "017";
  char *clave4 = "cuarenta y seis",    *valor4a = "46", *valor4b = "046";
  char *clave5 = "cincuenta y cinco",  *valor5a = "55",  *valor5b = "055";
  char *clave6 = "sesenta y uno",     *valor6a = "61",  *valor6b = "061";
  char *clave7 = "sesenta y tres",   *valor7a = "63",  *valor7b = "063";


  // Inserta 7 valores y no lo borra
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));

  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3a));
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3a);
  print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

  print_test("Prueba arbol insertar clave4", abb_guardar(arbol, clave4, valor4a));
  print_test("Prueba arbol obtener clave es valor", abb_obtener(arbol, clave4) == valor4a);
  print_test("Prueba arbol pertenece clave4, es true", abb_pertenece(arbol, clave4));

  print_test("Prueba arbol insertar clave5", abb_guardar(arbol, clave5, valor5a));
  print_test("Prueba arbol obtener clave5 es valor5", abb_obtener(arbol, clave5) == valor5a);
  print_test("Prueba arbol pertenece clave5, es true", abb_pertenece(arbol, clave5));

  print_test("Prueba arbol insertar clave6", abb_guardar(arbol, clave6, valor6a));
  print_test("Prueba arbol obtener clave6 es valor6", abb_obtener(arbol, clave6) == valor6a);
  print_test("Prueba arbol pertenece clave6, es true", abb_pertenece(arbol, clave6));

  print_test("Prueba arbol insertar clave7", abb_guardar(arbol, clave7, valor7a));
  print_test("Prueba arbol obtener clave7 es valor7", abb_obtener(arbol, clave7) == valor7a);
  print_test("Prueba arbol pertenece clave7, es true", abb_pertenece(arbol, clave7));

  // Reemplazo los 7 valores
  print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
  print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);

  print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
  print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);

  print_test("Prueba arbol insertar clave3 con otro valor", abb_guardar(arbol, clave3, valor3b));
  print_test("Prueba arbol obtener clave3 es valor3b", abb_obtener(arbol, clave3) == valor3b);

  print_test("Prueba arbol insertar clave4 con otro valor", abb_guardar(arbol, clave4, valor4b));
  print_test("Prueba arbol obtener clave4 es valor4b", abb_obtener(arbol, clave4) == valor4b);

  print_test("Prueba arbol insertar clave5 con otro valor", abb_guardar(arbol, clave5, valor5b));
  print_test("Prueba arbol obtener clave5 es valor5b", abb_obtener(arbol, clave5) == valor5b);

  print_test("Prueba arbol insertar clave6 con otro valor", abb_guardar(arbol, clave6, valor6b));
  print_test("Prueba arbol obtener clave6 es valor6b", abb_obtener(arbol, clave6) == valor6b);

  print_test("Prueba arbol insertar clave7 con otro valor", abb_guardar(arbol, clave7, valor7b));
  print_test("Prueba arbol obtener clave7 es valor7b", abb_obtener(arbol, clave7) == valor7b);

  print_test("Prueba arbol la cantidad de elementos es 7", abb_cantidad(arbol) == 7);

  // Borro los 7 elementos
  print_test("Prueba arbol borrar clave1, es valor1b", abb_borrar(arbol, clave1) == valor1b);
  print_test("Prueba arbol borrar clave2, es valor2b", abb_borrar(arbol, clave2) == valor2b);
  print_test("Prueba arbol borrar clave3, es valor3b", abb_borrar(arbol, clave3) == valor3b);
  print_test("Prueba arbol borrar clave4, es valor4b", abb_borrar(arbol, clave4) == valor4b);
  print_test("Prueba arbol borrar clave5, es valor5b", abb_borrar(arbol, clave5) == valor5b);
  print_test("Prueba arbol borrar clave6, es valor6b", abb_borrar(arbol, clave6) == valor6b);
  print_test("Prueba arbol borrar clave7, es valor7b", abb_borrar(arbol, clave7) == valor7b);

  abb_destruir(arbol);
}

void prueba_arbol_insertar_7_nodos_termina_en_lista(){

 abb_t* arbol = abb_crear(strcmp, NULL);

 char *clave1 = "uno",    *valor1a = "1",  *valor1b = "01";
 char *clave2 = "dos",  *valor2a = "2",  *valor2b = "02";
 char *clave3 = "tres",  *valor3a = "3", *valor3b = "03";
 char *clave4 = "cuatro",    *valor4a = "4", *valor4b = "04";
 char *clave5 = "cinco",  *valor5a = "5",  *valor5b = "05";
 char *clave6 = "seis",     *valor6a = "6",  *valor6b = "06";
 char *clave7 = "siete",   *valor7a = "7",  *valor7b = "07";


 // Inserta 7 valores y no lo borra
 print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
 print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1a);
 print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));

 print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
 print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2a);
 print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

 print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3a));
 print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3a);
 print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

 print_test("Prueba arbol insertar clave4", abb_guardar(arbol, clave4, valor4a));
 print_test("Prueba arbol obtener clave es valor", abb_obtener(arbol, clave4) == valor4a);
 print_test("Prueba arbol pertenece clave4, es true", abb_pertenece(arbol, clave4));

 print_test("Prueba arbol insertar clave5", abb_guardar(arbol, clave5, valor5a));
 print_test("Prueba arbol obtener clave5 es valor5", abb_obtener(arbol, clave5) == valor5a);
 print_test("Prueba arbol pertenece clave5, es true", abb_pertenece(arbol, clave5));

 print_test("Prueba arbol insertar clave6", abb_guardar(arbol, clave6, valor6a));
 print_test("Prueba arbol obtener clave6 es valor6", abb_obtener(arbol, clave6) == valor6a);
 print_test("Prueba arbol pertenece clave6, es true", abb_pertenece(arbol, clave6));

 print_test("Prueba arbol insertar clave7", abb_guardar(arbol, clave7, valor7a));
 print_test("Prueba arbol obtener clave7 es valor7", abb_obtener(arbol, clave7) == valor7a);
 print_test("Prueba arbol pertenece clave7, es true", abb_pertenece(arbol, clave7));

 // Reemplazo los 7 valores
 print_test("Prueba arbol insertar clave1 con otro valor", abb_guardar(arbol, clave1, valor1b));
 print_test("Prueba arbol obtener clave1 es valor1b", abb_obtener(arbol, clave1) == valor1b);

 print_test("Prueba arbol insertar clave2 con otro valor", abb_guardar(arbol, clave2, valor2b));
 print_test("Prueba arbol obtener clave2 es valor2b", abb_obtener(arbol, clave2) == valor2b);

 print_test("Prueba arbol insertar clave3 con otro valor", abb_guardar(arbol, clave3, valor3b));
 print_test("Prueba arbol obtener clave3 es valor3b", abb_obtener(arbol, clave3) == valor3b);

 print_test("Prueba arbol insertar clave4 con otro valor", abb_guardar(arbol, clave4, valor4b));
 print_test("Prueba arbol obtener clave4 es valor4b", abb_obtener(arbol, clave4) == valor4b);

 print_test("Prueba arbol insertar clave5 con otro valor", abb_guardar(arbol, clave5, valor5b));
 print_test("Prueba arbol obtener clave5 es valor5b", abb_obtener(arbol, clave5) == valor5b);

 print_test("Prueba arbol insertar clave6 con otro valor", abb_guardar(arbol, clave6, valor6b));
 print_test("Prueba arbol obtener clave6 es valor6b", abb_obtener(arbol, clave6) == valor6b);

 print_test("Prueba arbol insertar clave7 con otro valor", abb_guardar(arbol, clave7, valor7b));
 print_test("Prueba arbol obtener clave7 es valor7b", abb_obtener(arbol, clave7) == valor7b);

 print_test("Prueba arbol la cantidad de elementos es 7", abb_cantidad(arbol) == 7);

 // Borro los 7 elementos
 print_test("Prueba arbol borrar clave1, es valor1b", abb_borrar(arbol, clave1) == valor1b);
 print_test("Prueba arbol borrar clave2, es valor2b", abb_borrar(arbol, clave2) == valor2b);
 print_test("Prueba arbol borrar clave3, es valor3b", abb_borrar(arbol, clave3) == valor3b);
 print_test("Prueba arbol borrar clave4, es valor4b", abb_borrar(arbol, clave4) == valor4b);
 print_test("Prueba arbol borrar clave5, es valor5b", abb_borrar(arbol, clave5) == valor5b);
 print_test("Prueba arbol borrar clave6, es valor6b", abb_borrar(arbol, clave6) == valor6b);
 print_test("Prueba arbol borrar clave7, es valor7b", abb_borrar(arbol, clave7) == valor7b);

 abb_destruir(arbol);
}

void borrar_varias_veces_la_raiz(){

  abb_t* arbol = abb_crear(strcmp, NULL);

  char *clave1 = "ocho",    *valor1a = "8";
  char *clave2 = "cuatro",  *valor2a = "4";
  char *clave3 = "veinte",  *valor3a = "20";
  char *clave4 = "doce",    *valor4a = "12";
  char *clave5 = "quince",  *valor5a = "15";
  char *clave6 = "dos",     *valor6a = "2";
  char *clave7 = "nueve",   *valor7a = "9";


  // Inserta 7 valores y no lo borra
  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1a));
  print_test("Prueba arbol obtener clave1 es valor1", abb_obtener(arbol, clave1) == valor1a);
  print_test("Prueba arbol pertenece clave1, es true", abb_pertenece(arbol, clave1));

  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2a));
  print_test("Prueba arbol obtener clave2 es valor2", abb_obtener(arbol, clave2) == valor2a);
  print_test("Prueba arbol pertenece clave2, es true", abb_pertenece(arbol, clave2));

  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3a));
  print_test("Prueba arbol obtener clave3 es valor3", abb_obtener(arbol, clave3) == valor3a);
  print_test("Prueba arbol pertenece clave3, es true", abb_pertenece(arbol, clave3));

  print_test("Prueba arbol insertar clave4", abb_guardar(arbol, clave4, valor4a));
  print_test("Prueba arbol obtener clave es valor", abb_obtener(arbol, clave4) == valor4a);
  print_test("Prueba arbol pertenece clave4, es true", abb_pertenece(arbol, clave4));

  print_test("Prueba arbol insertar clave5", abb_guardar(arbol, clave5, valor5a));
  print_test("Prueba arbol obtener clave5 es valor5", abb_obtener(arbol, clave5) == valor5a);
  print_test("Prueba arbol pertenece clave5, es true", abb_pertenece(arbol, clave5));

  print_test("Prueba arbol insertar clave6", abb_guardar(arbol, clave6, valor6a));
  print_test("Prueba arbol obtener clave6 es valor6", abb_obtener(arbol, clave6) == valor6a);
  print_test("Prueba arbol pertenece clave6, es true", abb_pertenece(arbol, clave6));

  print_test("Prueba arbol insertar clave7", abb_guardar(arbol, clave7, valor7a));
  print_test("Prueba arbol obtener clave7 es valor7", abb_obtener(arbol, clave7) == valor7a);
  print_test("Prueba arbol pertenece clave7, es true", abb_pertenece(arbol, clave7));


  // Borro la raiz cada vez
  print_test("Prueba arbol borrar clave1 que es raiz, es valor1a", abb_borrar(arbol, clave1) == valor1a);
  print_test("Prueba arbol borrar clave2 que es raiz , es valor2a", abb_borrar(arbol, clave2) == valor2a);
  print_test("Prueba arbol borrar clave6 que es raiz, es valor6a", abb_borrar(arbol, clave6) == valor6a);
  print_test("Prueba arbol borrar clave3 que es raiz, es valor3a", abb_borrar(arbol, clave3) == valor3a);
  print_test("Prueba arbol borrar clave4 que es raiz, es valor4a", abb_borrar(arbol, clave4) == valor4a);
  print_test("Prueba arbol borrar clave7 que es raiz, es valor7a", abb_borrar(arbol, clave7) == valor7a);
  print_test("Prueba arbol borrar clave5 que es raiz, es valor5a", abb_borrar(arbol, clave5) == valor5a);

  abb_destruir(arbol);
}






bool imprimir_elementos (const  char* clave, void * dato , void *extra){
  printf("Clave: %s, Dato: %s \n", clave, (char*)dato);
  return true;
}

bool imprimir_elementos2 (const  char* clave, void * dato , void *extra){

  if (atoi((char*)dato)<15) {
    printf("Clave: %s, Dato: %s \n", clave, (char*)dato);
    return true;
  }

  return false;
}



void prueba_iterador_interno(){
  abb_t* arbol = abb_crear(strcmp, NULL);

  char *clave1 = "ocho",    *valor1 = "8";
  char *clave2 = "cuatro",  *valor2 = "4";
  char *clave3 = "veinte",  *valor3 = "20";
  char *clave4 = "doce",    *valor4 = "12";
  char *clave5 = "quince",  *valor5 = "15";
  char *clave6 = "dos",     *valor6 = "2";
  char *clave7 = "nueve",   *valor7 = "9";

  print_test("Prueba arbol insertar clave1", abb_guardar(arbol, clave1, valor1));
  print_test("Prueba arbol insertar clave2", abb_guardar(arbol, clave2, valor2));
  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave3, valor3));
  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave4, valor4));
  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave5, valor5));
  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave6, valor6));
  print_test("Prueba arbol insertar clave3", abb_guardar(arbol, clave7, valor7));

  abb_in_order(arbol, imprimir_elementos, NULL);
  printf("\n");
  abb_in_order(arbol, imprimir_elementos2, NULL);

  abb_destruir(arbol);

}




////////////////////////////////////////////////////////////////////

void pruebas_arbol(){

  prueba_crear_arbol_vacio();
  prueba_iterar_arbol_vacio();
  prueba_arbol_insertar();
  prueba_arbol_reemplazar();
  prueba_arbol_reemplazar_con_destruir();
  prueba_arbol_borrar();
  prueba_arbol_clave_vacia();
  prueba_arbol_valor_null();
  prueba_arbol_volumen(1000, true);
  prueba_arbol_iterar();
  prueba_arbol_iterar_volumen(1000);
  prueba_iterador_interno();
  prueba_arbol_insertar_7_nodos_1();
  prueba_arbol_insertar_7_nodos_2();
  prueba_arbol_insertar_7_nodos_3();
  prueba_arbol_insertar_7_nodos_4();
  prueba_arbol_insertar_7_nodos_5();
  prueba_arbol_insertar_7_nodos_termina_en_lista();
  borrar_varias_veces_la_raiz();

}

void pruebas_volumen(size_t largo)
{
    prueba_arbol_volumen(largo, false);
}







void pruebas_abb_alumno(){

  pruebas_arbol();
  //pruebas_volumen(5000);

}
