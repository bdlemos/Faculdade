from functools import lru_cache
from functools import reduce

def num_coins(N, coins):
    """O numero minimo de moedas cujos valores estao em coins que de soma N.

    Exemplos:
    * num_coins(10, {1, 3, 4}) == 3
    * num_coins(10, [1, 2, 4]) == 3
    * num_coins(11, [1, 4, 5]) == 3
    * num_coins(21, [1, 4, 5]) == 5
    * num_coins(21, range(1, 4, 2)) == 7

    Parameters:
        N (int): inteiro que deve ser construido como uma soma de moedas.
        coins (int iter): conjunto com os valores de moedas.

    Returns:
        integer denoting minimum number of coints that add up to x.
    """
    # TODO: implementar essa funcao.
    @lru_cache(maxsize=None)
    def num_coins_aux(x):
        if x < 0:
            return float('inf')
        if x == 0:
            return 0
        else:
            mins = [num_coins_aux(x-coin) + 1 for coin in coins]
            return reduce(min,mins)
    return num_coins_aux(N)

def num_ways(N, coins):
    """Numero de formas diferentes de construir N como soma de moedas em coins.

    Exemplos:
    * num_ways(10, {1, 3, 4}) == 64
    * num_ways(10, [1, 2, 4]) == 64
    * num_ways(11, [1, 4, 5]) == 41
    * num_ways(21, [1, 4, 5]) == 2252
    * num_ways(21, range(1, 4, 2)) == 1873

    Parameters:
        N (int): inteiro que deve ser construido como uma soma de moedas.
        coins (int iter): conjunto com os valores de moedas.

    Returns:
        int que representa o numero de formas de somarmos moedas ateh x.
    """
    # TODO: implementar essa funcao.
    @lru_cache(maxsize=None)
    def num_way_aux(x):
        if x < 0:
            return 0
        if x == 0:
            return 1
        else:
            total = [num_way_aux(x-coin) for coin in coins]
            return sum(total)
    return num_way_aux(N)

def longest_increasing_subsequence(s):
    '''Longest Increasing Subsequence.

    Essa funcao encontra o tamanho da maior subsequencia de caracteres
    dentro da string. Exemplos:
    1. longest_increasing_subsequence("") == 0 -> string vazia
    2. longest_increasing_subsequence("ebfacg") == 3 -> b-c-g
    3. longest_increasing_subsequence("eafbca") == 3 -> a-b-c
    4. longest_increasing_subsequence("eafbcah") == 4 -> a-b-c-h

    Parameters:
        s (str): string que representa a sequencia de caracteres.

    Returns:
        int que representa a maior subsequencia crescente (e nao contigua) de
        caracteres dentro de s
    '''
    @lru_cache(maxsize=None)
    def memoized_lis(i):
        if i == 0:
            return 1
        else:
            max_seq = 1
            for j in range(i):
                if s[j] < s[i]:
                    max_seq = max(max_seq, memoized_lis(j) + 1)
            return max_seq

    return max(memoized_lis(i) for i in range(len(s)))