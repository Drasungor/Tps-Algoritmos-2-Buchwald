#include"strutil.h"
#include<string.h>
#include<stdlib.h>


//devuelve la cantidad de cadenas que almacenará el vector
//split
size_t ver_cantidad_de_cadenas(const char* str, char sep){

  if (sep=='\0') {
    return 1;
  }

  size_t cantidad_de_cadenas=0;
  size_t largo_cadena=strlen(str);

  for (size_t i = 0; i < largo_cadena; i++) {
    if (str[i]==sep) {
      cantidad_de_cadenas++;
    }
  }

  return cantidad_de_cadenas+1;

}


//Devuelve la cantidad de elementos que almacenará la cadena unión
//incluyendo el \0

//cambiar nombre a obtener_largo_union
size_t obtener_largo_total(char** cadena_de_cadenas){

  size_t largo=0;
  size_t i=0;
  size_t cantidad_separadores=0;

  while (cadena_de_cadenas[i]!=NULL) {
    largo+= strlen(cadena_de_cadenas[i]);
    i++;
  }

  cantidad_separadores=i-1;

  if (cantidad_separadores>0) {
    largo+=cantidad_separadores;
  }

  return largo+1;

}




//Devuelve un puntero a la cadena dinámica de caracteres que va
//de inicio al anterior a fin
//Si falla la asignación de memoria devuelve NULL
char* generar_subcadena(const char* str, size_t inicio, size_t fin){

  char* subcadena=malloc(sizeof(char)*(fin-inicio+1));

  if (!subcadena) {
    return NULL;
  }

  for (size_t i = inicio; i < fin; i++) {
    subcadena[i-inicio]=str[i];
  }

  subcadena[fin-inicio]='\0';

  return subcadena;

}


/*
 * Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
 * de ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica del
 * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
 * malloc(), o si ‘sep’ es '\0'.
 */
char** split(const char* str, char sep){



  size_t largo=ver_cantidad_de_cadenas(str,sep)+1;

  char** arreglo_de_cadenas= malloc(sizeof(char*)*largo);

  if (!arreglo_de_cadenas) {
    return NULL;
  }

  arreglo_de_cadenas[0]=NULL;

  size_t inicio_subcadena=0;
  size_t numero_de_subcadena=0;
  char* subcadena="";

  size_t largo_cadena_recibida=strlen(str)+1;

  for (size_t i = 0; i < largo_cadena_recibida; i++) {

    if (str[i]==sep) {
      subcadena=generar_subcadena(str, inicio_subcadena, i);
      if (!subcadena) {
        free_strv(arreglo_de_cadenas);
        return NULL;
      }
      arreglo_de_cadenas[numero_de_subcadena]=subcadena;
      arreglo_de_cadenas[numero_de_subcadena+1]=NULL;
      numero_de_subcadena++;
      inicio_subcadena=i+1;
    }

  }

  if (sep!='\0') {

    if (inicio_subcadena>=largo_cadena_recibida) {
      subcadena=malloc(sizeof(char));
      *subcadena='\0';
      if (!subcadena) {
        free_strv(arreglo_de_cadenas);
        return NULL;
      }
    }else{
      subcadena=generar_subcadena(str, inicio_subcadena, largo_cadena_recibida);
      if (!subcadena) {
        free_strv(arreglo_de_cadenas);
        return NULL;
      }
    }

    arreglo_de_cadenas[numero_de_subcadena]=subcadena;
    arreglo_de_cadenas[numero_de_subcadena+1]=NULL;

  }


  return arreglo_de_cadenas;

}


//Agrega al final de la cadena_1 el contenido de la cadena_a_adjuntar, no hace
//chequeo de errores (invalid writes, etc)
//Devuelve el largo final de la cadena luego de la operacion
size_t adjuntar_cadena(char* cadena_1, size_t largo_cadena_1, char* cadena_a_adjuntar){

  size_t i=0;
  size_t largo_final=largo_cadena_1;

  while (cadena_a_adjuntar[i]!='\0') {
    cadena_1[largo_cadena_1+i]=cadena_a_adjuntar[i];
    largo_final++;
    i++;
  }

  cadena_1[largo_final]='\0';

  return largo_final;

}




/*
 * Devuelve una cadena, allocada dinámicamente, resultado de unir todas las
 * cadenas del arreglo terminado en NULL ‘strv’.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica de la
 * cadena devuelta. La función devuelve NULL si no se pudo allocar memoria.
 */
char* join(char** strv, char sep){

  if (sep=='\0') {
    return NULL;
  }

  size_t largo_total_union;
  char* cadena_union;

  if (!strv[0]) {
    cadena_union=malloc(sizeof(char));
    if (!cadena_union) {
      return NULL;
    }
    *cadena_union='\0';
    return cadena_union;
  }else{
    largo_total_union=obtener_largo_total(strv);
    cadena_union=malloc(sizeof(char)*largo_total_union);
  }


  if (!cadena_union) {
    return NULL;
  }

  char separador[2]={sep, '\0'};

  *cadena_union='\0';

  size_t largo_actual_union=0;

  size_t i=0;


  while (strv[i]!=NULL) {
    largo_actual_union=adjuntar_cadena(cadena_union, largo_actual_union, strv[i]);
    if (strv[i+1]!=NULL) {
      largo_actual_union=adjuntar_cadena(cadena_union, largo_actual_union, separador);
    }
    i++;
  }


  return cadena_union;

}

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char* strv[]){

  size_t i=0;

  while (strv[i]!=NULL) {
    free(strv[i]);
    i++;
  }

  free(strv);


}
