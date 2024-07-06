from math import *


class Heap:
    def __init__(self):
        self.heap = [-inf]
    
    def extract_min(self):
        return self.heap[1]

    def sift_up(self, pos):
        while pos > 0:
            if self.heap[pos] < self.heap[pos//2]:
                self.heap[pos], self.heap[pos//2] = self.heap[pos//2], self.heap[pos]
                pos//=2
            else:
                break

    def sift_down(self, pos):
        while len(self.heap) > 2 * pos:
            if len(self.heap > 2 * pos + 1):
                if self.heap[pos] > min(self.heap[2 * pos], self.heap[2 * pos + 1]):
                    if min(self.heap[2 * pos], self.heap[2 * pos + 1]) == self.heap[2 * pos]:
                        self.heap[pos], self.heap[2 * pos] = self.heap[2 * pos], self.heap[pos]
                        pos *= 2
                    else:
                        self.heap[pos], self.heap[2 * pos + 1] = self.heap[2 * pos + 1], self.heap[pos]
                        pos = pos * 2 + 1
            else:
                if self.heap[pos] > self.heap[2 * pos]:
                    self.heap[pos], self.heap[2 * pos] = self.heap[2 * pos], self.heap[pos]
                    pos *= 2
    
    def append(self, element):
        self.heap.append(element)
        self.sift_up(len(self.heap) - 1)

    def decrease_key(self, element, delta):
        pos = self.heap.index(element)
        self.heap[pos] -= delta
        self.sift_up(pos)
    
    def delete(self, element):
        pos = self.heap.index(element)
        self.heap[pos], self.heap[-1] = self.heap[-1], self.heap[pos]
        self.heap.pop()
        self.sift_down(pos)

heap = Heap()

N = int(input())
M = int(input())

class Graph:
    def __init__(self, n):
        self.graph = [[]*n]

    def output(self):
        return self.graph

    def add_vertice(self):
        self.graph.append([])

    def add_edge(self, from_, to, weight):
        self.graph[from_].append([to, weight])
        self.graph[to].append([from_, weight])


graph = Graph(N)
for i in range(M):
    graph.add_edge(int(input()), int(input()), int(input()))

used = []
heap.append(0, 0)
for i in range(1, N):
    heap.append((inf, i))
while len(heap.heap) > 0:
    x = heap.extract_min()
    heap.delete(heap.extract_min())
    used.append(x)
    for i in graph.output()[x]:
        if graph.output[i]
