def head(L):
    return L[0]
 
def tail(L):
    return L[1]

def py2ll(L):
    if not L:
        return None
    else:
        return (L[0], py2ll(L[1:]))

def ll2py(L):
    if not L:
        return []
    else:
        return [head(L)] + ll2py(tail(L))

def fact(N):
    if N > 1:
        return N * fact(N-1)
    else:
        return 1

def prime(a):
     return not (a < 2 or any(a % x == 0 for x in range(2, int(a ** 0.5) + 1)))

def mapL(L, f):
    if not L:
        return None
    else:
        return (f(head(L)), mapL(tail(L), f))

def factAll(L):
    return mapL(L,fact)

def strAll(L):
    return mapL(L,str)

def incAll(L):
    return mapL(L, lambda x: x + 1)

def sqrAll(L):
    return mapL(L, lambda x: x*x)

def isPrimeAll(L):
    return mapL(L, prime)

def incAllN(L, N):
    return mapL(L, lambda x: x+N)

def filterL(L, f):
    if not L:
        return None
    else:
        T = filterL(tail(L), f)
        H = head(L)
        return (H, T) if f(H) else T

def filterOdd(L):
    return filterL(L, lambda x: x % 2 == 1)

def filterPositive(L):
    return filterL(L, lambda x: x > 0)

def filterGtN(L, N):
    return filterL(L, lambda x: x > N)

def filterPrimes(L):
    return filterL(L, prime)