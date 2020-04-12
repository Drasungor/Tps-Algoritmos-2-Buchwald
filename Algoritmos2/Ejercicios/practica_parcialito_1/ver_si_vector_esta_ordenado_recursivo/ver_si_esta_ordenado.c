#include <stdbool.h>
#include <stdio.h>






bool _esta_ordenado(int vector[], size_t inicio, size_t fin){

  if (fin-inicio==0) {
    return true;
  }

  size_t medio= (fin+inicio)/2;

  if ((_esta_ordenado(vector,inicio,medio))&&(_esta_ordenado(vector,medio+1,fin))) {
    if (vector[medio]<vector[medio+1]) {
      return true;
    }
    return false;
  }

  return false;

}


bool esta_ordenado(int vector[], size_t tamanio){

  return _esta_ordenado(vector, 0, tamanio-1);

}


int main(int argc, char const *argv[]) {


  int vector1[5]={1,3,5,8,12};

  int vector2[6]={1,3,2,7,8,0};

  if (esta_ordenado(vector1, 5)) {
    printf("Vector1 esta ordenado\n");
  }else{
    printf("Vector21 no esta ordenado\n");
  }


  if (esta_ordenado(vector2, 6)) {
    printf("Vector2 esta ordenado\n");
  }else{
    printf("Vector2 no esta ordenado\n");
  }

  return 0;
}
