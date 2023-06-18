import sys

from todo import *

def test_const():
    env = {}
    instructions = Instructions()
    instructions.add_instruction(make_const("a", "1"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction(env, instructions)
    if env["a"] == 1:
        print("Teste const PASSOU")

def test_add():
    env = {"a": 1, "b": 2}
    instructions = Instructions()
    instructions.add_instruction(make_add("c", "a", "b"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction(env, instructions)
    if env["c"] == 3:
        print("Teste add PASSOU")

def test_mul():
    env = {"a": 3, "b": 4}
    instructions = Instructions()
    instructions.add_instruction(make_mul("c", "a", "b"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction(env, instructions)
    if env["c"] == 12:
        print("Teste mul PASSOU")

def test_and():
    env = {"a": 3, "b": 0}
    instructions = Instructions()
    instructions.add_instruction(make_and("c", "a", "b"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction(env, instructions)
    if env["c"] == 0:
        print("Teste and PASSOU")

def test_grt():
    env = {"a": 5, "b": 4}
    instructions = Instructions()
    instructions.add_instruction(make_grt("c", "a", "b"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction(env, instructions)
    if env["c"] == 1:
        print("Teste grt PASSOU")

def test_bez_is_zero():
    env = {"a": 0}
    instructions = Instructions()
    instructions.add_instruction(make_bez("a", "0"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction(env, instructions)
    next_instruction = instructions.get_next_instruction()
    if next_instruction.str == "if a == 0 goto 0":
        print("Teste bez_is_zero PASSOU")

def test_bez_not_is_zero():
    env = {"a": 1}
    instructions = Instructions()
    instructions.add_instruction(make_bez("a", "0"))
    instructions.add_instruction(make_bez("xx", "1000"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction(env, instructions)
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    if next_instruction.str == "if xx == 0 goto 1000":
        print("Teste bez_not_is_zero PASSOU")

def test_jump():
    instructions = Instructions()
    instructions.add_instruction(make_jump("0"))
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    next_instruction({}, instructions)
    next_instruction = instructions.get_next_instruction()
    print(next_instruction.str)
    if next_instruction.str == "jump 0":
        print("Teste jump PASSOU")

def make_interpreter():
    """Essa instrucao constroi um 'interpretador', isso eh, um programa que
    emite instrucoes para interpretar programas. O codigo para criar as
    instrucoes fica armazenado em um dicionario. Veja que esse codigo implementa
    um switch funcional. Ha varias explicacoes na internet sobre como
    implementar switches usando dicionarios. Veja, por exemplo, esse link em
    Stack Overflow:

    using-a-dictionary-as-a-switch-statement-in-python

    Returns
    -------
        Um dicionario que associa nomes de instrucoes a funcoes que criam
        interpretadores para essas instrucoes.
    """
    interpreter = {}
    interpreter["const"] = lambda args: make_const(*args)
    interpreter["add"] = lambda args: make_add(*args)
    interpreter["mul"] = lambda args: make_mul(*args)
    interpreter["and"] = lambda args: make_and(*args)
    interpreter["grt"] = lambda args: make_grt(*args)
    interpreter["bez"] = lambda args: make_bez(*args)
    interpreter["jump"] = lambda args: make_jump(*args)
    return interpreter

def read_instructions(interpreter):
    """Essa funcao leh um conjunto de linhas da entrada padrao, e usa o
    interpretador criado por make_interpreter para criar uma instrucao para
    cada linha lida.

    Parameters
    ----------
    interpreter : dict
        O dicionario com funcoes que criam instrucoes.

    Returns
    -------
        Um objeto do tipo Instruction, contendo todas as instrucoes lidas.
    """
    instructions = Instructions()
    for line in sys.stdin:
        inps = line.strip().split(" ")
        opcode = inps[0]
        operands = inps[1:]
        instructions.add_instruction(interpreter[opcode](operands))
    return instructions

def eval_program_on_empty_env(instructions):
    """Essa funcao interpreta as instrucoes ateh que uma instrucao vazia
    seja encontrada. O environment em que comeca a interpretacao eh vazio.

    Parameters
    ----------
    instructions : Instruction
        a lista de instrucoes que deve ser interpretada.

    Returns
    -------
        O environment que resulta da interpretacao das instrucoes.
    """
    env = {}
    next_instruction = instructions.get_next_instruction()
    while next_instruction:
        next_instruction(env, instructions)
        next_instruction = instructions.get_next_instruction()
    return env

def print_env(environment):
    """Essa funcao imprime o environment recebido, como uma sequencia de
    linhas, cada uma contendo uma variavel, dois pontos e o valor da variavel.

    Parameters
    ----------
    environment : dict
        o dicionario que representa o environment que deve ser impresso.
    """
    for variable, value in sorted(environment.items()):
        print(variable + ": " + str(value))

def run_interpreter():
    """Essa funcao simula a interpretacao de um programa lido a partir da linha
    de comando.
    """
    print_env(eval_program_on_empty_env(read_instructions(make_interpreter())))

def test():
    """Codigo de teste. Essa parte do programa le a opcao de teste da entrada
    padrao. Algumas opcoes chamam testes pre-existentes. Outras opcoes chamam o
    interpretador de programas via a funcao run_interpreter
    """
    line = next(sys.stdin)
    case = int(line)
    if case == 0:
        test_const()
    elif case == 1:
        test_add()
    elif case == 2:
        test_mul()
    elif case == 3:
        test_grt()
    elif case == 4:
        test_bez_is_zero()
    elif case == 5:
        test_bez_not_is_zero()
    elif case == 6:
        test_jump()
    elif case == 7:
        test_and()
    else:
        run_interpreter()

test()