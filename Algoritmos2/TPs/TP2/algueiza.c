//Entrega 1 TP2
//Correctora: Camila Dvorkin
//Grupo: G21
//Alumnos: Cambiano Agustín - Gualdieri Sofía



#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#include "strutil.h"
#include "hash.h"
#include "abb.h"
#include "vuelo.h"
#include "contador.h"
#include "heap.h"
#include "lista.h"
#include "auxiliares.h"
#include "algueiza.h"



#define SEPARADOR_ENTRADA_ESTANDAR ' '
#define SEPARADOR_DATOS_VUELOS ','
#define AGREGAR_ARCHIVO "agregar_archivo"
#define VER_TABLERO "ver_tablero"
#define INFO_VUELO "info_vuelo"
#define PRIORIDAD_VUELOS "prioridad_vuelos"
#define BORRAR "borrar"

#define RECORRIDO_ASCENDENTE "asc"
#define RECORRIDO_DESCENDENTE "desc"


int agregar_archivo(hash_t* hash, abb_t* abb, char** elementos_comando){

  FILE* vuelos = fopen (elementos_comando[1],"r");

  if (!vuelos){
    return NO_SE_PUDO_ABRIR_EL_ARCHIVO;
  }

  vuelo_t* vuelo;

  hash_iter_t* iter_hash=hash_iter_crear(hash);

  lista_t* actual;

  while (!hash_iter_al_final(iter_hash)) {
    vuelo=hash_obtener(hash, hash_iter_ver_actual(iter_hash));
    actual=abb_borrar(abb, vuelo_fecha(vuelo));
    if (actual!=NULL) {
      lista_destruir(actual, NULL);
    }
    hash_iter_avanzar(iter_hash);
  }

  hash_iter_destruir(iter_hash);


  char* informacion_vuelo=NULL;
  size_t tamanio;
  size_t largo=getline(&informacion_vuelo, &tamanio, vuelos);


  while (largo!=-1) {
    informacion_vuelo[largo-1]='\0';
    vuelo=vuelo_crear(informacion_vuelo, SEPARADOR_DATOS_VUELOS);

    if (!vuelo) {
      free(informacion_vuelo);
      fclose(vuelos);
      return ERROR_CON_MEMORIA_DINAMICA;
    }

    if (!hash_guardar(hash, vuelo_codigo(vuelo), vuelo)) {
      vuelo_destruir(vuelo);
      free(informacion_vuelo);
      fclose(vuelos);
      return ERROR_CON_MEMORIA_DINAMICA;
    }

    free(informacion_vuelo);

    informacion_vuelo=NULL;
    largo=getline(&informacion_vuelo, &tamanio, vuelos);

  }

  free(informacion_vuelo);
  fclose(vuelos);

  iter_hash=hash_iter_crear(hash);

  while (!hash_iter_al_final(iter_hash)) {
    vuelo=hash_obtener(hash, hash_iter_ver_actual(iter_hash));
    lista_t* codigos=abb_obtener(abb, vuelo_fecha(vuelo));
    if (!codigos) {
      codigos=lista_crear();
      if ((!codigos)||(!abb_guardar(abb, vuelo_fecha(vuelo), codigos))) {
        hash_iter_destruir(iter_hash);
        return ERROR_CON_MEMORIA_DINAMICA;
      }
    }
    if (!lista_insertar_ultimo(codigos, (void*)vuelo_codigo(vuelo))) {
      hash_iter_destruir(iter_hash);
      return ERROR_CON_MEMORIA_DINAMICA;
    }

    hash_iter_avanzar(iter_hash);
  }

  hash_iter_destruir(iter_hash);

  return PROCESO_REALIZADO_CON_EXITO;

}



int ver_tablero(hash_t* hash, abb_t* abb, char** elementos_comando){

  contador_t* vuelos_a_mostrar=contador_crear(obtener_entero(elementos_comando[1]));

  if (!vuelos_a_mostrar) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  auxiliar_ver_tablero_t auxiliar;

  auxiliar.hash=hash;
  auxiliar.indicador=true;

  if (!strcmp(RECORRIDO_ASCENDENTE, elementos_comando[2])) {
    auxiliar.ascendente=true;
  }else{
    auxiliar.ascendente=false;
  }

  auxiliar.contador=vuelos_a_mostrar;

  abb_in_order(abb, imprimir_en_orden, &auxiliar, elementos_comando[3], elementos_comando[4], elementos_comando[2]);

  contador_destruir(vuelos_a_mostrar);

  if (!auxiliar.indicador) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  return PROCESO_REALIZADO_CON_EXITO;

}


int info_vuelo(hash_t* hash, abb_t* abb, char** elementos_comando){

  vuelo_t* vuelo= hash_obtener(hash, elementos_comando[1]);

  if (!vuelo) {
    return VUELO_INEXISTENTE;
  }

  const char** informacion_vuelo=vuelo_obtener_informacion(vuelo);

  imprimir_arreglo_de_cadenas(informacion_vuelo);

  return PROCESO_REALIZADO_CON_EXITO;

}


