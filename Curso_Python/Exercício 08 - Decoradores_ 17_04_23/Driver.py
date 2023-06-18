import sys

import todo

def test(case, args):
    if case == 0:
        return todo.fact(int(args[0]))
    elif case == 1:
        return todo.join_args(args[1:], args[0])
    elif case == 2:
        from math import sqrt
        dec_sqrt = todo.decorator_non_negative(sqrt)
        return dec_sqrt(float(args[0]))
    elif case == 3:
        value = todo.gcd(int(args[0]), int(args[1]))
        return (value, todo.gcd.num_calls)
    elif case == 4:
        value = todo.fib(int(args[0]))
        return (value, len(todo.fib.arg_set))
    elif case == 5:
        return todo.inc(args[0])
    else:
        return None

for line in sys.stdin:
    inps = line.strip().split(" ")
    case = int(inps[0])
    args = inps[1:]
    print(test(case, args))