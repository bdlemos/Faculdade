import sys

import todo

def test(case, args):
    if case == 0:
        return todo.num_coins(90, {1, 3, 4, 7})
    elif case == 1:
        return todo.num_coins(90, range(1, 5))
    elif case == 2:
        args = [int(e) for e in args]
        return todo.num_coins(args[0], args[1:])
    elif case == 3:
        return todo.num_ways(90, {1, 3, 4, 7})
    elif case == 4:
        return todo.num_ways(90, range(1, 5))
    elif case == 5:
        args = [int(e) for e in args]
        return todo.num_ways(args[0], args[1:])
    elif case == 6:
        return todo.longest_increasing_subsequence("ebfacg")
    elif case == 7:
        return todo.longest_increasing_subsequence("eafbcah")
    elif case == 8:
        return todo.longest_increasing_subsequence(args[0])

for line in sys.stdin:
    inps = line.strip().split(" ")
    case = int(inps[0])
    args = inps[1:] if len(inps) > 1 else []
    print(test(case, args))