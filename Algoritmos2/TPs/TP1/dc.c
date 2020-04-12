#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include "pila.h"
#include "strutil.h"
#include "operaciones.h"

#define MENSAJE_DE_ERROR "ERROR"

#define SUMA "+"
#define RESTA "-"
#define MULTIPLICACION "*"
#define DIVISION "/"
#define LOGARITMO "log"
#define POTENCIA "^"
#define RAIZ_CUADRADA "sqrt"
#define OPERADOR_TERNARIO "?"

#define SEPARADOR_ENTRADA_ESTANDAR ' '

//La cantidad de elementos que se necesitará para
//realizar la operación que más argumentos necesita
#define MAXIMO_ARGUMENTOS_POSIBLES 3

#define PROCESO_REALIZADO_CON_EXITO 0
#define ERROR_CON_MEMORIA_DINAMICA -1
#define ERROR_DE_OPERACION -2
#define OPERACION_INEXISTENTE -3
#define SE_ACABO_EL_ARCHIVO -4
#define NO_HAY_MAS_OPERACIONES -5


//destruye todos los elementos almacenados en la pila
void destruir_pila_dinamica(pila_t* pila){

  while (!pila_esta_vacia(pila)) {
    free(pila_desapilar(pila));
  }

  pila_destruir(pila);

}



//cambiar para que el default sea false y poner condicionales
//para que sea true
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

//Devuelve la version entera del string pasado,
//no chequea errores
int obtener_entero(char* cadena){

  if (cadena[0]=='-') {
    return -atoi(cadena+1);
  }

  return atoi(cadena);

}




//Apila los elementos necesarios para realizar una operacion y devuelve la posición
//del arreglo de cadenas en el que se encuentra el ultimo elemento apilado
int buscar_operacion(pila_t* pila, char** elementos_operaciones, int comienzo){

  int* numero;
  char* operacion;

  int i=comienzo;

  if (!elementos_operaciones[i]) {
    return NO_HAY_MAS_OPERACIONES;
  }

  bool es_entero;

  if (elementos_operaciones[i][0]=='\0') {
    es_entero=true;
  }else{
    es_entero=es_un_entero(elementos_operaciones[i]);
  }


  while (es_entero) {

    if (elementos_operaciones[i][0]!='\0') {

      numero=malloc(sizeof(int));

      if (!numero) {
        return ERROR_CON_MEMORIA_DINAMICA;
      }

      *numero=obtener_entero(elementos_operaciones[i]);

      if (!pila_apilar(pila, numero)) {
        free(numero);
        return ERROR_CON_MEMORIA_DINAMICA;
      }

      i++;

    }

    if (!elementos_operaciones[i]) {
      return OPERACION_INEXISTENTE;
    }

    if (elementos_operaciones[i][0]=='\0') {
      i++;
    }

    if (!elementos_operaciones[i]) {
      if (elementos_operaciones[i-1][0]=='\0') {
        return NO_HAY_MAS_OPERACIONES;
      }
      return OPERACION_INEXISTENTE;
    }

    if (elementos_operaciones[i][0]!='\0') {
      es_entero=es_un_entero(elementos_operaciones[i]);
    }

  }

  operacion=elementos_operaciones[i];

  if (!pila_apilar(pila, operacion)) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  return i;

}




//Destruye todos los valores almacenados en el vector hasta el elemento
//de indice n-1
void vaciar_vector(void* vector[MAXIMO_ARGUMENTOS_POSIBLES], size_t n){

  for (size_t i = 0; i < n; i++) {
    free(vector[i]);
  }

}


//introduce en el vector de punteros n elementos de la pila, si esta no
//tiene la cantiadd de elementos solicitada es destruida y la función devuelve
//false
bool obtener_argumentos_a_utilizar(int argumentos[MAXIMO_ARGUMENTOS_POSIBLES], pila_t* pila, size_t n){

  void* auxiliar[MAXIMO_ARGUMENTOS_POSIBLES];

  bool hay_argumentos_suficientes=true;
  size_t i;

  for (i = 0; i < n; i++) {
    if (pila_esta_vacia(pila)) {
      hay_argumentos_suficientes= false;
      break;
    }

    auxiliar[i]=pila_desapilar(pila);

  }

  if (!hay_argumentos_suficientes) {
    if (i!=0) {
      vaciar_vector(auxiliar, i);
    }
    return false;
  }

  for (size_t j = 0; j < n; j++) {
    argumentos[j]=*(int*)auxiliar[j];
  }

  vaciar_vector(auxiliar, n);

  return true;

}


