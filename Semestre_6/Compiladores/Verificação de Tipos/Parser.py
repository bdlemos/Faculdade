import sys

from Expression import *
from Lexer import Token, TokenType

"""
This file implements a parser for SML with anonymous functions and type
annotations. The grammar is as follows:

fn_exp  ::= fn <var>: types => fn_exp
          | if_exp
if_exp  ::= <if> if_exp <then> fn_exp <else> fn_exp
          | or_exp
or_exp  ::= and_exp (or and_exp)*
and_exp ::= eq_exp (and eq_exp)*
eq_exp  ::= cmp_exp (= cmp_exp)*
cmp_exp ::= add_exp ([<=|<] add_exp)*
add_exp ::= mul_exp ([+|-] mul_exp)*
mul_exp ::= unary_exp ([*|/] unary_exp)*
unary_exp ::= <not> unary_exp
             | ~ unary_exp
             | let_exp
let_exp ::= <let> <var>: types <- fn_exp <in> fn_exp <end>
          | val_exp
val_exp ::= val_tk (val_tk)*
val_tk ::= <var> | ( fn_exp ) | <num> | <true> | <false>

types ::= type -> types | type

type ::= int | bool | ( types )

References:
    see https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm#classic
"""

class Parser:
    def __init__(self, tokens):
        """
        Initializes the parser. The parser keeps track of the list of tokens
        and the current token. For instance:
        """
        self.tokens = list(tokens)
        self.cur_token_idx = 0 # This is just a suggestion!
        self.operators = {
            TokenType.ADD: Add,
            TokenType.SUB: Sub,
            TokenType.MUL: Mul,
            TokenType.DIV: Div,
            TokenType.LEQ: Leq,
            TokenType.LTH: Lth,
            TokenType.EQL: Eql,
            TokenType.NOT: Not,
            TokenType.NEG: Neg,
            TokenType.AND: And,
            TokenType.ORX: Or,
            TokenType.IFX: IfThenElse
        }


    def cur_token(self):
        if self.cur_token_idx < len(self.tokens):
            return self.tokens[self.cur_token_idx]
        return None


    def consume_token(self, expected_type):
        token = self.cur_token()
        if token.kind != expected_type:
            raise SyntaxError(f"Esperado {expected_type}, mas encontrado {token.kind}")
        self.cur_token_idx += 1

    def parse(self):
        """
        Returns the expression associated with the stream of tokens.

        Examples:
        >>> parser = Parser([Token('123', TokenType.NUM)])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> parser = Parser([Token('True', TokenType.TRU)])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> parser = Parser([Token('False', TokenType.FLS)])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> tk0 = Token('~', TokenType.NEG)
        >>> tk1 = Token('123', TokenType.NUM)
        >>> parser = Parser([tk0, tk1])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('~', TokenType.NEG)
        >>> tk3 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('/', TokenType.DIV)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('+', TokenType.ADD)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('-', TokenType.SUB)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('2', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('(', TokenType.LPR)
        >>> tk3 = Token('3', TokenType.NUM)
        >>> tk4 = Token('+', TokenType.ADD)
        >>> tk5 = Token('4', TokenType.NUM)
        >>> tk6 = Token(')', TokenType.RPR)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('==', TokenType.EQL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<=', TokenType.LEQ)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<', TokenType.LTH)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> tk0 = Token('not', TokenType.NOT)
        >>> tk1 = Token('(', TokenType.LPR)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> tk3 = Token('<', TokenType.LTH)
        >>> tk4 = Token('4', TokenType.NUM)
        >>> tk5 = Token(')', TokenType.RPR)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> tk0 = Token('true', TokenType.TRU)
        >>> tk1 = Token('or', TokenType.ORX)
        >>> tk2 = Token('false', TokenType.FLS)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> tk0 = Token('true', TokenType.TRU)
        >>> tk1 = Token('and', TokenType.AND)
        >>> tk2 = Token('false', TokenType.FLS)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'bool'>

        >>> t0 = Token('let', TokenType.LET)
        >>> t1 = Token('v', TokenType.VAR)
        >>> t2 = Token(':', TokenType.COL)
        >>> t3 = Token('int', TokenType.INT)
        >>> t4 = Token('<-', TokenType.ASN)
        >>> t5 = Token('42', TokenType.NUM)
        >>> t6 = Token('in', TokenType.INX)
        >>> t7 = Token('v', TokenType.VAR)
        >>> t8 = Token('end', TokenType.END)
        >>> parser = Parser([t0, t1, t2, t3, t4, t5, t6, t7, t8])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, {})
        <class 'int'>

        >>> t0 = Token('let', TokenType.LET)
        >>> t1 = Token('v', TokenType.VAR)
        >>> t2 = Token(':', TokenType.COL)
        >>> t3 = Token('int', TokenType.INT)
        >>> t4 = Token('<-', TokenType.ASN)
        >>> t5 = Token('21', TokenType.NUM)
        >>> t6 = Token('in', TokenType.INX)
        >>> t7 = Token('v', TokenType.VAR)
        >>> t8 = Token('+', TokenType.ADD)
        >>> t9 = Token('v', TokenType.VAR)
        >>> tA = Token('end', TokenType.END)
        >>> parser = Parser([t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, tA])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, {})
        <class 'int'>

        >>> tk0 = Token('if', TokenType.IFX)
        >>> tk1 = Token('2', TokenType.NUM)
        >>> tk2 = Token('<', TokenType.LTH)
        >>> tk3 = Token('3', TokenType.NUM)
        >>> tk4 = Token('then', TokenType.THN)
        >>> tk5 = Token('1', TokenType.NUM)
        >>> tk6 = Token('else', TokenType.ELS)
        >>> tk7 = Token('2', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('if', TokenType.IFX)
        >>> tk1 = Token('false', TokenType.FLS)
        >>> tk2 = Token('then', TokenType.THN)
        >>> tk3 = Token('1', TokenType.NUM)
        >>> tk4 = Token('else', TokenType.ELS)
        >>> tk5 = Token('2', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, None)
        <class 'int'>

        >>> tk0 = Token('fn', TokenType.FNX)
        >>> tk1 = Token('v', TokenType.VAR)
        >>> tk2 = Token(':', TokenType.COL)
        >>> tk3 = Token('int', TokenType.INT)
        >>> tk4 = Token('=>', TokenType.ARW)
        >>> tk5 = Token('v', TokenType.VAR)
        >>> tk6 = Token('+', TokenType.ADD)
        >>> tk7 = Token('1', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> print(exp.accept(ev, {}))
        <class 'int'> -> <class 'int'>

        >>> t0 = Token('(', TokenType.LPR)
        >>> t1 = Token('fn', TokenType.FNX)
        >>> t2 = Token('v', TokenType.VAR)
        >>> t3 = Token(':', TokenType.COL)
        >>> t4 = Token('int', TokenType.INT)
        >>> t5 = Token('=>', TokenType.ARW)
        >>> t6 = Token('v', TokenType.VAR)
        >>> t7 = Token('+', TokenType.ADD)
        >>> t8 = Token('1', TokenType.NUM)
        >>> t9 = Token(')', TokenType.RPR)
        >>> tA = Token('2', TokenType.NUM)
        >>> parser = Parser([t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, tA])
        >>> exp = parser.parse()
        >>> ev = TypeCheckVisitor()
        >>> exp.accept(ev, {})
        <class 'int'>
        """
        return self.fn_exp()
    
    def fn_exp(self):
        if self.cur_token().kind == TokenType.FNX:
            self.consume_token(TokenType.FNX)
            var = self.cur_token().text
            self.consume_token(TokenType.VAR)
            self.consume_token(TokenType.COL)
            t = self.types()
            self.consume_token(TokenType.ARW)
            body = self.fn_exp()
            return Fn(var, t, body)
        return self.if_exp()
    def if_exp(self):
        if self.cur_token().kind == TokenType.IFX:
            self.consume_token(TokenType.IFX)
            cond = self.if_exp()
            self.consume_token(TokenType.THN)
            then = self.fn_exp()
            self.consume_token(TokenType.ELS)
            els = self.fn_exp()
            return IfThenElse(cond, then, els)
        return self.or_exp()

    def or_exp(self):
        left = self.and_exp()
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind == TokenType.ORX:
            self.consume_token(TokenType.ORX)
            right = self.and_exp()
            left = Or(left, right)
        return left

    def and_exp(self):
        left = self.eq_exp()
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind == TokenType.AND:
            self.consume_token(TokenType.AND)
            right = self.eq_exp()
            left = And(left, right)
        return left

    def eq_exp(self):
        left = self.cmp_exp()
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind == TokenType.EQL:
            self.consume_token(TokenType.EQL)
            right = self.cmp_exp()
            left = Eql(left, right)
        return left
    
    def cmp_exp(self):
        left = self.add_exp()
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind in [TokenType.LTH, TokenType.LEQ]:
            kind = self.cur_token().kind
            self.consume_token(kind)
            right = self.add_exp()
            left = Lth(left, right) if kind == TokenType.LTH else Leq(left, right)
        return left

    def add_exp(self):
        left = self.mul_exp()
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind in [TokenType.ADD, TokenType.SUB]:
            kind = self.cur_token().kind
            self.consume_token(kind)
            right = self.mul_exp()
            left = Add(left, right) if kind == TokenType.ADD else Sub(left, right)
        return left

    def mul_exp(self):
        left = self.uny_exp()
        #print(left)
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind in [TokenType.MUL, TokenType.DIV]:
            kind = self.cur_token().kind
            self.consume_token(kind)
            right = self.uny_exp()
            left = Mul(left, right) if kind == TokenType.MUL else Div(left, right)
        return left

    def uny_exp(self):
        if self.cur_token().kind == TokenType.NOT:
            self.consume_token(TokenType.NOT)
            return Not(self.uny_exp())
        if self.cur_token().kind == TokenType.NEG:
            self.consume_token(TokenType.NEG)
            return Neg(self.uny_exp())
        return self.let_exp()

    def let_exp(self):
        if self.cur_token().kind == TokenType.LET:
            self.consume_token(TokenType.LET)
            var = self.cur_token().text
            self.consume_token(TokenType.VAR)
            self.consume_token(TokenType.COL)
            type = self.types()
            self.consume_token(TokenType.ASN)
            expr = self.fn_exp()
            self.consume_token(TokenType.INX)
            body = self.fn_exp()
            self.consume_token(TokenType.END)
            return Let(var, type, expr, body)
        return self.val_exp()
    
    def val_exp(self):
        expr = self.val_tk()
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind in [TokenType.VAR, TokenType.LPR, TokenType.NUM, TokenType.TRU, TokenType.FLS]:
            expr = App(expr, self.val_tk())
        return expr
    
    def val_tk(self):
        token = self.cur_token()
        if token.kind == TokenType.VAR:
            self.consume_token(TokenType.VAR)
            return Var(token.text)
        if token.kind == TokenType.LPR:
            self.consume_token(TokenType.LPR)
            expr = self.fn_exp()
            self.consume_token(TokenType.RPR)
            return expr
        if token.kind == TokenType.NUM:
            self.consume_token(TokenType.NUM)
            return Num(int(token.text))
        if token.kind == TokenType.TRU:
            self.consume_token(TokenType.TRU)
            return Bln(True)
        if token.kind == TokenType.FLS:
            self.consume_token(TokenType.FLS)
            return Bln(False)

        sys.exit("Parse error")

    def types(self):
        t = self.parse_type()
        if self.cur_token().kind == TokenType.TPF:
            self.consume_token(TokenType.TPF)
            t = ArrowType(t, self.types())
            return t
        return t

    def parse_type(self):
        if self.cur_token().kind == TokenType.INT:
            self.consume_token(TokenType.INT)
            return type(1)
        if self.cur_token().kind == TokenType.LGC:
            self.consume_token(TokenType.LGC)
            return type(True)
        if self.cur_token().kind == TokenType.LPR:
            self.consume_token(TokenType.LPR)
            parsed_type = self.types()
            self.consume_token(TokenType.RPR)
            return parsed_type
        sys.exit("Parse error")

