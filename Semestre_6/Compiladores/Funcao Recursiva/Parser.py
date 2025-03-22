import sys

from Expression import *
from Lexer import Token, TokenType

"""
This file implements a parser for SML with anonymous functions. The grammar is
as follows:

fn_exp  ::= fn <var> => fn_exp
          | if_exp
if_exp  ::= <if> if_exp <then> fn_exp <else> fn_exp
          | or_exp
or_exp  ::= and_exp (or and_exp)*
and_exp ::= eq_exp (and eq_exp)*
eq_exp  ::= cmp_exp (= cmp_exp)*
cmp_exp ::= add_exp ([<=|<] add_exp)*
add_exp ::= mul_exp ([+|-] mul_exp)*
mul_exp ::= uny_exp ([*|div|mod] uny_exp)*
uny_exp ::= <not> uny_exp
          | ~ uny_exp
          | let_exp
let_exp ::= <let> decl <in> fn_exp <end>
          | val_exp
val_exp ::= val_tk (val_tk)*
val_tk  ::= <var> | ( fn_exp ) | <num> | <true> | <false>

decl    ::= val <var> = fn_exp
          | fun <var> <var> = fn_exp

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
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        123

        >>> parser = Parser([Token('True', TokenType.TRU)])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> parser = Parser([Token('False', TokenType.FLS)])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        False

        >>> tk0 = Token('~', TokenType.NEG)
        >>> tk1 = Token('123', TokenType.NUM)
        >>> parser = Parser([tk0, tk1])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        -123

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        12

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('~', TokenType.NEG)
        >>> tk3 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        -12

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('div', TokenType.DIV)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        7

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('+', TokenType.ADD)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        7

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('-', TokenType.SUB)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        26

        >>> tk0 = Token('2', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('(', TokenType.LPR)
        >>> tk3 = Token('3', TokenType.NUM)
        >>> tk4 = Token('+', TokenType.ADD)
        >>> tk5 = Token('4', TokenType.NUM)
        >>> tk6 = Token(')', TokenType.RPR)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        14

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('==', TokenType.EQL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<=', TokenType.LEQ)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<', TokenType.LTH)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        False

        >>> tk0 = Token('not', TokenType.NOT)
        >>> tk1 = Token('(', TokenType.LPR)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> tk3 = Token('<', TokenType.LTH)
        >>> tk4 = Token('4', TokenType.NUM)
        >>> tk5 = Token(')', TokenType.RPR)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('true', TokenType.TRU)
        >>> tk1 = Token('or', TokenType.ORX)
        >>> tk2 = Token('false', TokenType.FLS)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        True

        >>> tk0 = Token('true', TokenType.TRU)
        >>> tk1 = Token('and', TokenType.AND)
        >>> tk2 = Token('false', TokenType.FLS)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        False

        >>> tk0 = Token('let', TokenType.LET)
        >>> tk1 = Token('val', TokenType.VAL)
        >>> tk2 = Token('v', TokenType.VAR)
        >>> tk3 = Token('=', TokenType.EQL)
        >>> tk4 = Token('42', TokenType.NUM)
        >>> tk5 = Token('in', TokenType.INX)
        >>> tk6 = Token('v', TokenType.VAR)
        >>> tk7 = Token('end', TokenType.END)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, {})
        42

        >>> tk0 = Token('let', TokenType.LET)
        >>> tk1 = Token('val', TokenType.VAL)
        >>> tk2 = Token('v', TokenType.VAR)
        >>> tk3 = Token('=', TokenType.EQL)
        >>> tk4 = Token('21', TokenType.NUM)
        >>> tk5 = Token('in', TokenType.INX)
        >>> tk6 = Token('v', TokenType.VAR)
        >>> tk7 = Token('+', TokenType.ADD)
        >>> tk8 = Token('v', TokenType.VAR)
        >>> tk9 = Token('end', TokenType.END)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7, tk8, tk9])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, {})
        42

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
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        1

        >>> tk0 = Token('if', TokenType.IFX)
        >>> tk1 = Token('false', TokenType.FLS)
        >>> tk2 = Token('then', TokenType.THN)
        >>> tk3 = Token('1', TokenType.NUM)
        >>> tk4 = Token('else', TokenType.ELS)
        >>> tk5 = Token('2', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, None)
        2

        >>> tk0 = Token('fn', TokenType.FNX)
        >>> tk1 = Token('v', TokenType.VAR)
        >>> tk2 = Token('=>', TokenType.ARW)
        >>> tk3 = Token('v', TokenType.VAR)
        >>> tk4 = Token('+', TokenType.ADD)
        >>> tk5 = Token('1', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> print(exp.accept(ev, None))
        Fn(v)

        >>> tk0 = Token('(', TokenType.LPR)
        >>> tk1 = Token('fn', TokenType.FNX)
        >>> tk2 = Token('v', TokenType.VAR)
        >>> tk3 = Token('=>', TokenType.ARW)
        >>> tk4 = Token('v', TokenType.VAR)
        >>> tk5 = Token('+', TokenType.ADD)
        >>> tk6 = Token('1', TokenType.NUM)
        >>> tk7 = Token(')', TokenType.RPR)
        >>> tk8 = Token('2', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7, tk8])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, {})
        3

        >>> t0 = Token('let', TokenType.LET)
        >>> t1 = Token('fun', TokenType.FUN)
        >>> t2 = Token('f', TokenType.VAR)
        >>> t3 = Token('v', TokenType.VAR)
        >>> t4 = Token('=', TokenType.EQL)
        >>> t5 = Token('v', TokenType.VAR)
        >>> t6 = Token('+', TokenType.ADD)
        >>> t7 = Token('v', TokenType.VAR)
        >>> t8 = Token('in', TokenType.INX)
        >>> t9 = Token('f', TokenType.VAR)
        >>> tA = Token('2', TokenType.NUM)
        >>> tB = Token('end', TokenType.END)
        >>> parser = Parser([t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, tA, tB])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, {})
        4
        """
        return self.fn_exp()
    
    def fn_exp(self):
        if self.cur_token().kind == TokenType.FNX:
            self.consume_token(TokenType.FNX)
            var = self.cur_token().text
            self.consume_token(TokenType.VAR)
            self.consume_token(TokenType.ARW)
            body = self.fn_exp()
            return Fn(var, body)
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
        while self.cur_token_idx < len(self.tokens) and self.cur_token().kind in [TokenType.MUL, TokenType.DIV, TokenType.MOD]:
            kind = self.cur_token().kind
            self.consume_token(kind)
            right = self.uny_exp()
            left = Mul(left, right) if kind == TokenType.MUL else Div(left, right) if kind == TokenType.DIV else Mod(left, right)
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
            name, decl = self.decl_exp()
            self.consume_token(TokenType.INX)
            body = self.fn_exp()
            self.consume_token(TokenType.END)
            return Let(name,decl, body)
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

    def decl_exp(self):
        if self.cur_token().kind == TokenType.VAL:
            self.consume_token(TokenType.VAL)
            var = self.cur_token().text
            self.consume_token(TokenType.VAR)
            self.consume_token(TokenType.EQL)
            body = self.fn_exp()
            return var, body
        if self.cur_token().kind == TokenType.FUN:
            self.consume_token(TokenType.FUN)
            fun = self.cur_token().text
            self.consume_token(TokenType.VAR)
            var = self.cur_token().text
            self.consume_token(TokenType.VAR)
            self.consume_token(TokenType.EQL)
            body = self.fn_exp()
            return fun, Fun(fun, var, body)
        sys.exit("Parse error")