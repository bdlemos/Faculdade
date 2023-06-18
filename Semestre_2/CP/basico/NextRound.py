import numpy as np

n, k = input().split()
cont = 0

inp = list(map(int, input().split()))
for i in inp:
    if i > 0 and i >= inp[int(k)-1]:
        cont+=1

print(cont)
