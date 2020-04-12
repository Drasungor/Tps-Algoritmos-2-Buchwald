from grafo import *
import string

def print_test(mensaje, condicion):

    if condicion:
        mensaje += ": Ok"
    else:
        mensaje += ": ERROR"

    print(mensaje)


def grafo_vacio():

    print("PRUEBAS GRAFO VACIO")

    grafo=Grafo()

    print_test("El grafo esta vacio", grafo.esta_vacio())
    grafo.borrar_vertice("hola")
    print_test("El grafo tiene 0 elementos", grafo.cantidad_vertices()==0)
    print_test("Pedir un vertice aleatorio devuelve None", grafo.vertice_aleatorio()==None)

    print()

def grafo_con_1_elemento():

    print ("PRUEBAS GRAFO 1 ELEMENTO")

    grafo=Grafo()

    grafo.agregar_vertice("hola")

    print_test("El grafo no esta vacio", not grafo.esta_vacio())
    print_test("El grafo tiene 1 vertice", grafo.cantidad_vertices()==1)
    print_test("El vertice agregado esta en el grafo", grafo.pertenece("hola"))
    print_test("El vertice no tiene aristas", not grafo.existe_arista("hola", "chau"))
    print_test("Pedir un vertice aleatorio devuelve el unico elemento del grafo", grafo.vertice_aleatorio()=="hola")
    print_test("Pedir los adyacentes de un vertice inexistente devuelve None", grafo.adyacentes("Hola")==None)

    print()


def grafo_con_arista():

    print("PRUEBAS GRAFO CON ARISTA")

    grafo=Grafo()

    v="hola"
    w="chau"

    grafo.agregar_arista(v, w, 3)
    print_test("Los verices agregados con la creacion de una arista pertenecen al grafo", grafo.pertenece(v) and grafo.pertenece(w))
    print_test("La arista existe en el grafo", grafo.existe_arista(v,w))
    print_test("Hay dos vertices en el grafo", grafo.cantidad_vertices()==2)
    print_test("La arista tiene el peso adecuado", grafo.peso_arista(v,w)==3)
    grafo.agregar_arista(v, w, 5)
    print_test("Si se guarda la arista nuevamente con un peso distinto queda el nuevo peso", grafo.peso_arista(v,w)==5)
    grafo.borrar_arista(v,w)
    print_test("La arista no existe una vez eliminada", not grafo.existe_arista(v,w))
    print_test("Hay 2 vertices en el grafo una vez borrada la arista", grafo.cantidad_vertices()==2)
    print_test("Los vertices siguen perteneciendo al grafo una vez borrada la arista", grafo.pertenece(v) and grafo.pertenece(w))
    grafo.agregar_vertice(v)
    print_test("Agregar nuevamente un elemento ya presente no modifica el grafo", grafo.cantidad_vertices()==2)

    print()

def prueba_volumen():

    print("PRUEBAS DE VOLUMEN")

    grafo=Grafo()

    for i in range(250):
        grafo.agregar_vertice(str(i))

    print_test("El grafo tiene la cantidad de vertices adecuada", grafo.cantidad_vertices()==250)

    for i in range(250):
        son_los_correctos=grafo.pertenece(str(i))

    print_test("Los vertices pedidos son los guardados en el grafo", son_los_correctos)

    for i in range(2,250,2):
        grafo.agregar_arista(str(i-2), str(i), i)

    for i in range(2,250,2):
        pertenecen=grafo.existe_arista(str(i-2), str(i))

        if not pertenecen:
            break


    print_test("Se agregan aristas y estan en el grafo", pertenecen)
    print_test("El grafo sigue con la cantidad de vertices adecuada", grafo.cantidad_vertices()==250)

    for i in range(2,250,2):
        grafo.borrar_arista(str(i-2), str(i))

    print_test("Luego de borrar las aristas se tiene la misma cantidad de vertices que antes", grafo.cantidad_vertices()==250)

    for i in range(2,250,2):
        pertenecen=grafo.existe_arista(str(i-2), str(i))

        if pertenecen:
            break

    print_test("Se eliminaron correctamente todas las aristas", not pertenecen)

    print()

grafo_vacio()
grafo_con_1_elemento()
grafo_con_arista()
prueba_volumen()
