import sys
from abc import ABC, abstractmethod
from Expression import *


class Visitor(ABC):
    """
    The visitor pattern consists of two abstract classes: the Expression and the
    Visitor. The Expression class defines on method: 'accept(visitor, args)'.
    This method takes in an implementation of a visitor, and the arguments that
    are passed from expression to expression. The Visitor class defines one
    specific method for each subclass of Expression. Each instance of such a
    subclasse will invoke the right visiting method.
    """
    contador = 0
    @abstractmethod
    def visit_var(self, exp, arg):
        pass

    @abstractmethod
    def visit_bln(self, exp, arg):
        pass

    @abstractmethod
    def visit_num(self, exp, arg):
        pass

    @abstractmethod
    def visit_eql(self, exp, arg):
        pass

    @abstractmethod
    def visit_and(self, exp, arg):
        pass

    @abstractmethod
    def visit_or(self, exp, arg):
        pass

    @abstractmethod
    def visit_add(self, exp, arg):
        pass

    @abstractmethod
    def visit_sub(self, exp, arg):
        pass

    @abstractmethod
    def visit_mul(self, exp, arg):
        pass

    @abstractmethod
    def visit_div(self, exp, arg):
        pass

    @abstractmethod
    def visit_mod(self, exp, arg):
        pass

    @abstractmethod
    def visit_leq(self, exp, arg):
        pass

    @abstractmethod
    def visit_lth(self, exp, arg):
        pass

    @abstractmethod
    def visit_neg(self, exp, arg):
        pass

    @abstractmethod
    def visit_not(self, exp, arg):
        pass

    @abstractmethod
    def visit_let(self, exp, arg):
        pass

    @abstractmethod
    def visit_ifThenElse(self, exp, arg):
        pass

    @abstractmethod
    def visit_fn(self, exp, arg):
        pass

    @abstractmethod
    def visit_fun(self, exp, arg):
        pass

    @abstractmethod
    def visit_app(self, exp, arg):
        pass


class Function:
    """
    This is the class that represents functions. This class lets us distinguish
    the three types that now exist in the language: numbers, booleans and
    functions. Notice that the evaluation of an expression can now be a
    function. For instance:

        >>> f = Fn('v', Mul(Var('v'), Var('v')))
        >>> ev = EvalVisitor()
        >>> fval = f.accept(ev, {})
        >>> type(fval)
        <class 'Visitor.Function'>
    """

    def __init__(self, formal, body, env):
        self.formal = formal
        self.body = body
        self.env = env

    def __str__(self):
        return f"Fn({self.formal})"


class RecFunction(Function):
    """
    This is the class that represents named functions. The key different between
    named and anonymous functions is exactly the "name" :)

        >>> f = Fun('f', 'v', Mul(Var('v'), Var('v')))
        >>> ev = EvalVisitor()
        >>> fval = f.accept(ev, {})
        >>> type(fval)
        <class 'Visitor.RecFunction'>
    """

    def __init__(self, name, formal, body, env):
        super().__init__(formal, body, env)
        self.name = name

    def __str__(self):
        return f"Fun {self.name}({self.formal})"


