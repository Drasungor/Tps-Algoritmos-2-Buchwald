#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include "strutil.h"
#include "lista.h"


#define PROCESO_REALIZADO_CON_EXITO 0
#define ERROR_CON_MEMORIA_DINAMICA -1
#define CANTIDAD_DE_PARAMETROS_ERRONEA -2
#define TIPO_DE_PARAMETRO_INCORRECTO -3
#define NO_SE_PUDO_ABRIR_EL_ARCHIVO -4
#define SE_ACABO_EL_ARCHIVO -5

#define ESTA_SUBCADENA 0
#define NO_ESTA_SUBCADENA 1

#define BASE_HASH 256
#define PRIMO_HASH 101


bool es_un_natural(char* cadena){

size_t largo_cadena= strlen(cadena);

  //ascii 0: 48
  //ascii 9: 57
  for (size_t i = 0; i < largo_cadena; i++) {
    if ((cadena[i]<48)||(cadena[i]>57)) {
      return false;
    }
  }

  return true;
}

//fuente: https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
int _hash(char* cadena, int valor_acumulado, int caracter_a_calcular){

  //cantidad de caracteres de la tabla de ascii
  int base=BASE_HASH;

  int primo=PRIMO_HASH;

  if (cadena[caracter_a_calcular]=='\0') {
    return valor_acumulado;
  }

  return _hash(cadena, (valor_acumulado*base+cadena[caracter_a_calcular])%primo, caracter_a_calcular+1);

}

int hash(char* cadena){

  return _hash(cadena, 0, 0);

}


//Indica si la subcadena se encuentra en la cadena
//Devuelve 0 si la subcadena se encuentra en la cadena
//y 1 si no se encuentra. Los valroes negativos son utilizados
//para reportar errores
int esta_subcadena(char* cadena, char* subcadena){

  size_t hash_subcadena=hash(subcadena);
  size_t largo_subcadena=strlen(subcadena);
  size_t largo_cadena= strlen(cadena);
  char* pedazo_de_cadena=NULL;

  for (size_t i = 0; i+largo_subcadena-1 < largo_cadena; i++) {

    pedazo_de_cadena=strndup(cadena+i, largo_subcadena);

    if (!pedazo_de_cadena) {
      return ERROR_CON_MEMORIA_DINAMICA;
    }

    if ((hash(pedazo_de_cadena)==hash_subcadena)&&(!strcmp(pedazo_de_cadena, subcadena))) {
      free(pedazo_de_cadena);
      return ESTA_SUBCADENA;
    }

    free(pedazo_de_cadena);
  }

  return NO_ESTA_SUBCADENA;

}


//Rellena la lista que contendra las lineas que se deben mostrar para un match
//de la cadena buscada. Se muestran las lineas previas que no están vacías
int obtener_bloque(FILE* archivo, lista_t* bloque_de_impresion, char* cadena_buscada, int cantidad_lineas_adicionales){

  char* linea=NULL;

  size_t tamanio=0;

  if (getline(&linea, &tamanio, archivo)==-1) {
    free(linea);
    return SE_ACABO_EL_ARCHIVO;
  }

  while (esta_subcadena(linea, cadena_buscada)==NO_ESTA_SUBCADENA) {

    if (!lista_insertar_ultimo(bloque_de_impresion, linea)) {
      return ERROR_CON_MEMORIA_DINAMICA;
    }

    if (lista_largo(bloque_de_impresion)>cantidad_lineas_adicionales) {
      free(lista_borrar_primero(bloque_de_impresion));
    }

    linea=NULL;
    tamanio=0;

    if (getline(&linea, &tamanio, archivo)==-1) {
      free(linea);
      return SE_ACABO_EL_ARCHIVO;
    }

  }

  if (!lista_insertar_ultimo(bloque_de_impresion, linea)) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }


  return PROCESO_REALIZADO_CON_EXITO;

}



void imprimir_bloque(lista_t* bloque_de_impresion){

  char* linea_a_imprimir;
  size_t largo_lista=lista_largo(bloque_de_impresion);

  for (size_t i = 0; i < largo_lista; i++) {
    linea_a_imprimir=(char*)lista_borrar_primero(bloque_de_impresion);
    printf("%s", linea_a_imprimir);
    free(linea_a_imprimir);
  }

}



int main(int argc, char const *argv[]) {


  if (argc<3) {
    fprintf(stderr, "Cantidad de parametros erronea\n");
    return CANTIDAD_DE_PARAMETROS_ERRONEA;
  }

  if (!es_un_natural((char*)argv[2])) {
    fprintf(stderr, "Tipo de parametro incorrecto\n");
    return TIPO_DE_PARAMETRO_INCORRECTO;
  }

  FILE* archivo_de_entrada=stdin;

  if (argc==4) {
    archivo_de_entrada = fopen (argv[3],"r");

    if (!archivo_de_entrada){
      fprintf(stderr, "No se pudo leer el archivo indicado\n");
      return NO_SE_PUDO_ABRIR_EL_ARCHIVO;
    }

  }


  lista_t* bloque_de_impresion=lista_crear();

  if (!bloque_de_impresion) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  int lineas_adicionales=atoi(argv[2]);

  int estado_de_ejecucion=obtener_bloque(archivo_de_entrada, bloque_de_impresion, (char*)argv[1], lineas_adicionales);


  while (estado_de_ejecucion==PROCESO_REALIZADO_CON_EXITO) {
      imprimir_bloque(bloque_de_impresion);
      estado_de_ejecucion=obtener_bloque(archivo_de_entrada, bloque_de_impresion, (char*)argv[1], lineas_adicionales);
  }

  lista_destruir(bloque_de_impresion, free);

  if (archivo_de_entrada!=stdout) {
    fclose(archivo_de_entrada);
  }

  if ((estado_de_ejecucion!=PROCESO_REALIZADO_CON_EXITO)&&(estado_de_ejecucion!=SE_ACABO_EL_ARCHIVO)) {
    return estado_de_ejecucion;
  }

  return PROCESO_REALIZADO_CON_EXITO;

}
