#!/usr/bin/python3

from grafo import *
from operaciones_grafo import *
import csv
from constant import *
import sys
from auxiliares import *



def listar_operaciones():

    operaciones = [CAMINO_MAS, CAMINO_ESCALAS, NUEVA_AEROLINEA, EXPORTAR_KML, ITINERARIO_CULTURAL, VACACIONES, CENTRALIDAD]

    for elemento in operaciones:
        print (elemento)



def nueva_aerolinea(grafo_por_precio, vuelos, archivo_salida):

    with open(archivo_salida, "w") as ruta_aerolinea:
        writer=csv.writer(ruta_aerolinea)
        aristas= mst(grafo_por_precio)

        for vuelo in aristas:
            pesos_vuelo=(vuelos[vuelo[0]][vuelo[1]][0],vuelos[vuelo[0]][vuelo[1]][1],vuelos[vuelo[0]][vuelo[1]][2])
            writer.writerow(vuelo+pesos_vuelo)

    print(OK)
    return OPERACION_EXITOSA


def centralidad(grafo_por_vuelos, cantidad):

    centralidad_vertices=betweeness_centrality(grafo_por_vuelos)

    centralidades_ordenadas=[]

    for aeropuerto in centralidad_vertices:
        centralidades_ordenadas.append((centralidad_vertices[aeropuerto], aeropuerto))

    centralidades_ordenadas.sort(reverse=True)

    if len(centralidad_vertices)<cantidad:
        cantidad=len(centralidad_vertices)


    for i in range(cantidad):
        if i != cantidad-1:
            print(centralidades_ordenadas[i][1], end=", ")
        else:
            print(centralidades_ordenadas[i][1])



def vacaciones(grafo, aeropuertos_origen, n):

    recorrido=ciclo_de_largo_n(grafo, aeropuertos_origen, n)
    if recorrido!=None:
        imprimir_lista_separada(recorrido, SEPARADOR_AEROPUERTOS)
        return recorrido

    print(RECORRIDO_INEXISTENTE)
    return CAMINO_IMPOSIBLE



def itinerario_cultural(aeropuertos_precio, ruta_archivo, ciudades):

    grafo_ciudades=Grafo()
    grado={}

    with open(ruta_archivo, "r") as itinerario:
        r_itinerario=csv.reader(itinerario)
        a_visitar=next(r_itinerario)

        for ciudad in a_visitar:
            grafo_ciudades.agregar_vertice(ciudad)
            grado[ciudad]=0

        for restricciones in r_itinerario:
            grafo_ciudades.agregar_arista(restricciones[0], restricciones[1], 0)
            grado[restricciones[1]]+=1

    orden_de_visita=orden_topologico(grafo_ciudades, grado)

    if orden_de_visita==None:
        return CAMINO_IMPOSIBLE

    caminos=[]

    cantidad_ciudades=len(a_visitar)


    for ciudad in orden_de_visita:
        if ciudad not in ciudades:
            return CIUDAD_INEXISTENTE

    recorrido_parcial=camino_minimo_entre_ciudades(aeropuertos_precio, obtener_aeropuertos(ciudades[orden_de_visita[0]]), obtener_aeropuertos(ciudades[orden_de_visita[1]]))

    if recorrido_parcial==CAMINO_IMPOSIBLE:
        return CAMINO_IMPOSIBLE

    caminos.append(recorrido_parcial)

    for i in range(2, cantidad_ciudades):
        inicio=[recorrido_parcial[-1]]
        recorrido_parcial=camino_minimo_entre_ciudades(aeropuertos_precio, inicio, obtener_aeropuertos(ciudades[orden_de_visita[i]]))

        if recorrido_parcial==CAMINO_IMPOSIBLE:
            return CAMINO_IMPOSIBLE

        caminos.append(recorrido_parcial)

    imprimir_lista_separada(orden_de_visita, ", ")

    for camino in caminos:
        imprimir_lista_separada(camino, SEPARADOR_AEROPUERTOS)

    return OPERACION_EXITOSA

