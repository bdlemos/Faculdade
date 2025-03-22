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

    def advance_token(self):
        self.cur_token_idx += 1

    def consume_token(self, expected_type):
        token = self.cur_token()
        if token.kind != expected_type:
            raise SyntaxError(f"Esperado {expected_type}, mas encontrado {token.kind}")
        self.advance_token()


    def parse(self):
        """
        Returns the expression associated with the stream of tokens.

        Examples:
        >>> parser = Parser([Token('123', TokenType.NUM)])
        >>> exp = parser.parse()
        >>> exp.eval()
        123

        >>> parser = Parser([Token('True', TokenType.TRU)])
        >>> exp = parser.parse()
        >>> exp.eval()
        True

        >>> parser = Parser([Token('False', TokenType.FLS)])
        >>> exp = parser.parse()
        >>> exp.eval()
        False

        >>> tk0 = Token('~', TokenType.NEG)
        >>> tk1 = Token('123', TokenType.NUM)
        >>> parser = Parser([tk0, tk1])
        >>> exp = parser.parse()
        >>> exp.eval()
        -123

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval()
        12

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('~', TokenType.NEG)
        >>> tk3 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3])
        >>> exp = parser.parse()
        >>> exp.eval()
        -12

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('/', TokenType.DIV)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval()
        7

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('+', TokenType.ADD)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval()
        7

        >>> tk0 = Token('30', TokenType.NUM)
        >>> tk1 = Token('-', TokenType.SUB)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval()
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
        >>> exp.eval()
        14

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('==', TokenType.EQL)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval()
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<=', TokenType.LEQ)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval()
        True

        >>> tk0 = Token('4', TokenType.NUM)
        >>> tk1 = Token('<', TokenType.LTH)
        >>> tk2 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2])
        >>> exp = parser.parse()
        >>> exp.eval()
        False

        >>> tk0 = Token('not', TokenType.NOT)
        >>> tk1 = Token('4', TokenType.NUM)
        >>> tk2 = Token('<', TokenType.LTH)
        >>> tk3 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3])
        >>> exp = parser.parse()
        >>> exp.eval()
        True

        >>> tk0 = Token('3', TokenType.NUM)
        >>> tk1 = Token('*', TokenType.MUL)
        >>> tk2 = Token('3', TokenType.NUM)
        >>> tk3 = Token('+', TokenType.ADD)
        >>> tk4 = Token('4', TokenType.NUM)
        >>> parser = Parser([tk0, tk1, tk2, tk3, tk4])
        >>> exp = parser.parse()
        >>> exp.eval()
        13

        >>> tk0 = Token('not', TokenType.NOT)
        >>> tk1 = Token('true', TokenType.TRU)
        >>> parser = Parser([tk0, tk1])
        >>> exp = parser.parse()
        >>> exp.eval()
        False
        
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
            self.advance_token()
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
            self.advance_token()
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
            self.advance_token()
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
            self.advance_token()
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
            self.advance_token()
            return Num(int(token.text))
        elif token.kind == TokenType.TRU:
            self.advance_token()
            return Bln(True)
        elif token.kind == TokenType.FLS:
            self.advance_token()
            return Bln(False)
        elif token.kind == TokenType.LPR:
            self.advance_token()
            expr = self.parse_expression()
            self.consume_token(TokenType.RPR)  # Consome o parêntese direito
            return expr
        elif token.kind in {TokenType.NEG}:
            self.advance_token()
            operand = self.parse_factor()
            return self.operators[token.kind](operand)

        raise SyntaxError("Token inesperado")