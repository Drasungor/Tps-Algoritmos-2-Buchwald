#ifndef _OPERACIONES_H
#define  _OPERACIONES_H

#include <stddef.h>

//Devuelve la suma de los argumentos pasados
int obtener_suma(int argumento1, int argumento2);

//Devuelve la resta de los argumentos pasados
int obtener_resta(int argumento1, int argumento2);

//Devuelve el producto de los argumentos pasados
int obtener_producto(int argumento1, int argumento2);

//Devuelve la division de los argumentos pasados
int obtener_division(int argumento1, int argumento2);

//Si argumento3 es 0 devuelve el primer argumento, sino devuelve el segundo
int aplicar_operador_ternario(int argumento1, int argumento2, int argumento3);

//Devuelve la raíz cuadrada del entero pasado
int obtener_raiz(int n);

//Devuelve la base elevada al exponente
int obtener_potencia(int base, int exponente);

//Devuelve el logaritmo del argumento en base de la base pasada
int obtener_logaritmo(int base, int argumento);

#endif
