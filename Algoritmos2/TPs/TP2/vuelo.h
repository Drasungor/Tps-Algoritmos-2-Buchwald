#ifndef VUELO_H
#define VUELO_H

typedef struct vuelo vuelo_t;

//Devuelve un puntero a un vuelo, en caso de
//fallo devuelve NULL
vuelo_t* vuelo_crear(char* datos, char sep);

//Devuelve el numero del vuelo pasado
const char* vuelo_codigo(vuelo_t* vuelo);

//Devuelve la prioridad del vuelo
size_t vuelo_prioridad(vuelo_t* vuelo);

//Devuelve la fecha del vuelo en un vector, ordenado
//de la cifra más a menos significativa
const char* vuelo_fecha(vuelo_t* vuelo);

//Devuelve una copia de la cadena utilizada para
//inicializar la variable
const char** vuelo_obtener_informacion(vuelo_t* vuelo);

//Destruye el vuelo
void vuelo_destruir(vuelo_t* vuelo);


#endif
