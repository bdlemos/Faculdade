""" Este arquivo contem a implementacao de um interpretador de instrucoes.
    Temos as seguintes instrucoes:

        const x n  | x := n ;; n eh numero inteiro
        add x a b  | x := a + b
        mul x a b  | x := a * b
        and x a b  | x := a && b
        grt x a b  | x := a > b ? 1 : 0
        bez x @    | if x == 0 goto @
        jump @     | goto @

    A titulo de exemplo, o programa abaixo calcula o fatorial de 10:

        const n 10
        const i 1
        const one 1
        const fact 1
        grt cond n i
        bez cond 9
        mul fact fact i
        add i i one
        jump 4
"""

class Instructions:
    """Uma classe para representar um programa. Um programa eh uma sequencia de
    instrucoes, mais um contador que guarda a proxima instrucao que serah
    executada.

    Essa classe nao assume nada sobre instrucoes. Assim, qualquer coisa pode
    ser passada para metodos como add_instruction. Porem, no restante deste
    trabalho, assumimos que instrucoes sao funcoes que recebem dois argumentos:
    um 'Environment', que eh uma tabela com o valor de variaveis, e uma
    instancia da classe Instruction, que eh o programa que estah sendo
    executado.

    Attributes
    ----------
    instructions : list
        uma lista de funcoes que processam instrucoes.
    pc : int
        o contador da proxima instrucao a ser executada.
    """

    def __init__(self):
        """Construtor da classe. O construtor nao recebe argumentos. Ele
        inicializa a lista de instrucoes com a lista vazia, e zera o contador
        de programas.
        """
        self.instructions = []
        self.pc = 0

    def set_next_instruction(self, new_pc):
        """Define o endereco da proxima instrucao que serah buscada.
        Normalmente, instrucoes sao executadas em sequencia: sempre que uma
        instrucao eh buscada, o contador de instrucoes eh incrementado de um.
        Porem, desvios condicionais podem alterar esse fluxo normal do programa.
        Esse metodo eh usado para permitir que tais alteracoes possam ocorrer.

        Parameters
        ----------
        new_pc : int
            o novo contador de programas. Note que desvios sao absolutos, nao
            relativos. Assim, a proxima instrucao a ser buscada serah a
            instrucao armazenada na posicao new_pc da lista de instrucoes.
        """
        assert isinstance(new_pc, int), 'Contador de programa deve ser int'
        self.pc = new_pc

    def get_next_instruction(self):
        """Busca a proxima instrucao que deve ser executada. Sempre que uma
        instrucao eh buscada, o contador de programas eh incrementado de uma
        unidade. Assim, instrucoes sao buscadas sempre em sequencia. Caso o
        contador esteja fora do limite de instrucoes existentes, o valor None
        eh retornado em vez de uma instrucao.

        Returns
        -------
            A proxima instrucao a ser executada, ou None caso o contador seja
            maior que o numero de instrucoes armazenadas no programa, ou menor
            que zero.
        """
        if self.pc < len(self.instructions) and self.pc >= 0:
            next_instruction = self.instructions[self.pc]
            self.pc += 1
            return next_instruction
        else:
            return None

    def add_instruction(self, instruction):
        """Insere uma instrucao ao final da lista de instrucoes no programa.

        Parameters
        ----------
        instruction : function
            a instrucao que serah inserida ao final da lista de instrucoes.
        """
        self.instructions.append(instruction)

    def __str__(self):
        """Retorna uma string representando a lista de instrucoes no programa.

        Returns
        -------
            Um valor string. Ex.: "const a 1\nconst b 2\nadd c a b\n".
        """
        return "\n".join([inst.str for inst in self.instructions])

def make_const(lhs, val):
    """Cria uma instrucao que carrega uma variavel com um valor inteiro.
    Por exemplo, o programa abaixo, comecando com um environment vazio, termina
    com o environment {"a": 1, "b": 2}

    const a 1
    const b 2

    Parameters
    ----------
    lhs : str
        o lado esquerdo da atribuicao, ex.: lhs := 5

    val : str
        o lado direito da atribuicao, ex.: x := val. Note que val eh uma string.
        Essa string precisa ser transformada em um numero inteiro antes de ser
        usada para atualizar o valor associado a lhs no environment.

    Returns
    -------
        Um closure que atualiza env com o par {"lhs": val}. Esse closure
        nao faz nada com a lista de instrucoes.
    """
    def eval(env, instructions):
        """
        O closure que interpreta a instrucao no environment env sendo
        instructions a lista que compoe o programa em execucao.

        Parameters
        ----------
        env : dict
            O environment no qual a instrucao serah avaliada. Um environment eh
            um dictionario que associa nomes de variaveis aos valores que essas
            variaveis guardam.
 
        instructions : list
            A lista de instrucoes que compoem o programa em execucao.
        """
        # TODO: implemente este metodo que retorna a instrucao.
        env[lhs] = int(val)
    # A representacao string desta instrucao:
    #
    eval.str = "%s := %s" % (lhs, val)
    return eval