def exportar_kml(ruta_archivo, posiciones_aeropuertos, ultimo_camino):

    if isinstance(ultimo_camino, list):
        with open(ruta_archivo, "w") as kml:
            kml.write(ENCABEZADO_KML)

            for aeropuerto in ultimo_camino:
                agregar_punto_kml(kml, aeropuerto, posiciones_aeropuertos[aeropuerto])

            for i in range(1, len(ultimo_camino)):
                agregar_camino_kml(kml, posiciones_aeropuertos[ultimo_camino[i-1]], posiciones_aeropuertos[ultimo_camino[i]])

            kml.write(FIN_KML)

        print(OK)

    else:
        print(ERROR)



def camino_escalas(grafo, aeropuertos_origen, aeropuertos_destino):

    padres=[]
    cantidad_escalas = math.inf
    mejor_camino=[]


    for aeropuerto_salida in aeropuertos_origen:
        mejor_camino_actual=mejor_camino_a_ciudad(grafo, aeropuerto_salida, aeropuertos_destino)
        cantidad_escalas_aux=len(mejor_camino_actual)
        if cantidad_escalas_aux<cantidad_escalas:
            cantidad_escalas=cantidad_escalas_aux
            mejor_camino=mejor_camino_actual

    imprimir_lista_separada(mejor_camino, SEPARADOR_AEROPUERTOS)

    return mejor_camino



#Imprime el camino mínimo a seguir en el grafo recibido para ir de
#la ciudad origen a la destino en el grafo, recibe listas con los aeropuertos
#de esas ciudades
def camino_mas(grafo, aeropuertos_origen, aeropuertos_destino):

    camino_minimo=camino_minimo_entre_ciudades(grafo, aeropuertos_origen, aeropuertos_destino)

    if camino_minimo==None:
        return CAMINO_IMPOSIBLE

    imprimir_lista_separada(camino_minimo, SEPARADOR_AEROPUERTOS)

    return camino_minimo






def procesar_comando(linea, ciudades, posiciones_aeropuertos, grafos_aeropuertos, vuelos, retorno_previo):

    comando,siguiente_indice=obtener_subcadena(linea, 0, " ")

    if comando==LISTAR_OPERACIONES:
        listar_operaciones()

    elif comando==CAMINO_ESCALAS:

        origen, siguiente_indice=obtener_subcadena(linea, siguiente_indice, SEPARADOR_CIUDADES)
        destino, siguiente_indice=obtener_subcadena(linea, siguiente_indice)

        es_valido=camino_escalas_es_valido(ciudades, origen, destino)

        if es_valido!=COMANDO_VALIDO:
            return es_valido

        return camino_escalas(grafos_aeropuertos[0], obtener_aeropuertos(ciudades[origen]), obtener_aeropuertos(ciudades[destino]))

    elif comando==CAMINO_MAS:
        modo, siguiente_indice=obtener_subcadena(linea, siguiente_indice, " ")
        origen, siguiente_indice=obtener_subcadena(linea, siguiente_indice, SEPARADOR_CIUDADES)
        destino, siguiente_indice=obtener_subcadena(linea, siguiente_indice)

        es_valido=camino_mas_es_valido(ciudades, modo, origen, destino)

        if es_valido!=COMANDO_VALIDO:
            return es_valido

        if modo==BARATO:
            return camino_mas(grafos_aeropuertos[1], obtener_aeropuertos(ciudades[origen]), obtener_aeropuertos(ciudades[destino]))
        elif modo==RAPIDO:
            return camino_mas(grafos_aeropuertos[0], obtener_aeropuertos(ciudades[origen]), obtener_aeropuertos(ciudades[destino]))

    elif comando==NUEVA_AEROLINEA:

        ruta_archivo, siguiente_indice=obtener_subcadena(linea, siguiente_indice)

        es_valido=nueva_aerolinea_es_valido(ruta_archivo)

        if es_valido!=COMANDO_VALIDO:
            return es_valido

        return nueva_aerolinea(grafos_aeropuertos[1], vuelos, ruta_archivo)

    elif comando==CENTRALIDAD:

        cantidad, siguiente_indice=obtener_subcadena(linea, siguiente_indice)

        es_valido=centralidad_es_valido(cantidad)

        if es_valido!=COMANDO_VALIDO:
            return es_valido

        centralidad(grafos_aeropuertos[2], int(cantidad))

        return OPERACION_EXITOSA

    elif comando==EXPORTAR_KML:

        ruta_archivo, siguiente_indice=obtener_subcadena(linea, siguiente_indice)

        es_valido=exportar_kml_es_valido(ruta_archivo)

        if es_valido!=COMANDO_VALIDO:
            return es_valido

        exportar_kml(ruta_archivo, posiciones_aeropuertos, retorno_previo)
        return OPERACION_EXITOSA

    elif comando==ITINERARIO_CULTURAL:

        ruta_archivo, siguiente_indice=obtener_subcadena(linea, siguiente_indice)

        es_valido=itinerario_cultural_es_valido(ruta_archivo)

        if es_valido!=COMANDO_VALIDO:
            return es_valido

        return itinerario_cultural(grafos_aeropuertos[0], ruta_archivo, ciudades)

    elif comando==VACACIONES:
        origen, siguiente_indice=obtener_subcadena(linea, siguiente_indice, ",")
        cantidad, siguiente_indice=obtener_subcadena(linea, siguiente_indice)


        es_valido=vacaciones_es_valido(ciudades, origen, cantidad)

        if es_valido!=COMANDO_VALIDO:
            return es_valido

        return vacaciones(grafos_aeropuertos[1], obtener_aeropuertos(ciudades[origen]), int(cantidad))

    else:
        return COMANDO_INEXISTENTE

    return OPERACION_EXITOSA



