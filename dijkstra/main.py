import sys
import copy

# criando a classe Heap
class Heap:
    def __init__(self, heap_ar):
        self.heap_array = heap_ar
        self.heap_size = len(heap_ar)


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
    
    # agora temos uma matriz de vértices
    # construindo então uma lista de adjacencias
    adj = {}
    for v in range(len(matrix)):
        adj[v] = copy.copy(matrix[v])
        del adj[v][adj[v].index(0)]
""""    
    for elem in adj:
        print(elem, end=': ')
        print(adj[elem])
        print()
    
    for elem in matrix:
        print(elem)


    for x in matrix:
        print(x)
"""

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
    global m_heap
    l = left(i)
    r = right(i)
    menor = -1  # assumindo que a heap só contenha números positivos
    if (l <= m_heap.heap_size - 1) and (m_heap.heap_array[l] < m_heap.heap_array[i]):
        menor = l
    else:
        menor = i
    if (r <= m_heap.heap_size - 1) and m_heap.heap_array[r] < m_heap.heap_array[menor]:
        menor = r
    if menor != i:
        aux = m_heap.heap_array[i]
        m_heap.heap_array[i] = m_heap.heap_array[menor]
        m_heap.heap_array[menor] = aux
        min_heapify(menor)


# função que aplica max_heapify em toda a heap
def build_min_heap():
    global m_heap
    m_heap.heap_size = len(m_heap.heap_array)
    i = int(m_heap.heap_size / 2)
    for i in range(i-1,-1,-1):
        min_heapify(i)


# retorna o valor minimo (raiz)
def heap_minimum():
    global m_heap
    return m_heap.heap_array


# extrai o valor mínimo
def heap_extract_min():
    if(m_heap.heap_size < 1):
        return "heap underflow"
    minimo = m_heap.heap_array[0]
    m_heap.heap_array[0] = m_heap.heap_array[m_heap.heap_size-1]
    m_heap.heap_size -= 1
    min_heapify(0)
    return minimo


# sobe o nó
def heap_decrease_key(i, key): #key: valor inteiro a ser colocado
    global m_heap
    if(key > m_heap.heap_array[i]):
        return "nada a ser feito"
    m_heap.heap_array[i] = key
    while (i>1) and (m_heap.heap_array[parent(i)] < m_heap.heap_array[i]):
        aux = m_heap.heap_array[i]
        m_heap.heap_array[i] = m_heap.heap_array[parent(i)]
        m_heap.heap_array[parent(i)] = aux
        i = parent(i)


# insere uma chave
def min_heap_insert(key):
    global m_heap
    m_heap.heap_array += 1
    m_heap.heap_array.append(sys.maxsize)
    heap_decrease_key(m_heap.heap_size,key)


def func():
    return


# main
"""print("Array antes:")
print(m_heap.heap_array)
build_min_heap()
print("\nArray ordenado:")
print(m_heap.heap_array)"""