## Recebe uma entrada e monta o tableau utilizando apenas listas

import sys

def main():
    # Le de um diretorio
    with open(sys.argv[1], 'r') as f:
        entrada = f.read().split('\n')
    for i in range(len(entrada)):
        entrada[i] = entrada[i].split(' ')
    
    # Le o numero de variaveis e restricoes
    n, m = map(int, entrada[0])

    # Le a funcao objetivo
    fo = list(map(int, entrada[1]))

    # Le as restricoes
    restricoes = [list(map(int, linha)) for linha in entrada[2:2+m]]

    # Le os valores de b
    b = list(restricoes[i].pop() for i in range(n))

    return fo, restricoes, b

def Simplex_2Fases(fo, restricoes, b):
    # Tornar b>=0
    for i in range(len(b)):
        if b[i] < 0:
            restricoes[i] = [-x for x in restricoes[i]]
            b[i] *= -1

    #Encontrar a base viavel

    ans = func()


def aux_pl(fo, restricoes, b):
    new_fo = [0]*len(fo) + [-1]*len(restricoes)


    for i in range(len(restricoes)):
        restricoes[i] = restricoes[i] + [0]*len(restricoes)
        restricoes[i][len(fo)+i] = 1

    new_restricoes = restricoes
    print(new_fo)
    print(new_restricoes)

    # # Adicionar variaveis de folga
    # for i in range(len(restricoes)):
    #     restricoes[i].append(1 if i == 0 else 0)
    #     fo.append(0)

    # # Adicionar variaveis de excesso
    # for i in range(len(restricoes)):
    #     restricoes[i].append(-1 if i == 0 else 0)
    #     fo.append(0)

    # # Adicionar variaveis artificiais
    # for i in range(len(restricoes)):
    #     restricoes[i].append(1 if i == 0 else 0)
    #     fo.append(-1)

    return fo, restricoes, b

def func():
    pass


if __name__ == '__main__':
    fo, restricoes, b = main()
    aux_pl(fo, restricoes, b)