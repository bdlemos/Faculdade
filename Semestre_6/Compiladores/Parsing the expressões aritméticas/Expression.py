from abc import ABC, abstractmethod

class Expression(ABC):
    @abstractmethod
    def eval(self):
        raise NotImplementedError

class Bln(Expression):
    """
    This class represents expressions that are boolean values. There are only
    two boolean values: true and false. The evaluation of such an expression is
    the boolean itself.
    """
    def __init__(self, bln):
        self.bln = bln
    def eval(self):
        """
        Example:
        >>> e = Bln(True)
        >>> e.eval()
        True
        """
        # TODO: Implement this method!
        return self.bln
    def __str__(self):
        return str(self.bln)

class Num(Expression):
    """
    This class represents expressions that are numbers. The evaluation of such
    an expression is the number itself.
    """
    def __init__(self, num):
        self.num = num
    def eval(self):
        """
        Example:
        >>> e = Num(3)
        >>> e.eval()
        3
        """
        # TODO: Implement this method!
        return self.num
    def __str__(self):
        return str(self.num)

class BinaryExpression(Expression):
    """
    This class represents binary expressions. A binary expression has two
    sub-expressions: the left operand and the right operand.
    """
    def __init__(self, left, right):
        if not isinstance(left, Expression):
            raise ValueError("left operand is not an expression")
        if not isinstance(right, Expression):
            raise ValueError("right operand is not an expression")
        self.left = left
        self.right = right

    @abstractmethod
    def eval(self):
        raise None
    
class Eql(BinaryExpression):
    """
    This class represents the equality between two expressions. The evaluation
    of such an expression is True if the subexpressions are the same, or false
    otherwise.
    """
    def eval(self):
        """
        Example:
        >>> n1 = Num(3)
        >>> n2 = Num(4)
        >>> e = Eql(n1, n2)
        >>> e.eval()
        False

        >>> n1 = Num(3)
        >>> n2 = Num(3)
        >>> e = Eql(n1, n2)
        >>> e.eval()
        True
        """
        # TODO: Implement this method!
        return self.left.eval() == self.right.eval()
    def __str__(self):
        return "=="

class Add(BinaryExpression):
    """
    This class represents addition of two expressions. The evaluation of such
    an expression is the addition of the two subexpression's values.
    """
    def eval(self):
        """
        Example:
        >>> n1 = Num(3)
        >>> n2 = Num(4)
        >>> e = Add(n1, n2)
        >>> e.eval()
        7
        """
        return self.left.eval() + self.right.eval()
    
    def __str__(self):
        return "+"

class Sub(BinaryExpression):
    """
    This class represents subtraction of two expressions. The evaluation of such
    an expression is the subtraction of the two subexpression's values.
    """
    def eval(self):
        """
        Example:
        >>> n1 = Num(3)
        >>> n2 = Num(4)
        >>> e = Sub(n1, n2)
        >>> e.eval()
        -1
        """
        return self.left.eval() - self.right.eval()
    
    def __str__(self):
        return "-"

class Mul(BinaryExpression):
    """
    This class represents multiplication of two expressions. The evaluation of
    such an expression is the product of the two subexpression's values.
    """
    def eval(self):
        """
        Example:
        >>> n1 = Num(3)
        >>> n2 = Num(4)
        >>> e = Mul(n1, n2)
        >>> e.eval()
        12
        """
        return self.left.eval() * self.right.eval()
    
    def __str__(self):
        return "*"

class Div(BinaryExpression):
    """
    This class represents the integer division of two expressions. The
    evaluation of such an expression is the integer quocient of the two
    subexpression's values.
    """
    def eval(self):
        """
        Example:
        >>> n1 = Num(28)
        >>> n2 = Num(4)
        >>> e = Div(n1, n2)
        >>> e.eval()
        7
        >>> n1 = Num(22)
        >>> n2 = Num(4)
        >>> e = Div(n1, n2)
        >>> e.eval()
        5
        """
        return self.left.eval() // self.right.eval()
    def __str__(self):
        return "/"

class Leq(BinaryExpression):
    """
    This class represents comparison of two expressions using the
    less-than-or-equal comparator. The evaluation of such an expression is a
    boolean value that is true if the left operand is less than or equal the
    right operand. It is false otherwise.
    """
    def eval(self):
        """
        Example:
        >>> n1 = Num(3)
        >>> n2 = Num(4)
        >>> e = Leq(n1, n2)
        >>> e.eval()
        True
        >>> n1 = Num(3)
        >>> n2 = Num(3)
        >>> e = Leq(n1, n2)
        >>> e.eval()
        True
        >>> n1 = Num(4)
        >>> n2 = Num(3)
        >>> e = Leq(n1, n2)
        >>> e.eval()
        False
        """
        return self.left.eval() <= self.right.eval()
    
    def __str__(self):
        return "<="

