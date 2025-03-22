import sys
import enum


class Token:
    """
    This class contains the definition of Tokens. A token has two fields: its
    text and its kind. The "kind" of a token is a constant that identifies it
    uniquely. See the TokenType to know the possible identifiers (if you want).
    You don't need to change this class.
    """
    def __init__(self, tokenText, tokenKind):
        # The token's actual text. Used for identifiers, strings, and numbers.
        self.text = tokenText
        # The TokenType that this token is classified as.
        self.kind = tokenKind


class TokenType(enum.Enum):
    """
    These are the possible tokens. You don't need to change this class at all.
    """
    EOF = -1  # End of file
    NLN = 0   # New line
    WSP = 1   # White Space
    COM = 2   # Comment
    NUM = 3   # Number (integers)
    STR = 4   # Strings
    TRU = 5   # The constant true
    FLS = 6   # The constant false
    VAR = 7   # An identifier
    LET = 8   # The 'let' of the let expression
    INX = 9   # The 'in' of the let expression
    END = 10  # The 'end' of the let expression
    EQL = 201
    ADD = 202
    SUB = 203
    MUL = 204
    DIV = 205
    LEQ = 206
    LTH = 207
    NEG = 208
    NOT = 209
    LPR = 210
    RPR = 211
    ASN = 212 # The assignment '<-' operator


class Lexer:
    
    def __init__(self, source):
        """
        The constructor of the lexer. It receives the string that shall be
        scanned.
        TODO: You will need to implement this method.
        """
        self.input_string = source
        self.position = 0
        self.length = len(source)

    def tokens(self):
        """
        This method is a token generator: it converts the string encapsulated
        into this object into a sequence of Tokens. Examples:

        >>> l = Lexer("1 + 3")
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.ADD: 202>, <TokenType.NUM: 3>]

        >>> l = Lexer('1 * 2 -- 3\\n')
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.MUL: 204>, <TokenType.NUM: 3>]

        >>> l = Lexer("1 + var")
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.ADD: 202>, <TokenType.VAR: 7>]

        >>> l = Lexer("let v <- 2 in v end")
        >>> [tk.kind.name for tk in l.tokens()]
        ['LET', 'VAR', 'ASN', 'NUM', 'INX', 'VAR', 'END']
        """
        token = self.getToken()
        while token.kind != TokenType.EOF:
            if token.kind != TokenType.WSP and token.kind != TokenType.COM:
                yield token
            token = self.getToken()

    def getToken(self):
        """
        Return the next token.
        TODO: Implement this method!
        """
        if self.position >= self.length:
            return Token("", TokenType.EOF)

        current_char = self.input_string[self.position]
        self.position += 1

        # Se for um número pega todos os seus digitos
        if current_char.isdigit():
            # Handle numbers (NUM)
            number_text = current_char
            while (self.position < self.length and self.input_string[self.position].isdigit()):
                number_text += self.input_string[self.position]
                self.position += 1
            return Token(number_text, TokenType.NUM)
        
        # Se for uma string pega todos os seus caracteres
        elif current_char.isalpha():

            text = current_char
            while (self.position < self.length and self.input_string[self.position].isalpha()):
                text += self.input_string[self.position]
                self.position += 1
            if text == "true":
                return Token(text, TokenType.TRU)
            elif text == "false":
                return Token(text, TokenType.FLS)
            elif text == "not":
                return Token(text, TokenType.NOT)
            elif text == "let":
                return Token(text, TokenType.LET)
            elif text == "in":
                return Token(text, TokenType.INX)
            elif text == "end":
                return Token(text, TokenType.END)
            else:
                return Token(text, TokenType.VAR)

        elif current_char == "+":
            return Token(current_char, TokenType.ADD)

        # Se for um sinal de menos, verifica se é um comentário ou um sinal de subtração
        elif current_char == "-":
            if self.position < self.length and self.input_string[self.position] == "-":
                self.position += 1
                while self.position < self.length and self.input_string[self.position] != "\n":
                    self.position += 1
                self.position += 1
                return Token("", TokenType.COM)
            return Token(current_char, TokenType.SUB)

        elif current_char == "*":
            return Token(current_char, TokenType.MUL)

        elif current_char == "/":
            return Token(current_char, TokenType.DIV)

        elif current_char == " ":
            return Token(current_char, TokenType.WSP)

        elif current_char == "\n":
            return Token(current_char, TokenType.NLN)
        
        elif current_char == "~":
            return Token(current_char, TokenType.NEG)
        
        elif current_char == "<":
            if self.position < self.length and self.input_string[self.position] == "-":
                self.position += 1
                return Token("<-", TokenType.ASN)
            if self.position < self.length and self.input_string[self.position] == "=":
                self.position += 1
                return Token(current_char + "=", TokenType.LEQ)
            return Token(current_char, TokenType.LTH)
        
        elif current_char == "(":  # Se o próximo caractere for um asterisco, pode ser um comentário
            if self.position < self.length and self.input_string[self.position] == "*":
                self.position += 1 
                
                while self.position < self.length:
                    if self.input_string[self.position] == "*" and self.position + 1 < self.length and self.input_string[self.position + 1] == ")":
                        self.position += 2  # Consome '*' e ')'
                        break  # Sai do loop, comentário terminou
                    
                    self.position += 1
                
                return Token("", TokenType.COM)
            
            return Token(current_char, TokenType.LPR)

        
        elif current_char == ")":
            return Token(current_char, TokenType.RPR)
        
        elif current_char == "=":
            return Token(current_char, TokenType.EQL)
                      

        else:
            raise ValueError(f"Unexpected character: {current_char}")