def make_add(lhs, op0, op1):
    """Cria uma instrucao que adiciona duas variaveis e coloca o valor em uma
    terceira variavel.
    Por exemplo, o programa abaixo, comecando com o environment {"a": 1, "b": 2}
    termina com o environment {"a": 1, "b": 2, "c": 3}

    add c a b

    Parameters
    ----------
    lhs : str
        o lado esquerdo da atribuicao, ex.: lhs := a + b

    op0 : str
        o primeiro operando da soma, ex.: x := op0 + b

    op1 : str
        o segundo operando da soma, ex.: x := a + op1

    Returns
    -------
        Um closure que atualiza env com o par {"lhs": val}. Esse closure
        nao faz nada com a lista de instrucoes.
    """
    def eval(env, instructions):
        """Este closure faz quatro acoes:
            1. Le o valor de op0 em env;
            2. Le o valor de op1 em env;
            3. Soma os valores lidos em (1) e (2);
            4. Atualiza env[lhs] com o valor lido em (3).
        """
        # TODO: implemente este metodo que retorna a instrucao.
        env[lhs] = env[op0] + env[op1]

    # A representacao string desta instrucao:
    #
    eval.str = "%s := %s + %s" % (lhs, op0, op1)
    return eval

def make_mul(lhs, op0, op1):
    """Cria uma instrucao que multiplica duas variaveis e coloca o valor em uma
    terceira variavel.
    Por exemplo, o programa abaixo, comecando com o environment {"a": 3, "b": 2}
    termina com o environment {"a": 3, "b": 2, "c": 6}

    mul c a b

    Parameters
    ----------
    lhs : str
        o lado esquerdo da atribuicao, ex.: lhs := a * b

    op0 : str
        o primeiro operando da multiplicacao, ex.: x := op0 * b

    op1 : str
        o segundo operando da multiplicacao, ex.: x := a * op1

    Returns
    -------
        Um closure que atualiza env com o par {"lhs": val}. Esse closure
        nao faz nada com a lista de instrucoes.
    """
    def eval(env, instructions):
        """Este closure eh muito similar aquele retornado por make_add, exceto
        que a operacao implementada eh multiplicacao em vez de adicao.
        """
        # TODO: implemente este metodo que retorna a instrucao.
        env[lhs] = env[op0] * env[op1]
    # A representacao string desta instrucao:
    #
    eval.str = "%s := %s * %s" % (lhs, op0, op1)
    return eval

def make_and(lhs, op0, op1):
    """Cria uma instrucao que faz a conjuncao logica (AND) de dois operandos e
    coloca o resultado na variavel lhs. O AND logico funciona seguindo essa
    tabela verdade, em que X eh qualquer valor diferente de zero:

        0 AND 0 eh 0
        0 AND X eh 0
        X AND 0 eh 0
        X AND X eh 1

    Por exemplo, o programa abaixo, comecando com o environment {"a": 3, "b": 0}
    termina com o environment {"a": 3, "b": 0, "c": 0}

    and c a b

    Parameters
    ----------
    lhs : str
        o lado esquerdo da atribuicao, ex.: lhs := a AND b

    op0 : str
        o primeiro operando da conjuncao, ex.: x := op0 AND b

    op1 : str
        o segundo operando da conjuncao, ex.: x := a AND op1

    Returns
    -------
        Um closure que atualiza env com o par {"lhs": val}. Esse closure
        nao faz nada com a lista de instrucoes.
    """
    def eval(env, instructions):
        """Este closure eh muito similar aquele retornado por make_add, exceto
        que a operacao implementada eh multiplicacao em vez de adicao.
        """
        # TODO: implemente este metodo que retorna a instrucao.
        env[lhs] = 1 if env[op0] and env[op1] else 0
    # A representacao string desta instrucao:
    #
    eval.str = "%s := %s and %s" % (lhs, op0, op1)
    return eval

