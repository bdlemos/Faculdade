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

class EvalVisitor(Visitor):
    """
    The EvalVisitor class evaluates logical and arithmetic expressions. The
    result of evaluating an expression is the value of that expression. The
    inherited attribute propagated throughout visits is the environment that
    associates the names of variables with values.
    
    Notice that this implementation must perform type verification. If some
    verification fail, then it invokes sys.exit with the correct error
    message. We expect two different messages:
    
    1. sys.exit("Type error")
    2. sys.exit("Def error")

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

    >>> e0 = Let('v', Add(Num(40), Num(10)), Sub(Var('v'), Num(2)))
    >>> ev = EvalVisitor()
    >>> e0.accept(ev, {})
    48
    >>> e0 = Add(Num(40), Bln(False))
    >>> ev = EvalVisitor()
    >>> e0.accept(ev, {})
    Type error
    """
    def ensure_type(self, value, expected_type, operation_name):
        if type(value) != expected_type:
            op_str = f"Type error in {operation_name}"
            ex_str = f"expected {expected_type.__name__}"
            gt_str = f"got {type(value).__name__}"
            # raise TypeError(f"{op_str}: {ex_str}, {gt_str}")
            sys.exit("Type error")

    def visit_var(self, exp, env):
        if exp.identifier in env:
            return env[exp.identifier]
        else:
            #sys.exit(f"Variavel inexistente {exp.identifier}")
            sys.exit("Def error")

    def visit_bln(self, exp, env):
        self.ensure_type(exp.bln, bool, "bln")
        return exp.bln

    def visit_num(self, exp, env):
        self.ensure_type(exp.num, int, "num")
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
    
    def visit_ifThenElse(self, exp, arg):
        cond = exp.exp_cond.accept(self, arg)
        self.ensure_type(cond, bool, "ifThenElse")
        if cond:
            return exp.exp_then.accept(self, arg)
        else:
            return exp.exp_else.accept(self, arg)