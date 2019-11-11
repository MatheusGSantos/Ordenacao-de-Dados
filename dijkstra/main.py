# criando a classe Heap
class Heap:
    def __init__(self, heap_ar):
        self.heap_array = heap_ar
        self.heap_size = len(heap_ar)


# instanciando a classe Heap (casos de teste)
with open("couting.txt", 'r') as input_f:
    m_heap = input_f.read().split('\n')[1:]
    m_heap = list(map(int,m_heap))
    m_heap = Heap(m_heap)


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


# função que realiza a operação de troca do max heap numa "subarvore" da heap
def min_heapify(i):
    global m_heap
    l = left(i)
    r = right(i)
    maior = -1  # assumindo que a heap só contenha números positivos
    if (l <= m_heap.heap_size - 1) and (m_heap.heap_array[l] < m_heap.heap_array[i]):
        maior = l
    else:
        maior = i
    if (r <= m_heap.heap_size - 1) and m_heap.heap_array[r] < m_heap.heap_array[maior]:
        maior = r
    if maior != i:
        aux = m_heap.heap_array[i]
        m_heap.heap_array[i] = m_heap.heap_array[maior]
        m_heap.heap_array[maior] = aux
        min_heapify(maior)


# função que aplica max_heapify em toda a heap
def build_min_heap():
    global m_heap
    m_heap.heap_size = len(m_heap.heap_array)
    i = int(m_heap.heap_size / 2)
    for i in range(i-1,-1,-1):
        min_heapify(i)


# heap sort
"""def heap_sort():
    global m_heap
    build_min_heap()
    i = m_heap.heap_size - 1
    while i > 0:
        aux = m_heap.heap_array[0]
        m_heap.heap_array[0] = m_heap.heap_array[i]
        m_heap.heap_array[i] = aux
        m_heap.heap_size -= 1
        min_heapify(0)
        i -= 1
"""

# main
print("Array antes:")
print(m_heap.heap_array)
build_min_heap()
print("\nArray ordenado:")
print(m_heap.heap_array)
