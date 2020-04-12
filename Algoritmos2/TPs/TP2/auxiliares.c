#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "auxiliares.h"
#include "vuelo.h"
#include "contador.h"
#include "heap.h"
#include "lista.h"
#include "strutil.h"
#include "hash.h"

#define SEPARADOR_DIA_HORA 'T'
#define SEPARADOR_DIA '-'
#define SEPARADOR_HORA ':'
#define FECHA_VALIDA 1
#define FECHA_INVALIDA 0




//Intercambia los valores almacenados en las variables pasadas
static void swap (char** x, char** y) {

	void* auxiliar= *x;

	*x=*y;
	*y=auxiliar;

}


/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(char* vector[], size_t n) {

	int mayor_elemento=0;

	if (n==0) {
		return -1;
	}

	for (int i = 1; i < n; i++) {
    if (strcmp(vector[i], vector[mayor_elemento])>0) {
      mayor_elemento=i;
    }
	}

	return mayor_elemento;

}


/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(char* vector[], size_t n) {

	int maximo_elemento=0;

  for (int i = 0; i < n; i++) {
		maximo_elemento=maximo(vector, n-i);
		swap(&vector[n-1-i],&vector[maximo_elemento]);
	}

}


//Indica si la cadena pasada representa a un entero
bool es_un_entero(char* cadena){

  size_t largo_cadena= strlen(cadena);

  //ascii 0: 48
  //ascii 9: 57
  int primer_digito=0;

  if (cadena[0]=='-') {
    primer_digito=1;

    if (largo_cadena==1) {
      return false;
    }
  }

  for (size_t i = primer_digito; i < largo_cadena; i++) {
    if ((cadena[i]<48)||(cadena[i]>57)) {
      return false;
    }
  }

  return true;
}



void imprimir_arreglo_de_cadenas(const char** cadenas) {
  size_t i=0;

  while (cadenas[i]!=NULL) {
    printf("%s", cadenas[i]);
    if (cadenas[i+1]!=NULL) {
      printf(" ");
    }
    i++;
  }

  printf("\n");

}




int mayor_prioridad_inversa(const void* vuelo1, const void* vuelo2){

  size_t prioridad1=vuelo_prioridad((vuelo_t*)vuelo1);
  size_t prioridad2=vuelo_prioridad((vuelo_t*)vuelo2);

  if (prioridad1<prioridad2) {
    return 1;
  }

  if (prioridad1>prioridad2) {
    return -1;
  }

  return strcmp(vuelo_codigo((vuelo_t*)vuelo1), vuelo_codigo((vuelo_t*)vuelo2));

}



size_t cantidad_elementos(const char** arr_cadenas){

  size_t cantidad=0;

  size_t i=0;

  while (arr_cadenas[i]!=NULL) {
    cantidad++;
    i++;
  }

  return cantidad;

}