//Indica si se puede realizar una operación, en caso de que se
//pueda devuelve el resultado de esta almacenandolo en la pila
//pasada
//Si no se tienen los argumentos suficientes como para realizar
//la operacion devuelve false y se pierden los elementos sacados
//de la pila
int realizar_operacion(pila_t* pila){

  //este sera el resultado de toda la operacion,
  //luego sera apilado en la pila pasada, que sera la auxiliar
  int* resultado=malloc(sizeof(int));

  if (!resultado) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  int argumentos_a_utilizar[MAXIMO_ARGUMENTOS_POSIBLES];
  int estado_de_ejecucion=0;
  char* operacion= pila_desapilar(pila);


  if (!strcmp(operacion, SUMA)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,2)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else{
      *resultado= argumentos_a_utilizar[0] + argumentos_a_utilizar[1];
    }

  }else if (!strcmp(operacion, RESTA)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,2)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else{
      *resultado= argumentos_a_utilizar[0] - argumentos_a_utilizar[1];
    }

  }else if (!strcmp(operacion, MULTIPLICACION)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,2)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else{
      *resultado= argumentos_a_utilizar[0] * argumentos_a_utilizar[1];
    }

  }else if (!strcmp(operacion, DIVISION)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,2)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else if (argumentos_a_utilizar[1]==0) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else{
      *resultado= argumentos_a_utilizar[0] / argumentos_a_utilizar[1];
    }

  }else if (!strcmp(operacion, LOGARITMO)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,2)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else if ((argumentos_a_utilizar[1]<2)||(argumentos_a_utilizar[0]<1)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else{
      *resultado= obtener_logaritmo(argumentos_a_utilizar[1], argumentos_a_utilizar[0]);
    }

  }else if (!strcmp(operacion, POTENCIA)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,2)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else if(argumentos_a_utilizar[1]<0){
      estado_de_ejecucion=ERROR_DE_OPERACION;
    }else{
      *resultado= obtener_potencia(argumentos_a_utilizar[0], argumentos_a_utilizar[1]);
    }

  }else if (!strcmp(operacion, RAIZ_CUADRADA)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,1)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else if (argumentos_a_utilizar[0]<0) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else{
      *resultado= obtener_raiz(argumentos_a_utilizar[0]);
    }

  }else if (!strcmp(operacion, OPERADOR_TERNARIO)) {
    if (!obtener_argumentos_a_utilizar(argumentos_a_utilizar, pila,3)) {
      estado_de_ejecucion= ERROR_DE_OPERACION;
    }else{
      *resultado= aplicar_operador_ternario(argumentos_a_utilizar[2], argumentos_a_utilizar[1], argumentos_a_utilizar[0]);
    }

  }else{
    estado_de_ejecucion= OPERACION_INEXISTENTE;
  }

  if (estado_de_ejecucion!=PROCESO_REALIZADO_CON_EXITO) {
    free(resultado);
    return estado_de_ejecucion;
  }

  if (!pila_apilar(pila, resultado)) {
    free(resultado);
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  return estado_de_ejecucion;

}



int realizar_operaciones(char** elementos_operaciones, int* resultado){

  pila_t* pila_de_ejecucion=pila_crear();

  if (!pila_de_ejecucion) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }

  int estado_de_ejecucion=PROCESO_REALIZADO_CON_EXITO;

  int ultima_cadena_apilada=-1;

  ultima_cadena_apilada=buscar_operacion(pila_de_ejecucion, elementos_operaciones, ultima_cadena_apilada+1);

  while (ultima_cadena_apilada!=NO_HAY_MAS_OPERACIONES) {

    if (ultima_cadena_apilada==OPERACION_INEXISTENTE) {
      destruir_pila_dinamica(pila_de_ejecucion);
      return OPERACION_INEXISTENTE;
    }


    estado_de_ejecucion=realizar_operacion(pila_de_ejecucion);

    if (estado_de_ejecucion!=PROCESO_REALIZADO_CON_EXITO) {
      destruir_pila_dinamica(pila_de_ejecucion);
      return estado_de_ejecucion;
    }

    ultima_cadena_apilada=buscar_operacion(pila_de_ejecucion, elementos_operaciones, ultima_cadena_apilada+1);

  }

  int* presultado=pila_desapilar(pila_de_ejecucion);

  *resultado=*presultado;

  free(presultado);

  if (!pila_esta_vacia(pila_de_ejecucion)) {
    destruir_pila_dinamica(pila_de_ejecucion);
    return ERROR_DE_OPERACION;
  }

  destruir_pila_dinamica(pila_de_ejecucion);

  return estado_de_ejecucion;

}




int procesar_linea(int* resultado){

  char* linea=NULL;
  size_t tamanio=0;
  size_t largo=0;

  largo=getline(&linea, &tamanio, stdin);

  if (largo==-1) {
    free(linea);
    return SE_ACABO_EL_ARCHIVO;
  }

  if (linea[0]=='\n') {
    free(linea);
    return OPERACION_INEXISTENTE;
  }

  linea[largo-1]='\0';


  if (!linea) {
    return ERROR_CON_MEMORIA_DINAMICA;
  }


  char** elementos_operaciones=split(linea, SEPARADOR_ENTRADA_ESTANDAR);

  if (!elementos_operaciones) {
   free(linea);
   return ERROR_CON_MEMORIA_DINAMICA;
  }

  int estado_de_ejecucion= realizar_operaciones(elementos_operaciones, resultado);


  free(linea);
  linea=NULL;
  free_strv(elementos_operaciones);

  return estado_de_ejecucion;

}




int main(int argc, char const *argv[]) {

  int resultado;

 int estado_de_ejecucion= PROCESO_REALIZADO_CON_EXITO;

  while (estado_de_ejecucion!=SE_ACABO_EL_ARCHIVO) {
    estado_de_ejecucion=procesar_linea(&resultado);
    if (estado_de_ejecucion==PROCESO_REALIZADO_CON_EXITO) {
      printf("%d\n", resultado);
    }else if(estado_de_ejecucion!=SE_ACABO_EL_ARCHIVO){
      printf("%s\n", MENSAJE_DE_ERROR);
    }
  }

  return 0;
}
