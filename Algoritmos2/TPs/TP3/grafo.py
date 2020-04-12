import random


class Grafo (object):

    def __init__(self):
        self.numero_vertices = 0
        self.vertices = {}

    #Indica la cantidad de vertices presente en el grafo
    def cantidad_vertices(self):
        return self.numero_vertices

    #Indica si el vertice pasado pertenece o no al grafo
    def pertenece(self, v):
        return v in self.vertices

    def existe_arista(self, v, w):
        return w in self.vertices[v]

    #Agrega un vertice al grafo, si este ya existe
    #no se modifica el grafo
    def agregar_vertice(self, v):

        if v in self.vertices:
            return

        self.vertices[v]={}
        self.numero_vertices +=1

    #Elimina un vertice del grafo
    def borrar_vertice(self, v):

        if self.numero_vertices==0:
            return

        del self.vertices[v]

        for w in self.vertices:
            del w[v]

        self.numero_vertices -=1

    #Agrega una conexion en la que v apunta a w y viceversa, si alguno
    #de los dos no existe lo agrega al grafo
    #Si la arista ya existia la actualiza
    def agregar_arista(self, v, w, peso):

        if v not in self.vertices:
            self.agregar_vertice(v)

        self.vertices[v][w]=peso

        if w not in self.vertices:
            self.agregar_vertice(w)

        self.vertices[w][v]=peso


    #Elimima la conexion entre dos vertices del grafo
    def borrar_arista(self, v, w):
        if v not in self.vertices or v not in self.vertices:
            return

        del self.vertices[v][w]
        del self.vertices[w][v]


    #Devuelve una lista con los vertices presentes en el grafo
    def obtener_vertices(self):
        return list(self.vertices.keys())


    #Devuelve una lista con los adyacentes del vertice
    #Si el vertice no existe devuelve None
    def adyacentes(self, v):

        if v not in self.vertices:
            return None

        return list(self.vertices[v].keys())


    #Devuelve un vertice aleatorio del grafo
    def vertice_aleatorio(self):

        if self.esta_vacio():
            return None

        return random.choice(list(self.vertices.keys()))

    #Devuelve un booleano que indica si el grafo esta o no vacio
    def esta_vacio(self):
        return self.numero_vertices==0

    #Devuelve el peso de la arista que conecta a v y w
    #si esta no existe devuelve None
    def peso_arista(self, v, w):
        if not self.existe_arista(v,w):
            return None

        return self.vertices[v][w]
