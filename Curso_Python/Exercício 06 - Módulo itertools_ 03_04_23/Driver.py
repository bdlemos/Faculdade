import sys

import todo

def test(case, args):
    if case == 0:
        return todo.printCSV(args)
    elif case == 1:
        return todo.firstDay(args, args[-1])
    elif case == 2:
        return todo.countTurns(args, args[-1])
    elif case == 3:
        return todo.payTurns(args, args[-1])
    else:
        return None

for line in sys.stdin:
    inps = line.strip().split(" ")
    case = int(inps[0])
    args = inps[1:]
    print(test(case, args))

    