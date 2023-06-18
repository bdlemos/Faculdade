# Procure usar o pacate itertools para resolver os quatro exercicios deste
# VPL. Embora seja possivel resolver os exercicios sem itertools, este modulo
# facilita a resolucao das questoes (e exercita os conceitos aprendidos no
# curso).
from itertools import *

# The list of week days:
dias = ["Seg", "Ter", "Qua", "Qui", "Sex", "Sab", "Dom"]

# The list of possible shifts: Day or Night.
periodos = ["D", "N"]

def buildTurns(profs):
    """Esta funcao recebe uma lista profs de profissionais, e constroi uma
    lista de tuplas. Cada tupla possui quatro elementos:
    - Um dia da semana;
    - Um periodo de trabalho (dia ou noite);
    - Um nome de profissional
    - Um indice indicando qual eh aquele turno. O primeiro turno (Seg/D) possui
    indice 1. O segundo turno (Seg/N) possui indice 2, o terceiro turno (Ter/D)
    possui indice 3, e assim por diante.
    """
    turns = product(dias, periodos)
    tXprof = zip(turns, cycle(profs), count(1))
    return ([a, b, c, d] for (a, b), c, d in tXprof)

def printCSV(profs):
    """Esta funcao recebe uma lista de profissionais, e imprime uma tabela
    CSV com os turnos, usando as colunas: indice, dia, periodo e profissional:
    """
    print("indice, dia, periodo, profissional")
    x = buildTurns(profs)
    for a, b, c, d in x:
        print("%s, %s, %s, %s" % (d, a, b, c))
    return 'fim'

def firstDay(profs, prof):
    """Esta funcao imprime o primeiro dia em que trabalha o profissional 'prof'.
    Caso 'prof' nao esteja presente na lista profs, ou nao exista em um turno
    valido, a funcao precisa retornar a string 'Inexistente'
    """
    # TODO:
    turnos = buildTurns(profs)
    primeiro = next(dropwhile(lambda x: x[2] != prof, turnos))
    return "Inexistente" if not primeiro else primeiro[0]


def countTurns(profs, prof):
    """Esta funcao retorna o numero de turnos em que trabalha o profissional
    'prof'. Caso 'prof' nao trabalhe em algum turno, entao a funcao retorna
    zero.
    """
    # TODO:
    x = filter(lambda x:x[2] == prof, buildTurns(profs))
    return sum(1 for i in x)

def payTurns(profs, prof):
    """Esta funcao retorna o salario semanal de um profissional, assumindo que
    cada turno diurno lhe paga 1000 e cada turno noturno lhe paga 1333.
    Caso 'prof' nao trabalhe em algum turno, a funcao deve retornar zero.
    """
    # TODO:
    x = filter(lambda x:x[2] == prof, buildTurns(profs))
    return sum(1333 if i[1] == 'N' else 1000 for i in x)