import random

class Polynom:
    def __init__(self) -> None:
        self.coefs = []

    def __init__(self, array) -> None:
        self.coefs = array


def pr(arg1: Polynom, arg2: Polynom) -> Polynom:
    new_poly = [0 for i in range(len(arg1.coefs)+len(arg2.coefs))]
    for i in range(len(arg1.coefs)):
        for j in range(len(arg2.coefs)):
            new_poly[i + j] += arg1.coefs[i] * arg2.coefs[j]

    while new_poly[-1] == 0:
        new_poly.pop()
    
    return Polynom(new_poly)

def poly_gen(degree: int):
    pols = [random.randint(-10, 10) for i in range(degree)]
    for i in pols:
        print(-i)

    result = Polynom([1])
    for i in pols:
        result = pr(result, Polynom([i, 1]))

    print(result.coefs)

poly_gen(int(input()))