class EvalVisitor(Visitor):
    """
    The EvalVisitor class evaluates logical and arithmetic expressions. The
    result of evaluating an expression is the value of that expression. The
    inherited attribute propagated throughout visits is the environment that
    associates the names of variables with values.

    Examples:
    >>> e0 = Let('v', Add(Num(40), Num(2)), Mul(Var('v'), Var('v')))
    >>> e1 = Not(Eql(e0, Num(1764)))
    >>> ev = EvalVisitor()
    >>> e1.accept(ev, {})
    False

    >>> e0 = Let('v', Add(Num(40), Num(2)), Sub(Var('v'), Num(2)))
    >>> e1 = Lth(e0, Var('x'))
    >>> ev = EvalVisitor()
    >>> e1.accept(ev, {'x': 41})
    True

    >>> e0 = Fn('v', Mul(Var('v'), Var('v')))
    >>> ev = EvalVisitor()
    >>> print(e0.accept(ev, {}))
    Fn(v)

    >>> e0 = Fn('v', Mul(Var('v'), Var('v')))
    >>> e1 = Add(Num(3), Num(4))
    >>> e2 = App(e0, e1)
    >>> ev = EvalVisitor()
    >>> print(e2.accept(ev, {}))
    49

    >>> e0 = Fun('f', 'v', Mul(Var('v'), Var('v')))
    >>> ev = EvalVisitor()
    >>> print(e0.accept(ev, {}))
    Fun f(v)

    >>> e0 = Fun('f', 'v', Mul(Var('v'), Var('v')))
    >>> e1 = Add(Num(3), Num(4))
    >>> e2 = App(e0, e1)
    >>> ev = EvalVisitor()
    >>> print(e2.accept(ev, {}))
    49
    """
    def ensure_type(self, value, expected_type, operation_name):
        # Se o valor é um booleano e o tipo esperado é int, levanta um erro
        if isinstance(value, bool) and expected_type is int:
            sys.exit("Type error")
        
        if not isinstance(value, expected_type):
            op_str = f"Type error in {operation_name}"
            ex_str = f"expected {expected_type.__name__}"
            gt_str = f"got {type(value).__name__}"
            # raise TypeError(f"{op_str}: {ex_str}, {gt_str}")
            sys.exit("Type error")

    def visit_var(self, exp, env):
        if exp.identifier in env:
            return env[exp.identifier]
        else:
            print(f"Variable {exp.identifier} not found")
            sys.exit("Def error")

    def visit_bln(self, exp, env):
        return exp.bln

    def visit_num(self, exp, env):
        return exp.num

    def visit_eql(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        try :
            self.ensure_type(left, int, "eql")
            self.ensure_type(right, int, "eql")
        except:
            try:
                self.ensure_type(left, bool, "eql")
                self.ensure_type(right, bool, "eql")
            except:
                sys.exit("Type error")
        return left == right

    def visit_and(self, exp, arg):
        e0 = exp.left.accept(self, arg)
        e1 = exp.right.accept(self, arg)
        self.ensure_type(e0, bool, "and")
        self.ensure_type(e1, bool, "and")
        return e0 and e1

    def visit_or(self, exp, arg):
        e0 = exp.left.accept(self, arg)
        e1 = exp.right.accept(self, arg)
        self.ensure_type(e0, bool, "or")
        self.ensure_type(e1, bool, "or")
        return e0 or e1

    def visit_add(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        self.ensure_type(left, int, "add")
        self.ensure_type(right, int, "add")
        return left + right

    def visit_sub(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        self.ensure_type(left, int, "sub")
        self.ensure_type(right, int, "sub")
        return left - right

    def visit_mul(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        self.ensure_type(left, int, "mul")
        self.ensure_type(right, int, "mul")
        return left * right

    def visit_div(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        self.ensure_type(left, int, "div")
        self.ensure_type(right, int, "div")

        return left // right
    def visit_mod(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        self.ensure_type(left, int, "mod")
        self.ensure_type(right, int, "mod")
        return left % right

    def visit_leq(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        self.ensure_type(left, int, "leq")
        self.ensure_type(right, int, "leq")
        return left <= right

    def visit_lth(self, exp, env):
        left = exp.left.accept(self, env)
        right = exp.right.accept(self, env)
        self.ensure_type(left, int, "lth")
        self.ensure_type(right, int, "lth")
        return left < right

    def visit_neg(self, exp, env):
        ans = exp.exp.accept(self, env)
        self.ensure_type(ans, int, "neg")
        return -ans

    def visit_not(self, exp, env):
        ans = exp.exp.accept(self, env)
        self.ensure_type(ans, bool, "not")
        return not ans

    def visit_let(self, exp, env):
        new_env = env.copy()
        new_env[exp.identifier] = exp.exp_def.accept(self, env)
        return exp.exp_body.accept(self, new_env)

    def visit_ifThenElse(self, exp, arg):
        cond = exp.cond.accept(self, arg)
        self.ensure_type(cond, bool, "ifThenElse")
        if cond:
            return exp.e0.accept(self, arg)
        else:
            return exp.e1.accept(self, arg)
        
    def visit_fn(self, exp, env):
        """
        The evaluation of a function is the function itself. Remember: in our
        language, functions are values as well. So, now we have four kinds of
        values: numbers, booleans, anonymous functions and named functions.
        """
        return Function(exp.formal, exp.body, env)

    def visit_fun(self, exp, env):
        """
        The evaluation of a named function returns a value that is the function
        itself. However, we use a different type of value: RecFunction. In this
        way, we have access to the name of the named function (and that's why
        they are called named functions :).
        """
        return RecFunction(exp.name, exp.formal, exp.body, env)

    def visit_app(self, exp, env):
        """
        Here comes most of the complexity of the homework, in five or six lines
        of code! You must implement the evaluation of a function application.
        """
        exp_fn = exp.function.accept(self, env)
        self.ensure_type(exp_fn, Function, "app")

        param = exp.actual.accept(self, env)

        new_env = exp_fn.env.copy()
        new_env[exp_fn.formal] = param

        if isinstance(exp_fn, RecFunction):
            new_env[exp_fn.name] = exp_fn

        return exp_fn.body.accept(self, new_env)