import sys

from Expression import *
from Lexer import Token, TokenType

"""
This file implements the parser of arithmetic expressions.

References:
    see https://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
"""
class Stack:
    def __init__(self):
        self.stack = []
    
    def push(self, value):
        self.stack.append(value)
    
    def pop(self):
        return self.stack.pop() if not self.is_empty() else None
    
    def peek(self):
        return self.stack[-1] if not self.is_empty() else None
    
    def is_empty(self):
        return len(self.stack) == 0

class Queue:
    def __init__(self):
        self.queue = []
    
    def enqueue(self, value):
        self.queue.append(value)
    
    def dequeue(self):
        return self.queue.pop(0) if not self.is_empty() else None
    
    def is_empty(self):
        return len(self.queue) == 0

def operator_priority(kind):
    if kind == TokenType.ADD or kind == TokenType.SUB:
        return 1  # Baixa prioridade para + e -
    elif kind == TokenType.MUL or kind == TokenType.DIV:
        return 2  # Maior prioridade para * e /
    elif kind == TokenType.NOT:  # Prioridade mais baixa para o 'not'
        return 0
    elif kind == TokenType.NEG:  # Prioridade mais alta para o '~' (bitwise NOT)
        return 3
    elif kind == TokenType.LPR:  # Parênteses à esquerda (não tem prioridade de operação)
        return 0
    return -1





class Parser:
    def __init__(self, tokens):
        """
        Initializes the parser. The parser keeps track of the list of tokens
        and the current token. For instance:
        """
        self.tokens = list(tokens)
        self.cur_token_idx = 0 # This is just a suggestion!
    def In2Pos(self, tokens):
        operators = Stack()
        expression_queue = Queue()
        result = []
        
        # Enqueue all tokens
        for i, token in enumerate(tokens):
            if token.kind in [TokenType.EQL, TokenType.LEQ, TokenType.LTH]:
                self.cur_token_idx = i + 1
                break
            expression_queue.enqueue(token)
        
        while not expression_queue.is_empty():
            #print([op.text for op in result])
            character = expression_queue.dequeue()
            operation = operator_priority(character.kind)
            # print([op.text for op in operators.stack])
            # print([op.text for op in result])
            if character.kind == TokenType.NLN:
                continue
            
            if operation > 0 or character.kind == TokenType.LPR:
                if not operators.is_empty():
                    last = operators.pop()
                    if operation <= operator_priority(last.kind) and character.kind != TokenType.LPR:
                        result += [last]
                    else:
                        operators.push(last)
                operators.push(character)
            
            elif not operators.is_empty() and character.kind == TokenType.RPR:
                #print([op.text for op in operators.stack])
                last = operators.pop()
                while last.kind != TokenType.LPR:
                    result += [last]
                    last = operators.pop()
            
            else:
                result += [character]
        
        # Add remaining operators to the result
        while not operators.is_empty():
            result += [operators.pop()]

        return result


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
        
        """
        operators = {
            TokenType.ADD: Add,
            TokenType.SUB: Sub,
            TokenType.MUL: Mul,
            TokenType.DIV: Div,
            TokenType.EQL: Eql,
            TokenType.LEQ: Leq,
            TokenType.LTH: Lth,
        }
        if self.tokens[0].kind == TokenType.NOT:
            flag = True
            left_side = self.In2Pos(self.tokens[1:])
            self.cur_token_idx += 1
        else:
            flag = False
            left_side = self.In2Pos(self.tokens)
        if self.cur_token_idx != 0:
            right_side = self.In2Pos(self.tokens[self.cur_token_idx:])
        
        
        stack_left_side = Stack()
        stack_right_side = Stack()
        #print([token.kind for token in left_side])
        for token in left_side:
            if token.kind == TokenType.NUM:
                stack_left_side.push(Num(int(token.text)))
            elif token.kind == TokenType.TRU:
                stack_left_side.push(Bln(True))
            elif token.kind == TokenType.FLS:
                stack_left_side.push(Bln(False))
            elif token.kind == TokenType.NEG:
                stack_left_side.push(Neg(stack_left_side.pop()))
            elif token.kind == TokenType.NOT:
                stack_left_side.push(Not(Bln(stack_left_side.pop())))
            else:
                right = stack_left_side.pop()
                left = stack_left_side.pop()
                stack_left_side.push(operators[token.kind](left, right))
        if self.cur_token_idx != 0:
            for token in right_side:
                if token.kind == TokenType.NUM:
                    stack_right_side.push(Num(int(token.text)))
                elif token.kind == TokenType.TRU:
                    stack_right_side.push(Bln(True))
                elif token.kind == TokenType.FLS:
                    stack_right_side.push(Bln(False))
                elif token.kind == TokenType.NEG:
                    stack_right_side.push(Neg(stack_right_side.pop()))
                elif token.kind == TokenType.NOT:
                    stack_right_side.push(Not(stack_right_side.pop()))
                elif token.kind == TokenType.NLN:
                    continue
                else:
                    right = stack_right_side.pop()
                    left = stack_right_side.pop()
                    stack_right_side.push(operators[token.kind](left, right))
        if stack_right_side.is_empty():
            return stack_left_side.pop() if not flag else Not(stack_left_side.pop())
        if flag:
            return Not(operators[self.tokens[self.cur_token_idx-1].kind](stack_left_side.pop(), stack_right_side.pop()))
        
        return operators[self.tokens[self.cur_token_idx-1].kind](stack_left_side.pop(), stack_right_side.pop())