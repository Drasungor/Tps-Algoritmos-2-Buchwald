from grafo import *
import math
import heapq
import queue

#Devuelve una lista con el camino reconstruido desde
#el origen hasta el destino
def reconstruir_camino(padres, destino):

    if destino not in padres:
        return None

    camino=[destino]
    v=padres[destino]

    while v!=None:
        camino.append(v)
        v=padres[v]

    camino.reverse()

    return camino


#Devuelve una lista con los vertices por los que
#se debe pasar para obtener el camino minimo, si
#no se puede llegar desde origen a destino devuelve None
def dijkstra(grafo, origen, destino=None):

    padre={}
    distancia={}
    heap=[]

    padre[origen]=None

    for v in grafo.obtener_vertices():
        distancia[v]=math.inf

    distancia[origen]=0

    heapq.heappush(heap, (distancia[origen], origen))

    while len(heap)>0:
        v=heapq.heappop(heap)

        if destino!=None and v[1]==destino:
            return reconstruir_camino(padre, destino), distancia[v[1]]

        for w in grafo.adyacentes(v[1]):
            distancia_auxiliar=distancia[v[1]]+grafo.peso_arista(v[1],w)
            if distancia_auxiliar<distancia[w]:
                padre[w]=v[1]
                distancia[w]=distancia_auxiliar
                heapq.heappush(heap, (distancia[w], w))

    return padre,distancia

#Devuelve un diccionaraio de padres que representa
#las conecciones entre los elementos del arbol generado
#por el recorrido
def recorrido_bfs(grafo, origen):

    q=queue.Queue()

    visitados=[]
    padres={}

    q.put(origen)
    visitados.append(origen)
    padres[origen]=None

    while not q.empty():
        v=q.get()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                visitados.append(w)
                padres[w]=v
                q.put(w)

    return padres


#Devuelve una lista con las aristas del arbol de
#tendido minimo generado
def mst(grafo):

    v=grafo.vertice_aleatorio()
    heap=[]
    visitados=[]
    aristas=[]

    for w in grafo.adyacentes(v):
        heapq.heappush(heap, (grafo.peso_arista(v,w), v, w))

    while len(heap)>0:
        (peso_arista, v, w)=heapq.heappop(heap)

        if w in visitados:
            continue

        aristas.append((v, w))
        visitados.append(w)

        for x in grafo.adyacentes(w):
            if x not in visitados:
                heapq.heappush(heap, (grafo.peso_arista(w,x), w, x))

    return aristas




def _ciclo_de_largo_n(grafo, lista_origen, n, paso_actual, vertice_actual, camino):

    if vertice_actual in lista_origen and paso_actual!=0:
        if paso_actual==n:
            return camino
        return None

    if paso_actual==n:
        return None

    for v in grafo.adyacentes(vertice_actual):
        if v in camino and v !=camino[0]:
            continue
        camino.append(v)
        #BORRAR EL PRINT
        #print(camino)

        camino_aux=_ciclo_de_largo_n(grafo, lista_origen, n, paso_actual+1, v, camino)
        if camino_aux!=None:
            return camino_aux
        camino.pop()

    return None


#Devuelve una lista con un ciclo de largo n que comienza y termina
#en alguno de los elementos del origen
def ciclo_de_largo_n(grafo, lista_origen, n):

    if n>grafo.cantidad_vertices():
        return None

    if len(lista_origen)==1 and len(grafo.adyacentes(lista_origen[0]))==1:
        return None

    for vertice in lista_origen:
        camino=[vertice]
        camino= _ciclo_de_largo_n(grafo, lista_origen, n, 0, vertice, camino)
        if camino!=None:
            return camino

    return None


#Devuelve una forma de recorrer el grafo tomando en
#cuenta los grados iniciales recibidos
def orden_topologico(grafo, grado_inicial):

    q=queue.Queue()

    vertices=grafo.obtener_vertices()

    for v in vertices:
        if grado_inicial[v]==0:
            q.put(v)

    orden=[]

    while not q.empty():
        v=q.get()
        orden.append(v)

        for w in grafo.adyacentes(v):
            grado_inicial[w]-=1
            if grado_inicial[w]==0:
                q.put(w)

    if len(orden)==len(vertices):
        return orden

    return None


#Devuelve un diccionario que contiene la centralidad de
#cada vertice del grafo
def betweeness_centrality(grafo):

    centralidad={}

    vertices=grafo.obtener_vertices()

    for v in vertices:
        centralidad[v]=0

    for v in vertices:
        centralidad_aux={}

        for w in vertices:
            centralidad_aux[w]=0

        padres, distancias =dijkstra(grafo, v)

        vertices_ordenados=[]

        for w in vertices:
            if distancias[w]==math.inf:
                continue
            vertices_ordenados.append((distancias[w], w))


        vertices_ordenados.sort(reverse=True)

        for w in vertices_ordenados:
            if w[1]==v:
                continue
            centralidad_aux[padres[w[1]]]+= 1 + centralidad_aux[w[1]]

        for w in vertices:
            if w==v:
                continue

            centralidad[w]+=centralidad_aux[w]

    return centralidad
