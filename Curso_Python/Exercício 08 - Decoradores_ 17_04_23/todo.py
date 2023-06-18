import functools

def decorator_non_negative(func):
    """Decorador de parametro unico que converte numeros negativos para seu
    valor absoluto positivo.

    Este decorador se aplica somente a funcoes que recebem um unico argumento
    cujo tipo eh numerico (int ou float). O decorador converte esse parametro
    para um valor positivo. Na pratica, o decorador aplica a funcao ABS (valor
    absoluto) ao parametro da funcao decorada.

    Parameters:
    func (function): A funcao que estarah sendo decorada. Espera-se que essa
    funcao receba um unico argumento.

    Returns:
    function: A funcao decorada com wrapper
    """
    @functools.wraps(func)
    def wrapper(num):
        # Para simplificar o exercicio, voce pode assumir que 'num' eh um
        # tipo numerico, isso eh, que suporta a operacao de inversao de sinal.
        # Exemplos de tipos numericos incluem 'int' e 'float'
        #
        # TODO: implemente esse decorador. Por enquanto, ele simplesmente
        # chama a funcao decorada.
        #
        return func(abs(num))
    return wrapper

def decorator_str_to_int(func):
    """Decorador de parametro unico que converte strings para numeros inteiros.

    Este decorador permite passar strings para funcoes que recebem numeros
    inteiros. O decorador se aplica a funcoes que recebem um unico parametro.
    Caso esse parametro seja um string, entao a string eh transformada em um
    numero inteiro, se ela contiver somente digitos. Por exemplo: '23' -> 23.
    Se ela contiver qualquer coisa diferente de um digito, entao a string eh
    transformada no numero zero, ex.: '3.14' -> 0. Se o argumento nao for
    instancia de string, entao nada eh feito: o argumento eh passado como estah
    para a funcao decorada.

    Parameters:
    func (function): A funcao que estarah sendo decorada. Espera-se que essa
    funcao receba um unico argumento.

    Returns:
    function: A funcao decorada com wrapper
    """
    @functools.wraps(func)
    def wrapper(arg):
        # TODO: implemente esse decorador. Por enquanto, ele simplesmente
        # chama a funcao decorada.
        #
        return func(int(arg) if arg.isdigit() else 0)
    return wrapper

def decorator_hide_nums(func):
    """Decorador de multiplos parametros que substitui digitos no valor de
    retorno da funcao decorada por asteriscos.

    Este decorador se aplica a funcoes com qualquer quantidade de argumentos,
    sejam eles passados via posicao ou nome. A restricao eh que o decorador
    se aplica somente a funcoes que retornam strings. O decorador nao faz nada
    com os argumentos da funcao: simplesmente passa esses argumentos para a
    funcao decorada. Porem, ele modifica o valor retornado. Ele substitui cada
    digito na string retornada por um 'x'. Por exemplo: "5 dedos e 2 olhos" ->
    "x dedos e x olhos".

    Parameters:
    func (function): A funcao que estarah sendo decorada. Essa funcao precisa
    retornar uma string.

    Returns:
    function: A funcao decorada com wrapper
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # TODO: implemente esse decorador. Por enquanto, ele simplesmente
        # chama a funcao decorada.
        #
        ret = func(*args, **kwargs)
        if not isinstance(ret, str): 
            return ret
        else:
            return "".join(map(lambda x: 'x' if x.isdigit() else x, ret))
    return wrapper

def num_calls_decorator(func):
    """Decorador que conta quantas vezes cada funcao foi chamada.

    Este decorador acrescenta um atributo 'num_calls' a funcao decorada. Esse
    atributo loga quantas vezes a funcao decorada foi invocada. A implementacao
    deste decorador estah disponivel nas notas de aula.

    Parameters:
    func (function): A funcao que estarah sendo decorada. Nenhuma restricao se
    aplica a funcao.

    Returns:
    function: A funcao decorada com wrapper
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # TODO: implemente esse decorador. Por enquanto, ele simplesmente
        # chama a funcao decorada.
        #
        wrapper.num_calls+=1
        return func(*args, **kwargs)
    # TODO: adicione a funcao um atributo num_calls inicializado com o valor 0:
    wrapper.num_calls = 0
    #
    return wrapper

def count_arg_values_decorator(func):
    """Decorador que loga os argumentos diferentes que cada funcao recebeu.

    Este decorador acrescenta um atributo 'arg_set' a funcao decorada. Esse
    atributo eh um conjunto. Cada argumento passado para a funcao decorada eh
    armazenado no conjunto. Veja que o conjunto nao suporta repeticoes, entao
    se a mesma funcao for chamada com argumentos repetidos, somente um valor
    serah armazenado no conjunto. O conjunto deve armazenar valores. Caso a
    funcao seja invocada com argumentos nominais, ex.: foo(arg=42), entao
    somente o valor 42 deve ser armazenado, mas nao o nome do argumento.

    Parameters:
    func (function): A funcao que estarah sendo decorada. Nenhuma restricao se
    aplica a funcao.

    Returns:
    function: A funcao decorada com wrapper
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # TODO: implemente esse decorador. Por enquanto, ele simplesmente
        # chama a funcao decorada.
        #
        x = [a for a in args] + [b for a,b in kwargs.items()]
        wrapper.arg_set.update(x)
        return func(*args, **kwargs)
    # TODO: adicione a funcao um atributo arg_set inicializado com o valor 0:
    #
    wrapper.arg_set = set()
    return wrapper

@decorator_non_negative
def fact(n):
    """Calcula o fatorial de n.
    """
    return 1 if n == 0 else n * fact(n-1)

@decorator_hide_nums
def join_args(args, sep):
    """Produz uma string com todos os elementos na lista args concatenados.

    Parameters:
    args (list): lista de objetos que podem ser transformados em string via a
    operacao str.
    sep: a string separadora que serah interposta entre cada elemento de args.

    Returns:
    str: a string formada pela concatenacao de cada elemento em args separado
    por sep. Exemplo: join_args([1, 2, 2], "x") -> "1x2x2"
    """
    return sep.join([str(arg) for arg in args])

@num_calls_decorator
def gcd(a, b):
    """Retorna o maior divisor comum entre os numeros a e b.

    Exemplos:
    gcd(48, 30) -> 6
    gcd(30, 48) -> 6
    """
    if b == 0:
        return a
    return gcd(b,a%b)

@count_arg_values_decorator
def fib(n):
    """Retorna o n-esimo termo da cadeia de Fibonacci: 1, 1, 2, 3, 5, 8, etc.
    """
    return 1 if n < 2 else fib(n-1) + fib(n-2)

@decorator_str_to_int
def inc(a):
    """Incrementa o argumento e o retorna.
    """
    return a + 1