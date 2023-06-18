import sys
import pandas as pd

import todo

def test(case, args):
    games = pd.read_csv('games.csv')
    if case == 0:
        return todo.numRows(games)
    elif case == 1:
        return todo.numColumns(games)
    elif case == 2:
        return todo.numGoldTotal(games)
    elif case == 3:
        return todo.numSummerGoldCountry(games, args[0])
    elif case == 4:
        return todo.getCodeMaxSummerGold(games)
    elif case == 5:
        return todo.getNthBestSummerCountry(games, int(args[0]))
    elif case == 6:
        return todo.numCountriesWithMoreThanNWinterMedals(games, int(args[0]))
    elif case == 7:
        return todo.numWinterCountries(games)
    elif case == 8:
        return todo.countGoldsWithLetter(games, args[0])
    elif case == 9:
        return todo.countHybernalCountries(games)

for line in sys.stdin:
    inps = line.strip().split(" ")
    case = int(inps[0])
    args = inps[1:]
    print(test(case, args))