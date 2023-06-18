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

def size(L):
    if not L:
        return 0
    else:
        return 1 + size(tail(L))

def sorted(L):
    if not L:
        return True
    if not tail(L):
        return True
    else:
        h1 = head(L)
        h2 = head(tail(L))
        return h1 <= h2 and sorted(tail(L))
        

def sum(L):
    if not L:
        return 0
    if not tail(L):
        return head(L)
    else:
        return head(L) + sum(tail(L))

def split(L):
    if not L:
        return (None, None)
    if not tail(L):
        return (L, None)
    else:
        h1 = head(L)
        h2 = head(tail(L))
        t1, t2 = split(tail(tail(L)))
        return (h1, t1), (h2,t2)
        

def merge(L0, L1):
    if not L0:
        return L1
    if not L1:
        return L0
    else:
        h0 = head(L0)
        h1 = head(L1)
        t0 = tail(L0)
        t1 = tail(L1)

        if h0 >= h1:
            return (h1, merge(t1, L0))
        else:
            return (h0, merge(t0, L1))

def mSort(L):
    if not L:
        return None
    if not tail(L):
        return L
    else:
        L1, L2 = split(L)
        return merge(mSort(L1), mSort(L2))

def max(L):
    L1 = mSort(L)
    if not tail(L1):
        return head(L1)
    else:
        return max(tail(L1))

def get(L, N):
    L1 = ll2py(L)
    return L1[N]