//Indica si la fecha pasada es válida
int es_fecha_valida(char* fecha){

  char** dia_y_hora=split(fecha, SEPARADOR_DIA_HORA);

  if (!dia_y_hora) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  if (cantidad_elementos((const char**)dia_y_hora)!=2) {
    free_strv(dia_y_hora);
    return FECHA_INVALIDA;
  }

  char** dia=split(dia_y_hora[0], SEPARADOR_DIA);

  if (!dia) {
    free_strv(dia_y_hora);
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  if (cantidad_elementos((const char**)dia)!=3) {
    free_strv(dia);
    free_strv(dia_y_hora);
    return FECHA_INVALIDA;
  }

  for (size_t i = 0; i < 3; i++) {
    if (!es_un_entero(dia[i])) {
      free_strv(dia);
      free_strv(dia_y_hora);
      return FECHA_INVALIDA;
    }
  }


  char** hora=split(dia_y_hora[1], SEPARADOR_HORA);

  if (!hora) {
    free_strv(dia);
    free_strv(dia_y_hora);
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  if (cantidad_elementos((const char**)dia)!=3) {
    free_strv(dia);
    free_strv(hora);
    free_strv(dia_y_hora);
    return FECHA_INVALIDA;
  }

  for (size_t i = 0; i < 3; i++) {
    if (!es_un_entero(hora[i])) {
      free_strv(dia);
      free_strv(hora);
      free_strv(dia_y_hora);
      return FECHA_INVALIDA;
    }
  }

  free_strv(dia);
  free_strv(hora);
  free_strv(dia_y_hora);

  return FECHA_VALIDA;

}




void destruir_vuelo(void* vuelo){

  vuelo_destruir((vuelo_t*)vuelo);

}


//Desencola todos los elementos del heap y los imprime de menor
//a mayor prioridad
void imprimir_elementos_heap(heap_t* heap){

  if (heap_esta_vacio(heap)) {
    return;
  }

  vuelo_t* vuelo= heap_desencolar(heap);

  imprimir_elementos_heap(heap);

  printf("%lu - %s\n", vuelo_prioridad(vuelo), vuelo_codigo(vuelo));
}



//Devuelve un arreglo con los codigos que contiene la lista
char** lista_a_arreglo(lista_t* lista){

  lista_iter_t* lista_iter= lista_iter_crear(lista);

  if (!lista_iter) {
    return NULL;
  }

  size_t cantidad_codigos=lista_largo(lista);

  char** codigos=malloc(sizeof(void*)*cantidad_codigos);

  if (!codigos) {
    return NULL;
  }

  size_t i=0;
  char* actual;
  while(!lista_iter_al_final(lista_iter)){
    actual=lista_iter_ver_actual(lista_iter);
    codigos[i]=actual;
    lista_iter_avanzar(lista_iter);
    i++;
  }

  lista_iter_destruir(lista_iter);

  return codigos;

}




bool imprimir_en_orden(void* dato, void* extra){

  auxiliar_ver_tablero_t* auxiliar=extra;



  lista_t* lista_codigos=dato;
  size_t cantidad_codigos=lista_largo(lista_codigos);

  char** codigos=lista_a_arreglo(lista_codigos);


  if(!codigos){
    auxiliar->indicador=false;
    return false;
  }

  seleccion(codigos, cantidad_codigos);

  vuelo_t* actual;

  size_t inicio;
  int incremento;

  if(auxiliar->ascendente){
    inicio=0;
    incremento=1;
  }else{
    inicio=cantidad_codigos-1;
    incremento=-1;
  }

  size_t j=inicio;

  for (int i = 0; i < cantidad_codigos; i++) {

    if (!contador_aumentar(auxiliar->contador)) {
      free(codigos);
      return false;
    }

    actual=hash_obtener(auxiliar->hash, codigos[j]);
    printf("%s - %s\n", vuelo_fecha(actual), vuelo_codigo(actual));
    j+=incremento;
  }

  free(codigos);

  return true;

}



bool guardar_vuelos(void* dato, void* extra){

  lista_e_indicador_t* copia_extra=(lista_e_indicador_t*)extra;
  lista_t* auxiliar=lista_crear();

  if (!auxiliar) {
    copia_extra->indicador=false;
    return false;
  }


  char** vuelos=lista_a_arreglo(dato);

  if (!vuelos) {
    copia_extra->indicador=false;
    return false;
  }

  size_t cantidad_vuelos=lista_largo(dato);

  seleccion(vuelos, cantidad_vuelos);

  for (size_t i = 0; i < cantidad_vuelos; i++) {
    if (!lista_insertar_ultimo(auxiliar, vuelos[i])) {
      free(vuelos);
      copia_extra->indicador=false;
      return false;
    }
  }

  if (!lista_insertar_ultimo(copia_extra->lista, auxiliar)) {
    copia_extra->indicador=false;
    free(vuelos);
    return false;
  }

  free(vuelos);

  return true;

}




int obtener_entero(char* cadena){

  if (cadena[0]=='-') {
    return -atoi(cadena+1);
  }

  return atoi(cadena);

}



bool ver_tablero_es_valido(char** componentes_comando, size_t cantidad_de_elementos){

  if (cantidad_de_elementos!=5) {
    return false;
  }
  if ((!es_un_entero(componentes_comando[1]))||(obtener_entero(componentes_comando[1])<0)) {
    return false;
  }
  if ((!es_fecha_valida(componentes_comando[3]))||(!es_fecha_valida(componentes_comando[4]))) {
    return false;
  }
  if ((strcmp(componentes_comando[2], ORDEN_ASCENDENTE))&&(strcmp(componentes_comando[2], ORDEN_DESCENDENTE))) {
    return false;
  }
  if (strcmp(componentes_comando[3], componentes_comando[4])>0) {
    return false;
  }

  return true;

}



bool info_vuelo_es_valido(size_t cantidad_de_elementos){

  if (cantidad_de_elementos!=2) {
    return false;
  }
  return true;

}


bool agregar_archivo_es_valido(size_t cantidad_de_elementos){

  if (cantidad_de_elementos!=2) {
    return false;
  }
  return true;

}



bool priodidad_vuelos_es_valido(char** componentes_comando, size_t cantidad_de_elementos){

  if (cantidad_de_elementos!=2) {
    return false;
  }
  if ((!es_un_entero(componentes_comando[1]))||(obtener_entero(componentes_comando[1])<0)) {
    return false;
  }

  return true;

}



bool borrar_es_valido(char** componentes_comando, size_t cantidad_de_elementos){

  if (cantidad_de_elementos!=3) {
    return false;
  }
  if ((!es_fecha_valida(componentes_comando[1]))||(!es_fecha_valida(componentes_comando[2]))) {
    return false;
  }
  if (strcmp(componentes_comando[1], componentes_comando[2])>0) {
    return false;
  }

  return true;

}




void destruir_lista(void* lista){
  lista_destruir(lista, NULL);
}
