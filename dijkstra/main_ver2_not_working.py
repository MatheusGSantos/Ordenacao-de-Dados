import sys

# criando a classe Heap
class Heap:
    def __init__(self, heap_ar=[]):
        self.heap_array = heap_ar
        self.heap_size = len(heap_ar)


# declarando a fila
p_queue = Heap()


# função que retorna o indice do filho da esquerda
def left(i):
    if i == 0:
        return i+1
    else:
        return int(2*i)


# função que retorna o filho da direita
def right(i):
    if i == 0:
        return i+2
    else:
        return int(2*i + 1)


# função que retorna o pai
def parent(i):
    return int((i-1)/2)


# função que realiza a operação de troca do max heap numa "subarvore" da heap
def min_heapify(i):
    global p_queue
    l = left(i)
    r = right(i)
    menor = -1  # assumindo que a heap só contenha números positivos
    if (l <= p_queue.heap_size - 1) and (p_queue.heap_array[l][1] < p_queue.heap_array[i][1]):
        menor = l
    else:
        menor = i
    if (r <= p_queue.heap_size - 1) and p_queue.heap_array[r][1] < p_queue.heap_array[menor][1]:
        menor = r
    if menor != i:
        aux = p_queue.heap_array[i]
        p_queue.heap_array[i] = p_queue.heap_array[menor]
        p_queue.heap_array[menor] = aux
        min_heapify(menor)


# função que aplica max_heapify em toda a heap
def build_min_heap():
    global p_queue
    p_queue.heap_size = len(p_queue.heap_array)
    i = int(p_queue.heap_size / 2)
    for i in range(i-1,-1,-1):
        min_heapify(i)


# retorna o valor minimo (raiz)
def heap_minimum():
    global p_queue
    return p_queue.heap_array[0]


# extrai o valor mínimo
def heap_extract_min():
    global p_queue
    if(p_queue.heap_size < 1):
        return "heap underflow"
    minimo = p_queue.heap_array[0]
    p_queue.heap_array[0] = p_queue.heap_array[p_queue.heap_size-1]
    p_queue.heap_size -= 1
    min_heapify(0)
    return minimo


# sobe o nó
def heap_decrease_key(i, key): # key: valor inteiro a ser colocado
    global p_queue
    if(key[1] > p_queue.heap_array[i][1]):
        return "nada a ser feito"
    p_queue.heap_array[i] = key
    while (i>1) and (p_queue.heap_array[parent(i)][1] < p_queue.heap_array[i][1]):
        aux = p_queue.heap_array[i]
        p_queue.heap_array[i] = p_queue.heap_array[parent(i)]
        p_queue.heap_array[parent(i)] = aux
        i = parent(i)


# insere uma chave
def min_heap_insert(key):
    global p_queue
    p_queue.heap_size += 1
    p_queue.heap_array.append(sys.maxsize)
    heap_decrease_key(p_queue.heap_size,key)


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
        global p_queue
        distances = {}
        previous = {}
        # initialize
        for vertex in self.adj_list:
            if(vertex == start):
                distances[vertex] = 0
                min_heap_insert([vertex,0])
            else:
                distances[vertex] = sys.maxsize
                min_heap_insert([vertex,sys.maxsize])
            previous[vertex] = None
        print(p_queue.heap_array)

        # enquanto tiver elementos na fila
        # while(p_queue.heap_size):



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