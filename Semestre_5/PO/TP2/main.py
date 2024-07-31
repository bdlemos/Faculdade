## Recebe uma entrada e monta o tableau utilizando apenas listas

import sys
import numpy as np

def read_pl():
    # Le de um diretorio
    with open(sys.argv[1], 'r') as f:
        entrada = f.read().split('\n')
    for i in range(len(entrada)):
        if entrada[i] != '':
            entrada[i] = entrada[i].split(' ')
    # Le o numero de variaveis e restricoes
    n, m = map(int, [i for i in entrada[0] if i != ''])
    #print(entrada)
    # Le a funcao objetivo
    fo = list(map(float, entrada[1]))
    # Le as restricoes
    restricoes = [list(map(float, linha)) for linha in entrada[2:2+n] if linha != '']

    # Le os valores de b
    b = list(i.pop() for i in restricoes)

    return np.array(fo), np.array(restricoes), np.array(b)

def read_certificate(file):
    # Le de um diretorio
    with open(file, 'r') as f:
        entrada = f.read().split('\n')
    return (entrada[0],[float(i) for i in entrada[1].split(' ') if i != ''])

def verifica_certificado_inviavel(fo, restricoes, b, cert):
    epsilon = 1e-1
    # Verifica se o certificado é viável
    yA = np.dot(cert, restricoes)
    by = np.dot(b, cert)
    print(yA, by)
    for i in yA:
        if i < -epsilon:
            return False
    if by > epsilon:
        return False
    return True
def verifica_certificado_ilimitado(fo, restricoes, cert):
    epsilon = 1e-9
    # Verifica se o certificado é viável
    for i in range(len(restricoes)):
        if len(restricoes[i]) != len(cert):
            continue
        if sum([restricoes[i][j]*cert[j] for j in range(len(cert))]) > epsilon and sum([restricoes[i][j]*cert[j] for j in range(len(cert))]) < -epsilon:
            return False
    
    val = sum([fo[j]*cert[j] for j in range(len(cert))])


    if val <= epsilon:
        return False
    return True
    


if __name__ == '__main__':
    fo, restricoes, b = read_pl()
    tipo, cert = read_certificate('certificado.txt')

    file = sys.argv[1].split('/')
    # file = file[0] + '/sol_' +file[1]
    # _, marcin = read_certificate(file)
    print("Meu")
    if tipo == 'inviavel':
        if verifica_certificado_inviavel(fo, restricoes, b, cert):
            print('Certificado viável')
        else:
            print('Certificado inviável')
    elif tipo == 'ilimitada':
        if verifica_certificado_ilimitado(fo, restricoes, cert):
            print('Certificado viável')
        else:
            print('Certificado inviável')
    else:
        print('Tipo de certificado inválido')

    # print("Marcin")
    # if tipo == 'inviavel':
    #     if verifica_certificado_inviavel(fo, restricoes, b, marcin):
    #         print('Certificado viável')
    #     else:
    #         print('Certificado inviável')
    # elif tipo == 'ilimitada':
    #     if verifica_certificado_ilimitado(fo, restricoes, marcin):
    #         print('Certificado viável')
    #     else:
    #         print('Certificado inviável')
    # else:
        # print('Tipo de certificado inválido')