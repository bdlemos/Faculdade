import sys

from Expression import *
from Lexer import Token, TokenType

"""
This file implements the parser of arithmetic expressions.

References:
    see https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
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
            TokenType.NEG: Neg
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
        >>> exp.eval(None)
        123

        >>> parser = Parser([Token('True', TokenType.TRU)])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        True

        >>> parser = Parser([Token('False', TokenType.FLS)])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        False

        >>> tk0 = Token('~', TokenType.NEG)
        >>> tk1 = Token('123', TokenType.NUM)
        >>> parser = Parser([tk0, tk1])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        -123

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        12

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('~', TokenType.NEG)
        >>> tk3 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        -12

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('/', TokenType.DIV)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        7

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('+', TokenType.ADD)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        7

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('-', TokenType.SUB)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval(None)
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
        >>> exp.eval(None)
        14

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('==', TokenType.EQL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<=', TokenType.LEQ)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<', TokenType.LTH)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        False

        >>> tk0 = Token('not', TokenType.NOT)
        >>> tk1 = Token('4', TokenType.NUM)
        >>> tk2 = Token('<', TokenType.LTH)
        >>> tk3 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3])
        >>> exp = parser.parse()
        >>> exp.eval(None)
        True

        >>> tk0 = Token('let', TokenType.LET)
        >>> tk1 = Token('v', TokenType.VAR)
        >>> tk2 = Token('<-', TokenType.ASN)
        >>> tk3 = Token('42', TokenType.NUM)
        >>> tk4 = Token('in', TokenType.INX)
        >>> tk5 = Token('v', TokenType.VAR)
        >>> tk6 = Token('end', TokenType.END)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4, tk5, tk6])
        >>> exp = parser.parse()
        >>> exp.eval({})
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
        >>> exp.eval({})
        42
        """
        return self.parse_negation()
    
    def parse_negation(self):
        """
        Lida com operadores unários (not).
        Primeiro, verifica se o token atual é um operador unário.
        Se for, consome o token e chama a função parse_negation recursivamente.
        Caso contrário, chama a função parse_comparison.
        """
        token = self.cur_token()
        if token.kind in {TokenType.NOT}:
            self.consume_token(TokenType.NOT)
            operand = self.parse_negation()
            return self.operators[token.kind](operand)
        return self.parse_comparison()

    def parse_comparison(self):
        """
        Lida com operadores relacionais (<=, <, ==).
        Primeiro, chama a função parse_expression para obter a expressão da esquerda.
        Em seguida, verifica se o token atual é um operador relacional.
        Se for, consome o token e chama a função parse_expression para obter a expressão da direita.
        Por fim, aplica o operador relacional à expressão da esquerda e da direita.
        """
        expr = self.parse_expression()

        while self.cur_token() and self.cur_token().kind in {TokenType.EQL, TokenType.LEQ, TokenType.LTH}:
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
            expr = self.parse_negation()
            self.consume_token(TokenType.RPR)  # Consome o parêntese direito
            return expr
        
        elif token.kind in {TokenType.NEG}:
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
            var_value = self.parse_negation()
            self.consume_token(TokenType.INX)
            expr = self.parse_negation()
            self.consume_token(TokenType.END)
            return Let(var_name, var_value, expr)

        raise SyntaxError("Token inesperado")