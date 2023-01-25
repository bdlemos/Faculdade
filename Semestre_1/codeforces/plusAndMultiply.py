times = int(input())
contador = 0
while(contador < times):
    n, a, b = input().split(' ')
    n, a, b = int(n), int(a), int(b)
    if n % b != 0 or n % a == 0 :
        print("Yes")
    else:
        print("Nos")
    contador += 1