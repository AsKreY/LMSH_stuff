from math import inf

class binary_heap:

    def __init__(self):
        self.box = {}
        self.heap = [-inf]

    def siftUp(self, pos):
        while self.heap[pos] < self.heap[pos//2]:
            self.heap[pos], self.heap[pos//2] = self.heap[pos//2], self.heap[pos]
            self.box[self.heap[pos]], self.box[self.heap[pos//2]] = self.box[self.heap[pos//2]], self.box[self.heap[pos]]
            pos //= 2

    def siftDown(self, pos):
        while True:
            pop = len(self.heap)
            if 2*pos +1 < pop:
                a = min(self.heap[2*pos], self.heap[2*pos + 1])
                if self.heap[pos]>self.heap[2*pos]:
                    self.heap[pos], self.heap[2*pos] = self.heap[2*pos], self.heap[pos]
                    self.box[self.heap[pos]], self.box[self.heap[2*pos]] = self.box[self.heap[2*pos]], self.box[self.heap[pos]]
                if self.heap[pos]>self.heap[2*pos+1]:
                    self.heap[pos], self.heap[2*pos + 1] = self.heap[2*pos + 1], self.heap[pos]
                    self.box[self.heap[pos]], self.box[self.heap[2*pos +1]] = self.box[self.heap[2*pos + 1]], self.box[self.heap[pos]]
                pos = a
            elif 2*pop < pop and 2*pop + 1 == pop:
                self.heap[pos], self.heap[2*pos] = self.heap[2*pos], self.heap[pos]
                self.box[self.heap[pos]], self.box[self.heap[2*pos]] = self.box[self.heap[2*pos]], self.box[self.heap[pos]]
            else:
                break
            

    def insert(self, C):
        self.heap.append(C)
        self.siftUp(len(self.heap) - 1)
        self.box[C] = len(self.heap) - 1;

    def getMin(self):
        return self.heap[1]

    def extractMin(self):
        pop = len(self.heap) - 1
        a = self.getMin()
        self.heap[1], self.heap[pop] = self.heap[pop], self.heap[1]
        self.box[self.heap[1]], self.box[self.heap[pop]] = self.box[self.heap[pop]], self.box[self.heap[1]]
        self.box.pop(self.heap[-1])
        self.heap.pop()
        self.siftDown(1)
        return a
    # def decreaseKey(self, C, D):
    #     self.heap[self.box[C]] -= D
    #     self.siftUp(self.box[C]) 
     
a = binary_heap()

a.insert(1)
a.insert(2)
a.insert(4)

print(a.extractMin())
print(a.extractMin())
print(a.extractMin())