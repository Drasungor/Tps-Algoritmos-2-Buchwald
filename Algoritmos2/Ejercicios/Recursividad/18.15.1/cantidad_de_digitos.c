#include <stdio.h>


int decir_cantidad_de_digitos(int numero_elegido){


  char[] numero= itoa(numero_elegido);

  if (/* comparar con \0 */) {
    return 0;
  }


  return

}



int main(int argc, char const *argv[]) {

int numero_recibido;


  do {

    printf("Ingrese un número positivo para saber la cantidad de dígitos que posee:");
    scanf("%d ", &numero_recibido);

    if (numero_recibido<0) {

      printf("Ha ingresado un número negativo, intente de nuevo\n");

    }

  } while(numero_recibido<0);



  return 0;
}
