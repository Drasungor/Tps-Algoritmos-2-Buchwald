#include "operaciones.h"



int aplicar_operador_ternario(int primer_numero, int segundo_numero, int indicador){

    if (indicador==0) {
      return primer_numero;
    }

    return segundo_numero;

}


int _obtener_raiz(int n, int inicio , int fin){

  int medio=(inicio+fin)/2;

  if ((medio*medio<n)&&((medio+1)*(medio+1)>n)) {
    return medio;
  }
  if (medio*medio<n) {
    return _obtener_raiz(n, medio+1, fin);
  }
  if (medio*medio>n) {
    return _obtener_raiz(n, inicio, medio-1);
  }

  return medio;

}

int obtener_raiz(int n){

  return _obtener_raiz(n, 0, n);

}



int obtener_potencia(int base, int exponente){

  if (exponente==1) {
    return base;
  }

  if (exponente<0) {
    return 0;
  }

  if (exponente==0) {
    return 1;
  }

  int potencia_menor= obtener_potencia(base, exponente/2);

  if (exponente%2==0) {
    return potencia_menor*potencia_menor;
  }

  return base*potencia_menor*potencia_menor;

}




int obtener_logaritmo(int base, int argumento){

  if (argumento<base) {
    return 0;
  }

  return 1+obtener_logaritmo(base, argumento/base);

}