#----------PROGRAMA PRINCIPAL-------------------

def fly_combi():

    ciudades={}
    posiciones_aeropuertos={}
    aeropuertos_precio=Grafo()
    aeropuertos_tiempo=Grafo()
    aeropuertos_cantidad_vuelos=Grafo()
    vuelos={}

    if len(sys.argv)!=3:
        print(ERROR)
        return CANTIDAD_INCORRECTA_DE_PARAMETROS

    #Formato aeropuertos: ciudad,codigo_aeropuerto,latitud,longitud
    #Formato vuelos: aeropuerto_i,aeropuerto_j,tiempo_promedio,precio,cant_vuelos_entre_aeropuertos
    with open(str(sys.argv[1]), "r") as f_aeropuertos:
        with open(str(sys.argv[2]), "r") as f_vuelos:
            r_aeropuertos=csv.reader(f_aeropuertos)
            r_vuelos=csv.reader(f_vuelos)

            for row in r_aeropuertos:
                ciudades[row[0]]=[]

                ciudades[row[0]].append((row[1], row[2], row[3]))
                posiciones_aeropuertos[row[1]]=(row[0], row[2], row[3])
                aeropuertos_precio.agregar_vertice(row[1])
                aeropuertos_tiempo.agregar_vertice(row[1])
                aeropuertos_cantidad_vuelos.agregar_vertice(row[1])
                vuelos[row[1]]={}

            for row in r_vuelos:
                aeropuertos_precio.agregar_arista(row[0], row[1], int(row[3]))
                aeropuertos_tiempo.agregar_arista(row[0], row[1], int(row[2]))
                aeropuertos_cantidad_vuelos.agregar_arista(row[0], row[1], 1.0/float(row[4]))
                vuelos[row[0]][row[1]]=(row[2], row[3], row[4])
                vuelos[row[1]][row[0]]=(row[2], row[3], row[4])

    retorno=None

    grafos_aeropuertos=(aeropuertos_tiempo, aeropuertos_precio, aeropuertos_cantidad_vuelos)

    for linea in sys.stdin:
        linea=linea[:len(linea)-1]
        retorno=procesar_comando(linea, ciudades, posiciones_aeropuertos, grafos_aeropuertos, vuelos, retorno)

fly_combi()
