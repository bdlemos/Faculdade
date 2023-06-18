def all_subs(s, q):
    """Conta a quantidade de ocorrencias da string q dentro da string s.

    Parameters
    ----------
        s (str): a string que servirah de base para a busca.
        q (str): a substring que serah procurada.

    Returns:
    --------
        A quantidade de vezes em que q ocorre dentro de s. Caso a string q
        seja vazia, entao o valor retornado serah -1

    Example
    >>> all_subs('ababacababa', 'aba')
    4

    >>> all_subs('ababa', 'abba')
    0

    >>> all_subs('', 'a')
    0

    >>> all_subs('ababa', '')
    -1
    """
    #TODO

    if not q:
        return -1
    return sum(1 for i in range(len(s)-len(q)+1) if s[i:i+len(q)] == q)

def kanguru(L):
    """Mapeia cada numero 'n' em L para '(kan)?(gu)?(ru)?' ou o proprio 'n'

    Exemplos:
    >>> kanguru([])
    []

    >>> kanguru([9, 10, 11, 21, 23, 105])
    ['kan', 'gu', '11', 'kanru', '23', 'kanguru']

    >>> kanguru(range(2, 8))
    ['2', 'kan', '4', 'gu', 'kan', 'ru']

    >>> kanguru([3, 5, 7, 15, 21, 35, 105, 2])
    ['kan', 'gu', 'ru', 'kangu', 'kanru', 'guru', 'kanguru', '2']
    """
    #TODO
    aux = []
    for i in L:
        if i % 3 == 0 and i % 5 == 0 and i % 7 == 0:
            aux += ['kanguru']
        elif i % 3 == 0 and i % 5 == 0:
            aux += ['kangu']
        elif i % 3 == 0 and i % 7 == 0:
            aux += ['kanru']
        elif i % 5 == 0 and i % 7 == 0:
            aux += ['guru']
        elif i % 3 == 0:
            aux += ['kan']
        elif i % 5 == 0:
            aux += ['gu']
        elif i % 7 == 0:
            aux += ['ru']
        else:
            aux+= [str(i)]
    return aux