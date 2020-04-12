from grafo import *
from operaciones_grafo import *
import csv
from constant import *

#Devuelve un string que contiene la subcadena que va desde indice_inicial
#hasta que sea encontrado el caracter de corte o termine la cadema
def obtener_subcadena(cadena, indice_inicial, caracter_de_corte=None):

    subcadena=""
    if indice_inicial==None or indice_inicial>=len(cadena):
        return None, None

    for i in range(indice_inicial, len(cadena)):
        if cadena[i]==caracter_de_corte:
            return subcadena, i+1
        subcadena+=cadena[i]

    return subcadena, i+1



#Agregar en el archivo líneas con el formato para introducir un punto
#en un archivo kml
#informacion_aeropuerto contiene una nupla (ciudad, latitud, longitud)
def agregar_punto_kml(archivo_de_salida, aeropuerto, informacion_aeropuerto):

    punto="""\t\t<Placemark>
        <name>""" + aeropuerto + """</name>
        <Point>
            <coordinates>""" + informacion_aeropuerto[1] + "," + informacion_aeropuerto[2] + """</coordinates>
        </Point>
    </Placemark>\n\n"""

    archivo_de_salida.write(punto)

#Agregar en el archivo líneas con el formato para introducir un camino
#en un archivo kml
#informacion_aeropuerto contiene una nupla (ciudad, latitud, longitud)
def agregar_camino_kml(archivo_de_salida, informacion_aeropuerto1, informacion_aeropuerto2):

    linea="""\t\t<Placemark>
        <LineString>
            <coordinates>""" + informacion_aeropuerto1[1] + "," + informacion_aeropuerto1[2] + " " + informacion_aeropuerto2[1] + "," + informacion_aeropuerto2[2] + """</coordinates>
        </LineString>
    </Placemark>\n\n"""

    archivo_de_salida.write(linea)


#Devuelve una lista con el camino con la menor cantidad de escalas del
#aeropuerto de salida a los aeropuertos de la ciudad de destino
def mejor_camino_a_ciudad(grafo, aeropuerto_salida, aeropuertos_destino):
    padres=recorrido_bfs(grafo, aeropuerto_salida)

    caminos=[]

    for aeropuerto_llegada in aeropuertos_destino:
        posible_camino=reconstruir_camino(padres, aeropuerto_llegada)

        if posible_camino==None:
            return CAMINO_IMPOSIBLE

        caminos.append(posible_camino)


    if len(caminos)==0:
        return CAMINO_IMPOSIBLE


    mejor_camino=caminos[0]
    escalas_mejor_camino=len(mejor_camino)

    for c in caminos:
        escalas_aux=len(c)
        if escalas_aux<escalas_mejor_camino:
            escalas_mejor_camino=escalas_aux
            mejor_camino=c

    return mejor_camino


#Imprime los elementos de la lista separados con
#el separador
def imprimir_lista_separada(lista, separador):

    largo_lista=len(lista)

    for i in range(largo_lista):
        if i!=largo_lista-1:
            print(lista[i], end=separador)
        else:
            print(lista[i])


#Recibe listas con los aeropuertos presentes en las ciudades de origen y de destino
#Devuelve una lista que representa el camino minimo desde la ciudad origen hasta
#la destino
def camino_minimo_entre_ciudades(grafo, aeropuertos_origen, aeropuertos_destino):

    peso_minimo=math.inf
    camino_minimo_aux=None
    camino_minimo=None

    for salida in aeropuertos_origen:
        for llegada in aeropuertos_destino:
            camino_minimo_aux, peso_aux=dijkstra(grafo, salida, llegada)
            if camino_minimo_aux==None:
                continue
            if peso_aux<peso_minimo:
                camino_minimo=camino_minimo_aux

    return camino_minimo




#Recibe una lista con los aeropuertos de una ciudad y su información
#y devuelve una lista que tiene solo los aeropuertos
def obtener_aeropuertos(informacion_aeropuertos):
    aeropuertos=[]
    for aeropuerto in informacion_aeropuertos:
        aeropuertos.append(aeropuerto[0])

    return aeropuertos



def camino_escalas_es_valido(ciudades, origen, destino):
    if origen==None or destino==None:
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    if origen not in ciudades or destino not in ciudades:
        return CIUDAD_INEXISTENTE

    return COMANDO_VALIDO


def camino_mas_es_valido(ciudades, modo, origen, destino):
    if modo==None or origen==None or destino==None:
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    if origen not in ciudades or destino not in ciudades:
        return CIUDAD_INEXISTENTE

    return COMANDO_VALIDO


def nueva_aerolinea_es_valido(ruta_archivo):
    if ruta_archivo==None:
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    return COMANDO_VALIDO


def centralidad_es_valido(cantidad):

    if cantidad==None:
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    try:
        cantidad=int(cantidad)
    except ValueError:
        return PARAMETROS_INCORRECTOS

    return COMANDO_VALIDO


def exportar_kml_es_valido(ruta_archivo):

    if ruta_archivo==None:
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    return COMANDO_VALIDO


def itinerario_cultural_es_valido(ruta_archivo):

    if ruta_archivo==None:
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    return COMANDO_VALIDO


def vacaciones_es_valido(ciudades, origen, cantidad):

    if origen==None or cantidad==None:
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    if origen not in ciudades:
        return CIUDAD_INEXISTENTE

    try:
        cantidad=int(cantidad)
    except ValueError:
        return PARAMETROS_INCORRECTOS

    return COMANDO_VALIDO
