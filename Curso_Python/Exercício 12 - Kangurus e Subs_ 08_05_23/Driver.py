import sys
import todo

def test(case, args):
    if case == 0:
        return todo.all_subs(args[0], args[1])
    elif case == 1:
        return todo.kanguru(map(int, args))
    else:
        return None

for line in sys.stdin:
    inps = line.strip().split(" ")
    case = int(inps[0])
    args = inps[1:]
    print(test(case, args))