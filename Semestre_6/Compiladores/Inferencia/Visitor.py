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
        
        
class CtrGenVisitor(Visitor):
    """
    This visitor creates constraints for a type-inference engine. Basically,
    it traverses the abstract-syntax tree of expressions, producing pairs like
    (type0, type1) on the way. A pair like (type0, type1) indicates that these
    two type variables are the same.

    Examples:
        >>> e = Let('v', Num(40), Let('w', Num(2), Add(Var('v'), Var('w'))))
        >>> ev = CtrGenVisitor()
        >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
        ["('TV_1', 'TV_2')", "('TV_2', 'TV_3')", "('v', <class 'int'>)", "('w', <class 'int'>)", "(<class 'int'>, 'TV_3')", "(<class 'int'>, 'v')", "(<class 'int'>, 'w')"]
    """

    def __init__(self):
        self.fresh_type_counter = 0

    def fresh_type_var(self):
        """
        Create a new type var using the current value of the fresh_type_counter.
        Two successive calls to this method will return different type names.
        Notice that the name of a type variable is always TV_x, where x is
        some integer number. That means that probably we would run into
        errors if someone declares a variable called, say, TV_1 or TV_2, as in
        "let TV_1 <- 1 in TV_1 end". But you can assume that such would never
        happen in the test cases. In practice, we should define a new class
        to represent type variables. But let's keep the implementation as
        simple as possible.

        Example:
            >>> ev = CtrGenVisitor()
            >>> [ev.fresh_type_var(), ev.fresh_type_var()]
            ['TV_1', 'TV_2']
        """
        self.fresh_type_counter += 1
        return f"TV_{self.fresh_type_counter}"

    """
    The CtrGenVisitor class creates constraints that, once solved, will give
    us the type of the different variables. Every accept method takes in
    two arguments (in addition to self):
    
    exp: is the expression that is being analyzed.
    type_var: that is a name that works as a placeholder for the type of the
    expression. Whenever we visit a new expression, we create a type variable
    to represent its type (you can do that with the method fresh_type_var).
    The only exception is the type of Var expressions. In this case, the type
    of a Var expression is the identifier of that expression.
    """

    def visit_var(self, exp, type_var):
        """
        Example:
            >>> e = Var('v')
            >>> ev = CtrGenVisitor()
            >>> e.accept(ev, ev.fresh_type_var())
            {('v', 'TV_1')}
        """
        return {(exp.identifier, type_var)}

    def visit_bln(self, exp, type_var):
        """
        Example:
            >>> e = Bln(True)
            >>> ev = CtrGenVisitor()
            >>> e.accept(ev, ev.fresh_type_var())
            {(<class 'bool'>, 'TV_1')}
        """
        return {(type(True), type_var)}

    def visit_num(self, exp, type_var):
        """
        Example:
            >>> e = Num(1)
            >>> ev = CtrGenVisitor()
            >>> e.accept(ev, ev.fresh_type_var())
            {(<class 'int'>, 'TV_1')}
        """
        return {(type(1), type_var)}

    def visit_eql(self, exp, type_var):
        """
        Example:
            >>> e = Eql(Num(1), Bln(True))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'bool'>, 'TV_1')", "(<class 'bool'>, 'TV_2')", "(<class 'int'>, 'TV_2')"]

        Notice that if we have repeated constraints, they only appear once in
        the set of constraints (after all, it's a set!). As an example, we
        would have two occurrences of the pair (TV_2, int) in the following
        example:
            >>> e = Eql(Num(1), Num(2))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'bool'>, 'TV_1')", "(<class 'int'>, 'TV_2')"]
        """
        new_type_var = self.fresh_type_var()
        eql_left = exp.left.accept(self, new_type_var)
        eql_right = exp.right.accept(self, new_type_var)
        return eql_left | eql_right | {(type(True), type_var)}

    def visit_and(self, exp, type_var):
        """
        Example:
            >>> e = And(Bln(False), Bln(True))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'bool'>, 'TV_1')", "(<class 'bool'>, <class 'bool'>)"]

        In the above example, notice that we ended up getting a trivial
        constraint, e.g.: (<class 'bool'>, <class 'bool'>). That's alright:
        don't worry about these trivial constraints at this point. We can
        remove them from the set of constraints later on, when we try to
        solve them.
        """
        left = exp.left.accept(self, type(True))
        right = exp.right.accept(self, type(True))
        return left | right | {(type(True), type_var)}

    def visit_or(self, exp, type_var):
        """
        Example:
            >>> e = Or(Bln(False), Bln(True))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'bool'>, 'TV_1')", "(<class 'bool'>, <class 'bool'>)"]
        """
        left = exp.left.accept(self, type(True))
        right = exp.right.accept(self, type(True))
        return left | right | {(type(True), type_var)}

    def visit_add(self, exp, type_var):
        """
        Example:
            >>> e = Add(Num(1), Num(2))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'int'>, 'TV_1')", "(<class 'int'>, <class 'int'>)"]
        """
        left = exp.left.accept(self, type(1))
        right = exp.right.accept(self, type(1))
        return left | right | {(type(1), type_var)}

    def visit_sub(self, exp, type_var):
        """
        Example:
            >>> e = Sub(Num(1), Num(2))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'int'>, 'TV_1')", "(<class 'int'>, <class 'int'>)"]
        """
        left = exp.left.accept(self, type(1))
        right = exp.right.accept(self, type(1))
        return left | right | {(type(1), type_var)}

    def visit_mul(self, exp, type_var):
        """
        Example:
            >>> e = Mul(Num(1), Num(2))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'int'>, 'TV_1')", "(<class 'int'>, <class 'int'>)"]
        """
        left = exp.left.accept(self, type(1))
        right = exp.right.accept(self, type(1))
        return left | right | {(type(1), type_var)}

    def visit_div(self, exp, type_var):
        """
        Example:
            >>> e = Div(Num(1), Num(2))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'int'>, 'TV_1')", "(<class 'int'>, <class 'int'>)"]
        """
        left = exp.left.accept(self, type(1))
        right = exp.right.accept(self, type(1))
        return left | right | {(type(1), type_var)}

    def visit_leq(self, exp, type_var):
        """
        Example:
            >>> e = Leq(Num(1), Num(2))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'bool'>, 'TV_1')", "(<class 'int'>, <class 'int'>)"]
        """
        left = exp.left.accept(self, type(1))
        right = exp.right.accept(self, type(1))
        return left | right | {(type(True), type_var)}

    def visit_lth(self, exp, type_var):
        """
        Example:
            >>> e = Lth(Num(1), Num(2))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'bool'>, 'TV_1')", "(<class 'int'>, <class 'int'>)"]
        """
        left = exp.left.accept(self, type(1))
        right = exp.right.accept(self, type(1))
        return left | right | {(type(True), type_var)}

    def visit_neg(self, exp, type_var):
        """
        Example:
            >>> e = Neg(Num(1))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'int'>, 'TV_1')", "(<class 'int'>, <class 'int'>)"]
        """
        val = exp.exp.accept(self, type(1))
        return val | {(type(1), type_var)}

    def visit_not(self, exp, type_var):
        """
        Example:
            >>> e = Not(Bln(True))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["(<class 'bool'>, 'TV_1')", "(<class 'bool'>, <class 'bool'>)"]
        """
        val = exp.exp.accept(self, type(True))
        return val | {(type(True), type_var)}

    def visit_let(self, exp, type_var):
        """
        Example:
            >>> e = Let('v', Num(42), Var('v'))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["('TV_1', 'TV_2')", "('v', 'TV_2')", "(<class 'int'>, 'v')"]
        """
        e0 = exp.exp_def.accept(self, exp.identifier)
        new_type_var = self.fresh_type_var()
        e1 = exp.exp_body.accept(self, new_type_var)
        return e0 | e1 | {(type_var, new_type_var)}

    def visit_ifThenElse(self, exp, type_var):
        """
        Example:
            >>> e = IfThenElse(Bln(True), Num(42), Num(30))
            >>> ev = CtrGenVisitor()
            >>> sorted([str(ct) for ct in e.accept(ev, ev.fresh_type_var())])
            ["('TV_1', 'TV_2')", "(<class 'bool'>, <class 'bool'>)", "(<class 'int'>, 'TV_2')"]
        """
        fresh_type_var = self.fresh_type_var()
        cond = exp.exp_cond.accept(self, type(True))
        then = exp.exp_then.accept(self, fresh_type_var)
        else_ = exp.exp_else.accept(self, fresh_type_var)
        return cond | then | else_ | {(type_var, fresh_type_var)}