class ArrowType:
    """
    This is the class that represents function types. A function type is just
    that: the type of a function. Function types are also called "arrow types",
    because they tend to be represented as 't0 -> t1'. Thus, an arrow type
    has two parts: the head type (t0) and the tail type (t1).

    Usage:
        >>> t = ArrowType(type(1), type(True))
        >>> t.hd == type(1) and t.tl == type(True)
        True

        >>> t = ArrowType(type(1), type(True))
        >>> str(t)
        "<class 'int'> -> <class 'bool'>"
    """

    def __init__(self, tp_formal, tp_body):
        self.hd = tp_formal
        self.tl = tp_body

    def __eq__(self, other):
        """
        Two arrow types are equal if their head and tail are equal.
        Example:
            >>> t0 = ArrowType(type(1), ArrowType(type(1), type(1)))
            >>> t1 = ArrowType(type(1), ArrowType(type(1), type(1)))
            >>> t0 == t1
            True
        """
        if isinstance(other, ArrowType):
            return self.hd == other.hd and self.tl == other.tl
        else:
            return False

    def __repr__(self):
        if isinstance(self.hd, ArrowType):
            hd_str = f"( {str(self.hd)} )"
        else:
            hd_str = str(self.hd)
        if isinstance(self.tl, ArrowType):
            tl_str = f"( {str(self.tl)} )"
        else:
            tl_str = str(self.tl)
        return f"{hd_str} -> {tl_str}"