int prioridad_vuelos(hash_t* hash, abb_t* abb, char** elementos_comando){

  heap_t* vuelos_por_prioridad=heap_crear(mayor_prioridad_inversa);

  if (!vuelos_por_prioridad) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  int vuelos_a_mostrar=obtener_entero(elementos_comando[1]);

  hash_iter_t* iter_hash=hash_iter_crear(hash);

  if (!iter_hash) {
    heap_destruir(vuelos_por_prioridad, NULL);
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  vuelo_t* actual;


  while (!hash_iter_al_final(iter_hash)) {

    actual=hash_obtener(hash, hash_iter_ver_actual(iter_hash));

    if (!heap_encolar(vuelos_por_prioridad, actual)) {
      hash_iter_destruir(iter_hash);
      heap_destruir(vuelos_por_prioridad, NULL);
      return ERROR_CON_MEMORIA_DINAMICA;
    }

    if (heap_cantidad(vuelos_por_prioridad)>vuelos_a_mostrar) {
      heap_desencolar(vuelos_por_prioridad);
    }

    hash_iter_avanzar(iter_hash);
  }

  hash_iter_destruir(iter_hash);
  imprimir_elementos_heap(vuelos_por_prioridad);
  heap_destruir(vuelos_por_prioridad, NULL);

  return PROCESO_REALIZADO_CON_EXITO;

}

int borrar(hash_t* hash, abb_t* abb, char** elementos_comando){

  lista_t* vuelos_a_borrar=lista_crear();

  if (!vuelos_a_borrar) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  lista_e_indicador_t extra;

  extra.lista=vuelos_a_borrar;
  extra.indicador=true;

  abb_in_order(abb, guardar_vuelos, &extra, elementos_comando[1], elementos_comando[2], ORDEN_ASCENDENTE);

  if (!extra.indicador) {
    lista_destruir(vuelos_a_borrar, free);
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  lista_t* codigos_fecha_actual;
  vuelo_t* vuelo_actual;
  char fecha_actual[20];

  while (!lista_esta_vacia(vuelos_a_borrar)) {
    codigos_fecha_actual=lista_borrar_primero(vuelos_a_borrar);
    strcpy(fecha_actual,vuelo_fecha(hash_obtener(hash, lista_ver_primero(codigos_fecha_actual))));
    while (!lista_esta_vacia(codigos_fecha_actual)) {
      vuelo_actual=hash_obtener(hash, lista_borrar_primero(codigos_fecha_actual));
      hash_borrar(hash, vuelo_codigo(vuelo_actual));
      imprimir_arreglo_de_cadenas(vuelo_obtener_informacion(vuelo_actual));
      vuelo_destruir(vuelo_actual);
    }
    lista_destruir(codigos_fecha_actual, NULL);
    lista_destruir(abb_borrar(abb, fecha_actual), NULL);
  }

  lista_destruir(vuelos_a_borrar, NULL);

  return PROCESO_REALIZADO_CON_EXITO;

}

comando_t obtener_comando_a_ejecutar(char** componentes_comando){

  size_t cantidad_de_elementos=cantidad_elementos((const char**)componentes_comando);


  if (!strcmp(componentes_comando[0], AGREGAR_ARCHIVO)) {

    if (agregar_archivo_es_valido(cantidad_de_elementos)) {
      return agregar_archivo;
    }
    return NULL;

  }else if(!strcmp(componentes_comando[0], VER_TABLERO)){

    if (ver_tablero_es_valido(componentes_comando, cantidad_de_elementos)) {
      return ver_tablero;
    }
    return NULL;

  }else if(!strcmp(componentes_comando[0], INFO_VUELO)){

    if (info_vuelo_es_valido(cantidad_de_elementos)) {
      return info_vuelo;
    }
    return NULL;

  }else if(!strcmp(componentes_comando[0], PRIORIDAD_VUELOS)){

    if (priodidad_vuelos_es_valido(componentes_comando, cantidad_de_elementos)) {
      return prioridad_vuelos;
    }
    return NULL;

  }else if(!strcmp(componentes_comando[0], BORRAR)){

    if (borrar_es_valido(componentes_comando, cantidad_de_elementos)) {
      return borrar;
    }
    return NULL;

  }

  return NULL;

}



int procesar_comando(hash_t* hash, abb_t* abb){

  int estado_de_ejecucion=PROCESO_REALIZADO_CON_EXITO;

  char* comando=NULL;
  size_t tamanio;

  size_t largo=getline(&comando, &tamanio, stdin);

  if (largo==-1) {
    free(comando);
    return SE_ACABO_EL_ARCHIVO;
  }

  comando[largo-1]='\0';

  char** componentes_comando=split(comando, SEPARADOR_ENTRADA_ESTANDAR);

  free(comando);
  comando=NULL;

  if (!componentes_comando) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  comando_t comando_a_ejecutar=obtener_comando_a_ejecutar(componentes_comando);

  if (!comando_a_ejecutar) {
    fprintf(stderr, "Error en comando %s\n", componentes_comando[0]);
    free_strv(componentes_comando);
    return COMANDO_INVALIDO;
  }

  estado_de_ejecucion=comando_a_ejecutar(hash, abb, componentes_comando);

  if (estado_de_ejecucion!=PROCESO_REALIZADO_CON_EXITO) {
    fprintf(stderr, "Error en comando %s\n", componentes_comando[0]);
    free_strv(componentes_comando);
    return COMANDO_INVALIDO;
  }

  free_strv(componentes_comando);

  printf("OK\n");

  return estado_de_ejecucion;

}


int main(int argc, char const *argv[]) {

  int estado_de_ejecucion;

  hash_t* hash_vuelos=hash_crear(destruir_vuelo);

  if (!hash_vuelos) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  abb_t* abb_vuelos=abb_crear(strcmp, destruir_lista);

  if (!abb_vuelos) {
    hash_destruir(hash_vuelos);
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  do {

    estado_de_ejecucion=procesar_comando(hash_vuelos, abb_vuelos);

  } while(estado_de_ejecucion!=SE_ACABO_EL_ARCHIVO);


  hash_destruir(hash_vuelos);
  abb_destruir(abb_vuelos);

  return 0;

}
