#include<stdio.h>



size_t _obtener_raiz(size_t n,size_t inicio ,size_t fin){

  if (inicio==fin) {
    return inicio;
  }

  size_t medio=(inicio+fin)/2;


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


size_t obtener_raiz(size_t n){

  return _obtener_raiz(n, 0, n);

}


int main(int argc, char const *argv[]) {

  size_t n;

  scanf(" %u", &n);

  printf("%u\n", obtener_raiz(n));


  return 0;
}