def make_grt(lhs, op0, op1):
    """Cria uma instrucao que compara duas variaveis. Se a primeira for maior
    que a segunda, entao essa instrucao coloca o valor 1 em lhs; senao, a
    instrucao coloca o valor 0 em lhs.
    Por exemplo, o programa abaixo, comecando com o environment {"a": 3, "b": 2}
    termina com o environment {"a": 3, "b": 2, "cond": 1}

    grt cond a b

    Parameters
    ----------
    lhs : str
        variavel que guardarah o resultado da comparacao, ex.: lhs := a > b

    op0 : str
        o primeiro operando da comparacao, ex.: x := op0 > b

    op1 : str
        o segundo operando da comaparacao, ex.: x := a > op1

    Returns
    -------
        Um closure que atualiza env com o par {"lhs": val}. Esse closure
        nao faz nada com a lista de instrucoes.
    """
    def eval(env, instructions):
        """Este closure faz quatro acoes:
            1. Le o valor de op0 em env;
            2. Le o valor de op1 em env;
            3. Se op0 > op1, entao: coloca 1 em env[lhs]
            4. senao (se op0 <= op1), entao: coloca 0 em env[lhs].
        """
        # TODO: implemente este metodo que retorna a instrucao.
        env[lhs] = 1 if env[op0] > env[op1] else 0
    # A representacao string desta instrucao:
    #
    eval.str = "%s := if %s greater than %s then 1 else 0" % (lhs, op0, op1)
    return eval

def make_bez(pred, goto_address):
    """Cria uma instrucao que implementa um desvio condicional. Se o valor
    armazenado em pred for zero, entao a instrucao atualiza a proxima instrucao
    da lista de instrucoes com o endereco goto_address.

    Note que tanto o environment que contem o valor de pred quanto a sequencia
    de instrucoes que serah atualizada sao parametros do closure que make_bez
    retorna. A proposito, bez significa 'branch if equal zero'.

    Parameters
    ----------
    pred : str
        variavel que determina se o desvio acontece ou nao.

    goto_address : str
        o endereco da proxima instrucao a ser buscada. Note que goto_address eh
        uma string, nao um inteiro. Entao, goto_address precisa ser
        transformada em um inteiro antes de ser usada para atualizar o contado
        de programas.

    Returns
    -------
        Um closure que atualiza atualiza a lista de instrucoes a ser buscada.
    """
    def eval(env, instructions):
        """Este closure realiza as seguintes acoes:
            1. Le o valor de pred em env;
            2. Se o valor lido em (1) for igual a zero, entao:
            3. chama set_next_instruction em instructions com goto_address.

            Note que nao eh necessario fazer nada se o valor de pred nao for
            zero. Nesse caso, a proxima instrucao em instructions serah,
            naturalmente, a instrucao em sequencia a partir do ultimo contador
            de programas usado.
        """
        # TODO: implemente este metodo que retorna a instrucao.
        if not env[pred]:
            instructions.set_next_instruction(int(goto_address))
    # A representacao string desta instrucao:
    #
    eval.str = "if %s == 0 goto %s" % (pred, goto_address)
    return eval

def make_jump(goto_address):
    """Cria uma instrucao que implementa um desvio incondicional. Essa instrucao
    atualiza a proxima instrucao da lista de instrucoes com o endereco
    goto_address. A atualizacao sempre ocorre.

    Parameters
    ----------
    goto_address : str
        o endereco da proxima instrucao a ser buscada. Note que goto_address eh
        uma string, nao um inteiro. Entao, goto_address precisa ser
        transformada em um inteiro antes de ser usada para atualizar o contado
        de programas.

    Returns
    -------
        Um closure que atualiza atualiza a lista de instrucoes a ser buscada.
    """
    def eval(env, instructions):
        """Este closure chama set_next_instruction em instructions, passando
        goto_address como parametro. Veja que o environment env nao eh usado
        para nada nesta instrucao.
        """
        # TODO: implemente este metodo que retorna a instrucao.
        instructions.set_next_instruction(int(goto_address))
    # A representacao string desta instrucao:
    #
    eval.str = "jump %s" % goto_address
    return eval