import sys
import todo

def test():
    numbers = [int(x) for x in sys.stdin.read().split()]
    case = numbers[0]
    test_args = numbers[1:]
    if case == 0:
        print(todo.find_double_slope(test_args))
    elif case == 1:
        print(todo.find_increasing_slope(test_args, 3))
    elif case == 2:
        print(todo.find_high_avg_slope(test_args, 5))
    elif case == 3:
        print(todo.find_repeated_element_slope(test_args))
    elif case == 4:
        print(todo.find_high_avg_slope(test_args, 2))
    else:
        print("Opcao desconhecida %d" % case)

test()