class Lth(BinaryExpression):
    """
    This class represents comparison of two expressions using the
    less-than comparison operator. The evaluation of such an expression is a
    boolean value that is true if the left operand is less than the right
    operand. It is false otherwise.
    """
    def eval(self):
        """
        Example:
        >>> n1 = Num(3)
        >>> n2 = Num(4)
        >>> e = Lth(n1, n2)
        >>> e.eval()
        True
        >>> n1 = Num(3)
        >>> n2 = Num(3)
        >>> e = Lth(n1, n2)
        >>> e.eval()
        False
        >>> n1 = Num(4)
        >>> n2 = Num(3)
        >>> e = Lth(n1, n2)
        >>> e.eval()
        False
        """

        return self.left.eval() < self.right.eval()
    
    def __str__(self):
        return "<"

class UnaryExpression(Expression):
    """
    This class represents unary expressions. A unary expression has only one
    sub-expression.
    """
    def __init__(self, exp):
        if not isinstance(exp, Expression):
            raise ValueError("operand is not an expression")

        self.exp = exp

    @abstractmethod
    def eval(self):
        raise NotImplementedError

class Neg(UnaryExpression):
    """
    This expression represents the additive inverse of a number. The additive
    inverse of a number n is the number -n, so that the sum of both is zero.
    """
    def eval(self):
        """
        Example:
        >>> n = Num(3)
        >>> e = Neg(n)
        >>> e.eval()
        -3
        >>> n = Num(0)
        >>> e = Neg(n)
        >>> e.eval()
        0
        """
        return -self.exp.eval()
    
    def __str__(self):
        return "-"

class Not(UnaryExpression):
    """
    This expression represents the negation of a boolean. The negation of a
    boolean expression is the logical complement of that expression.
    """
    def eval(self):
        """
        Example:
        >>> t = Bln(True)
        >>> e = Not(t)
        >>> e.eval()
        False
        >>> t = Bln(False)
        >>> e = Not(t)
        >>> e.eval()
        True
        """
        return not self.exp.eval()
    def __str__(self):
        return "not"
    
def print_prefix(exp):
    """
    Evaluate an arithmetic expression.

    Examples:
    >>> n1 = Num(28)
    >>> n2 = Num(4)
    >>> e0 = Div(n1, n2)
    >>> n3 = Num(5)
    >>> e1 = Mul(e0, n3)
    >>> f"{print_prefix(e1)} = {e1.eval()}"
    '* / 28 4 5 = 35'

    >>> n1 = Num(28)
    >>> n2 = Num(4)
    >>> e0 = Div(n1, n2)
    >>> n3 = Num(50)
    >>> e1 = Div(n3, e0)
    >>> e2 = Mul(e1, e0)
    >>> f"{print_prefix(e2)} = {e2.eval()}"
    '* / 50 / 28 4 / 28 4 = 49'
    """
    s = str(exp)
    if isinstance(exp, BinaryExpression):
        s = f"{s} {print_prefix(exp.left)} {print_prefix(exp.right)}"
    return s


def print_infix(exp):
    """
    Evaluate an arithmetic expression.

    Examples:
    >>> n1 = Num(28)
    >>> n2 = Num(4)
    >>> e0 = Div(n1, n2)
    >>> n3 = Num(5)
    >>> e1 = Mul(e0, n3)
    >>> f"{print_infix(e1)} = {e1.eval()}"
    '((28) / (4)) * (5) = 35'

    >>> n1 = Num(28)
    >>> n2 = Num(4)
    >>> e0 = Div(n1, n2)
    >>> n3 = Num(50)
    >>> e1 = Div(n3, e0)
    >>> e2 = Mul(e1, e0)
    >>> f"{print_infix(e2)} = {e2.eval()}"
    '((50) / ((28) / (4))) * ((28) / (4)) = 49'
    """
    s = str(exp)
    if isinstance(exp, BinaryExpression):
        s = f"({print_infix(exp.left)}) {s} ({print_infix(exp.right)})"
    return s


def print_postfix(exp):
    """
    Evaluate an arithmetic expression.

    Examples:
    >>> n1 = Num(28)
    >>> n2 = Num(4)
    >>> e0 = Div(n1, n2)
    >>> n3 = Num(5)
    >>> e1 = Mul(e0, n3)
    >>> f"{print_postfix(e1)} = {e1.eval()}"
    '28 4 / 5 * = 35'

    >>> n1 = Num(28)
    >>> n2 = Num(4)
    >>> e0 = Div(n1, n2)
    >>> n3 = Num(50)
    >>> e1 = Div(n3, e0)
    >>> e2 = Mul(e1, e0)
    >>> f"{print_postfix(e2)} = {e2.eval()}"
    '50 28 4 / / 28 4 / * = 49'
    """
    s = str(exp)
    if isinstance(exp, BinaryExpression):
        s = f"{print_postfix(exp.left)} {print_postfix(exp.right)} {s}"
    return s
