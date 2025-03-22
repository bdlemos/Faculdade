import sys

from Expression import *
from Lexer import Token, TokenType

"""
This file implements the parser of logic and arithmetic expressions.

Precedence table:
    1: not ~ ()
    2: *   /
    3: +   -
    4: <   <=   >=   >
    5: =
    6: and
    7: or
    8: if-then-else

Notice that not 2 < 3 must be a type error, as we are trying to apply a boolean
operation (not) onto a number.

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
            TokenType.AND: AND,
            TokenType.ORX: OR,
            TokenType.IFX: ifThenElse
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
        >>> tk1 = Token('/', TokenType.DIV)
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
        >>> tk1 = Token('v', TokenType.VAR)
        >>> tk2 = Token('<-', TokenType.ASN)
        >>> tk3 = Token('42', TokenType.NUM)
        >>> tk4 = Token('in', TokenType.INX)
        >>> tk5 = Token('v', TokenType.VAR)
        >>> tk6 = Token('end', TokenType.END)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6])
        >>> exp = parser.parse()
        >>> ev = EvalVisitor()
        >>> exp.accept(ev, {})
        42

        >>> tk0 = Token('let', TokenType.LET)
        >>> tk1 = Token('v', TokenType.VAR)
        >>> tk2 = Token('<-', TokenType.ASN)
        >>> tk3 = Token('21', TokenType.NUM)
        >>> tk4 = Token('in', TokenType.INX)
        >>> tk5 = Token('v', TokenType.VAR)
        >>> tk6 = Token('+', TokenType.ADD)
        >>> tk7 = Token('v', TokenType.VAR)
        >>> tk8 = Token('end', TokenType.END)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6, tk7, tk8])
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
        """
        return self.parse_if_then_else()
    
    def parse_if_then_else(self):
        """
        Lida com a expressão condicional if-then-else.
        Primeiro, verifica se o token atual é um if.
        Se for, consome o token e chama a função parse_if_then_else para obter a condição.
        Em seguida, consome o token then e chama a função parse_if_then_else para obter a expressão do ramo then.
        Por fim, consome o token else e chama a função parse_if_then_else para obter a expressão do ramo else.
        """
        
        while self.cur_token().kind == TokenType.IFX:
            operator = self.cur_token()
            self.consume_token(TokenType.IFX)
            condition = self.parse_if_then_else()
            self.consume_token(TokenType.THN)
            then_branch = self.parse_if_then_else()
            self.consume_token(TokenType.ELS)
            else_branch = self.parse_if_then_else()
            return self.operators[operator.kind](condition, then_branch, else_branch)
        return self.parse_or()
    def parse_or(self):
        """
        Lida com operadores lógicos (or).
        Primeiro, chama a função parse_and para obter a expressão da esquerda.
        Em seguida, verifica se o token atual é um operador lógico or.
        Se for, consome o token e chama a função parse_and para obter a expressão da direita.
        Por fim, aplica o operador lógico or à expressão da esquerda e da direita.
        """
        expr = self.parse_and()
        while self.cur_token() and self.cur_token().kind == TokenType.ORX:
            operator = self.cur_token()
            self.consume_token(TokenType.ORX)
            right = self.parse_and()
            expr = self.operators[operator.kind](expr, right)
        return expr
    
    def parse_and(self):
        """
        Lida com operadores lógicos (and).
        Primeiro, chama a função parse_comparison para obter a expressão da esquerda.
        Em seguida, verifica se o token atual é um operador lógico and.
        Se for, consome o token e chama a função parse_comparison para obter a expressão da direita.
        Por fim, aplica o operador lógico and à expressão da esquerda e da direita.
        """
        expr = self.parse_comparison_equal()
        while self.cur_token() and self.cur_token().kind == TokenType.AND:
            operator = self.cur_token()
            self.consume_token(TokenType.AND)
            right = self.parse_comparison()
            expr = self.operators[operator.kind](expr, right)
        return expr
    
    def parse_comparison_equal(self):
        """
        Lida com operador de igual ( ==).
        Primeiro, chama a função parse_comparison para obter a expressão da esquerda.
        Em seguida, verifica se o token atual é um operador relacional.
        Se for, consome o token e chama a função parse_comparison para obter a expressão da direita.
        Por fim, aplica o operador relacional à expressão da esquerda e da direita.
        """
        expr = self.parse_comparison()
        while self.cur_token() and self.cur_token().kind in {TokenType.EQL}:
            operator = self.cur_token()
            self.consume_token(operator.kind)
            right = self.parse_comparison()
            expr = self.operators[operator.kind](expr, right)
        return expr
    
    def parse_comparison(self):
        """
        Lida com operadores relacionais (<=, <).
        Primeiro, chama a função parse_expression para obter a expressão da esquerda.
        Em seguida, verifica se o token atual é um operador relacional.
        Se for, consome o token e chama a função parse_expression para obter a expressão da direita.
        Por fim, aplica o operador relacional à expressão da esquerda e da direita.
        """
        expr = self.parse_expression()

        while self.cur_token() and self.cur_token().kind in {TokenType.LEQ, TokenType.LTH}:
            operator = self.cur_token()
            self.consume_token(operator.kind)
            right = self.parse_expression()
            expr = self.operators[operator.kind](expr, right)

        return expr


    def parse_expression(self):
        """
        Inicia o parsing a partir da expressão de menor precedência (e.g., '+', '-')
        Primeiro, chama a função parse_term para obter a expressão da esquerda.
        Em seguida, verifica se o token atual é um operador de adição ou subtração.
        Se for, consome o token e chama a função parse_term para obter a expressão da direita.
        Por fim, aplica o operador de adição ou subtração à expressão da esquerda e da direita.
        """
        expr = self.parse_term()
        while self.cur_token() and self.cur_token().kind in {TokenType.ADD, TokenType.SUB}:
            operator = self.cur_token()
            self.consume_token(operator.kind)
            right = self.parse_term()
            expr = self.operators[operator.kind](expr, right)
        return expr

    def parse_term(self):
        """"
        Lida com operadores de multiplicação e divisão.
        Primeiro, chama a função parse_factor para obter a expressão da esquerda.
        Em seguida, verifica se o token atual é um operador de multiplicação ou divisão.
        Se for, consome o token e chama a função parse_factor para obter a expressão da direita.
        Por fim, aplica o operador de multiplicação ou divisão à expressão da esquerda e da direita.
        """
        expr = self.parse_factor()
        
        while self.cur_token() and self.cur_token().kind in {TokenType.MUL, TokenType.DIV}:
            operator = self.cur_token()
            self.consume_token(operator.kind)
            right = self.parse_factor()
            expr = self.operators[operator.kind](expr, right)
        
        return expr

    def parse_factor(self):
        """"
        Lida com fatores (números, booleanos e parênteses).
        Primeiro, verifica o tipo do token atual.
        Se for um número, consome o token e retorna um objeto Num.
        Se for um booleano, consome o token e retorna um objeto Bln.
        Se for um parêntese esquerdo, consome o token, chama a função parse_expression e consome o parêntese direito.
        Se for um operador unário, consome o token e chama a função parse_factor recursivamente.
        """
        token = self.cur_token()

        if token.kind == TokenType.NUM:
            self.consume_token(TokenType.NUM)
            return Num(int(token.text))
        
        elif token.kind == TokenType.TRU:
            self.consume_token(TokenType.TRU)
            return Bln(True)
        
        elif token.kind == TokenType.FLS:
            self.consume_token(TokenType.FLS)
            return Bln(False)
        
        elif token.kind == TokenType.LPR:
            self.consume_token(TokenType.LPR)  # Consome o parêntese esquerdo
            expr = self.parse_if_then_else()
            self.consume_token(TokenType.RPR)  # Consome o parêntese direito
            return expr
        
        elif token.kind == TokenType.NEG:
            self.consume_token(TokenType.NEG)
            operand = self.parse_factor()
            return self.operators[token.kind](operand)
        
        elif token.kind == TokenType.VAR:
            self.consume_token(TokenType.VAR)
            return Var(token.text)
        
        elif token.kind == TokenType.LET:
            """let var <- exp0 in exp1 end"""
            self.consume_token(TokenType.LET)
            var_name = self.cur_token().text
            self.consume_token(TokenType.VAR)
            self.consume_token(TokenType.ASN)
            var_value = self.parse_if_then_else()
            self.consume_token(TokenType.INX)
            expr = self.parse_if_then_else()
            self.consume_token(TokenType.END)
            return Let(var_name, var_value, expr)
        
        elif token.kind == TokenType.NOT:
            self.consume_token(token.kind)
            operand = self.parse_factor()
            return self.operators[token.kind](operand)

        sys.exit("Parse error")