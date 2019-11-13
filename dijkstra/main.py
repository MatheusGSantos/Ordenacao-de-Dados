import sys
import heapq

# criando a classe Grafo
class Graph:
    def __init__(self):
        self.adj_list = {}
    

    def add_vertex(self,vertex):
        if vertex not in self.adj_list:
            self.adj_list[vertex] = {}
    

    def add_edge(self, vertex1, vertex2, weight):
        self.adj_list[vertex1][vertex2] = weight
        self.adj_list[vertex2][vertex1] = weight


    def dijkstra(self, start, finish):
        queue = []
        distances = {}
        previous = {}
        # initialize
        for vertex in self.adj_list:
            if(vertex == start):
                distances[vertex] = 0
                heapq.heappush(queue, [0, vertex])
            else:
                distances[vertex] = sys.maxsize
                heapq.heappush(queue, [sys.maxsize, vertex])
            previous[vertex] = None

        # enquanto tiver elementos na fila
        while queue:
            pass



with open("dij10.txt", 'r') as input_f:
    matrix = input_f.readline()
    matrix = input_f.read().split('\n')[:]
    matrix = [x.split(" ") for x in matrix]
    for l in matrix:
        if l[0] == '':
            del matrix[matrix.index(l)]
            continue
        for i in l:
            if(i == ''):
                del matrix[matrix.index(l)][matrix[matrix.index(l)].index(i)]


    # transformar para inteiro
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            matrix[i][j] = int(matrix[i][j])

    """
    matrix.append([])
    
    # adicionar 0 e rebater o triangulo
    auxiliar = 0
    i = 0
    for x in matrix:
        matrix[i].insert(0,0)

        # preencher o triangulo debaixo
        for c in range(auxiliar):
            matrix[i].insert(0,matrix[auxiliar-1-c][auxiliar])
        i += 1
        auxiliar += 1
    """
    """for p in matrix:
        print(p)"""
    # agora temos uma matriz de vértices

    ## criando o grafo e inserindo vertices e arestas
    # adicionando vértices
    grafo = Graph()
    for z in range(len(matrix)+1):
        grafo.add_vertex(z)

    # adicionando arestas
    aux = 0
    for x in range(len(matrix)): # de 0 a 8
        for y in range(x+1, len(matrix)+1): # de 1 a 9, de 2 a 9, ...
            grafo.add_edge(x,y,matrix[x][aux])
            aux += 1
        aux = 0
"""
    for each_k in grafo.adj_list:
        print(each_k)
        print(grafo.adj_list[each_k])
"""    

# main
grafo.dijkstra(0,9)