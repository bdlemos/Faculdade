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
    NLN = 0  # New line
    WSP = 1  # White Space
    COM = 2  # Comment
    NUM = 3  # Number (integers)
    STR = 4  # Strings
    TRU = 5  # The constant true
    FLS = 6  # The constant false
    VAR = 7  # An identifier
    LET = 8  # The 'let' of the let expression
    INX = 9  # The 'in' of the let expression
    END = 10  # The 'end' of the let expression
    EQL = 201  # x = y
    ADD = 202  # x + y
    SUB = 203  # x - y
    MUL = 204  # x * y
    DIV = 205  # x div y
    LEQ = 206  # x <= y
    LTH = 207  # x < y
    NEG = 208  # ~x
    NOT = 209  # not x
    LPR = 210  # (
    RPR = 211  # )
    VAL = 212  # The 'val' declaration
    ORX = 213  # x or y
    AND = 214  # x and y
    IFX = 215  # The 'if' of a conditional expression
    THN = 216  # The 'then' of a conditional expression
    ELS = 217  # The 'else' of a conditional expression
    FNX = 218  # The 'fn' that declares an anonymous function
    ARW = 219  # The '=>' that separates the parameter from the body of function
    FUN = 220  # The 'fun' declaration
    MOD = 221  # The 'mod' operator


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
        into this object into a sequence of Tokens. Notice that this method
        filters out three kinds of tokens: white-spaces, comments and new lines.

        Examples:

        >>> l = Lexer("1 + 3")
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.ADD: 202>, <TokenType.NUM: 3>]

        >>> l = Lexer('1 * 2\\n')
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.MUL: 204>, <TokenType.NUM: 3>]

        >>> l = Lexer('1 * 2 -- 3\\n')
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.MUL: 204>, <TokenType.NUM: 3>]

        >>> l = Lexer("1 + var")
        >>> [tk.kind for tk in l.tokens()]
        [<TokenType.NUM: 3>, <TokenType.ADD: 202>, <TokenType.VAR: 7>]

        >>> l = Lexer("let val v = 2 in v end")
        >>> [tk.kind.name for tk in l.tokens()]
        ['LET', 'VAL', 'VAR', 'EQL', 'NUM', 'INX', 'VAR', 'END']

        >>> l = Lexer("fn x => x + 1")
        >>> [tk.kind.name for tk in l.tokens()]
        ['FNX', 'VAR', 'ARW', 'VAR', 'ADD', 'NUM']

        >>> l = Lexer("fun inc a = a + 1")
        >>> [tk.kind.name for tk in l.tokens()]
        ['FUN', 'VAR', 'VAR', 'EQL', 'VAR', 'ADD', 'NUM']

        >>> l = Lexer("3 < false")
        >>> [tk.kind.name for tk in l.tokens()]
        """
        token = self.getToken()
        while token.kind != TokenType.EOF:
            if token.kind != TokenType.WSP and token.kind != TokenType.COM \
                    and token.kind != TokenType.NLN:
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
                while (self.position < self.length and (self.input_string[self.position].isalpha() or self.input_string[self.position].isdigit())):
                    text += self.input_string[self.position]
                    self.position += 1
                if text == "true" or text == "True":
                    return Token(text, TokenType.TRU)
                elif text == "false" or text == "False":
                    return Token(text, TokenType.FLS)
                elif text == "not":
                    return Token(text, TokenType.NOT)
                elif text == "let":
                    return Token(text, TokenType.LET)
                elif text == "in":
                    return Token(text, TokenType.INX)
                elif text == "end":
                    return Token(text, TokenType.END)
                elif text == 'and':
                    return Token(text, TokenType.AND)
                elif text == 'or':
                    return Token(text, TokenType.ORX)
                elif text == 'if':
                    return Token(text,TokenType.IFX)
                elif text == 'then':
                    return Token(text, TokenType.THN)
                elif text == 'else':
                    return Token(text, TokenType.ELS)
                elif text == 'fn':
                    return Token(text, TokenType.FNX)
                elif text == 'div':
                    return Token(text, TokenType.DIV)
                elif text == 'mod':
                    return Token(text, TokenType.MOD)
                elif text == 'fun':
                    return Token(text, TokenType.FUN)
                elif text == 'val':
                    return Token(text, TokenType.VAL)
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
                if self.position < self.length and self.input_string[self.position] == ">":
                    self.position += 1
                    return Token("=>", TokenType.ARW)
                return Token(current_char, TokenType.EQL)
                        

            else:
                raise ValueError(f"Unexpected character: {current_char}")