from functools import reduce

def delInitials(L):
    """Esta funcao recebe uma lista de strings L, e retorna uma string S.
    S contem os elementos de L que possuem mais de um caracter, sempre com a
    primeira letra maiuscula. Ex.:
    delInitials(['Fer', 'mag', 'Q', 'pereira']) = 'Fer, Mag, Pereira'
    """
    # TODO
    str = ''
    return [str + name.capitalize() for name in L if len(name) > 1]

def everyOccurrence(S, Q):
    """Esta funcao retorna uma lista L formada pelos indices de caracteres na
    string S que existem tambem na string Q. Ex.:
    everyOccurrence('Fernando', 'abcde') == [1, 4, 6]
    everyOccurrence('xaxbxaxyza', 'abcde') == [1, 3, 5, 9]
    Para resolver esse exercicio, voce pode usar a funcao enumerate, ex.:
    [(a, b) for a, b in enumerate('abc')] == [(0, 'a'), (1, 'b'), (2, 'c')]
    Outra dica eh usar combinacoes de 'for' em compreencoes de lista, ex.:
    [(a, b) for a in 'xyz' for b in [1, 2]] ==
    [('x', 1), ('x', 2), ('y', 1), ('y', 2), ('z', 1), ('z', 2)]
    """
    return [a for a, b in enumerate(S) if b in Q]

def factors(N):
    """Retorna uma lista com os divisores do numero N, exceto 1 e N.
    Exemplos:
    factors(6) == [2, 3]
    factors(10) == [2, 5]
    factors(12) == [2, 3, 4, 6]
    factors(28) == [2, 4, 7, 14]
    """
    # TODO
    return [div for div in range(2,int(N/2)+1) if not N % div]

import operator
def isPerfect(N):
    """N eh perfeito se a soma de seus fatores (exceto ele mesmo) eh N.
    obs.: se for utilizar "factors" para resolver esse exercicio, lembre-se,
    que aquela funcao nao retorna o '1' como fator.
    Exemplos:
    isPerfect(6) == True
    isPerfect(10) == False
    isPerfect(12) == False
    isPerfect(28) == True
    """
    # TODO
    div = factors(N)
    return N == reduce(lambda soma, b: soma + b, div, 1)