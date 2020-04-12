//Entrega 2 TP0

//Nombre y apellido: Agustín Cambiano
//Padrón: 102291


#include "tp0.h"

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */

void swap (int* x, int* y) {

	int auxiliar= *x;

	*x=*y;
	*y=auxiliar;

}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */

int maximo(int vector[], int n) {

	int mayor_elemento=0;

	if (n==0) {
		return -1;
	}

	for (int i = 1; i < n; i++) {
			if (vector[i]>vector[mayor_elemento]) {
				mayor_elemento=i;
			}
	}

	return mayor_elemento;

}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */

int comparar(int vector1[], int n1, int vector2[], int n2) {

	int i=0;


	while ((i<n1)&&(i<n2)) {
			if (vector1[i]<vector2[i]) {
					return -1;
			}
			if (vector1[i]>vector2[i]) {
				return 1;
			}
			i++;
	}

	if (n1<n2) {
		return -1;
	}else if (n1>n2) {
		return 1;
	}

	return 0;

}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */

void seleccion(int vector[], int n) {

	int maximo_elemento=0;

	for (int i = 0; i < n; i++) {
		maximo_elemento=maximo(vector, n-i);
		swap(&vector[n-1-i],&vector[maximo_elemento]);
	}

}
