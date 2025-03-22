import sys
from abc import ABC, abstractmethod
from Expression import *
import Asm as AsmModule


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
    

class RenameVisitor(ABC):
    """
    This visitor traverses the AST of a program, renaming variables to ensure
    that they all have different names.

    Usage:
        # >>> e0 = Let('x', Num(2), Add(Var('x'), Num(3)))
        # >>> e1 = Let('x', e0, Mul(Var('x'), Num(10)))
        # >>> e0.identifier == e1.identifier
        # True

        # >>> e0 = Let('x', Num(2), Add(Var('x'), Num(3)))
        # >>> e1 = Let('x', e0, Mul(Var('x'), Num(10)))
        # >>> r = RenameVisitor()
        # >>> e1.accept(r, {})
        # >>> e0.identifier == e1.identifier
        # False

        >>> x0 = Var('x')
        >>> x1 = Var('x')
        >>> e0 = Let('x', Num(2), Add(x0, Num(3)))
        >>> e1 = Let('x', e0, Mul(x1, Num(10)))
        >>> x0.identifier == x1.identifier
        True

        >>> x0 = Var('x')
        >>> x1 = Var('x')
        >>> e0 = Let('x', Num(2), Add(x0, Num(3)))
        >>> e1 = Let('x', e0, Mul(x1, Num(10)))
        >>> r = RenameVisitor()
        >>> e1.accept(r, {})
        >>> x0.identifier == x1.identifier
        False
    """
    def visit_var(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_bln(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_num(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_eql(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_add(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_sub(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_mul(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_div(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_leq(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_lth(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_neg(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_not(self, exp, arg):
        # TODO: Implement this method.
        return

    def visit_let(self, exp, arg):
        # TODO: Implement this method.
        return
    




class GenVisitor(Visitor):
    """
    The GenVisitor class compiles arithmetic expressions into a low-level
    language.
    """

    def __init__(self):
        self.next_var_counter = 0
        self.var_scope = {}

    def next_var_name(self):
        self.next_var_counter += 1
        return f"v{self.next_var_counter}"
    
    def _generate_unique_name(self, var_name):
        """
        Generates a unique name for the variable to avoid shadowing.
        """
        if var_name not in self.var_scope:
            self.var_scope[var_name] = []
        
        # Create a unique name by appending a counter or unique suffix
        unique_name = f"{var_name}_{len(self.var_scope[var_name])}"
        
        # Push the unique name onto the stack for this variable
        self.var_scope[var_name].append(unique_name)
        
        return unique_name

    def _pop_variable(self, var_name):
        """
        Pops the variable name off the stack when exiting a scope.
        """
        if var_name in self.var_scope and self.var_scope[var_name]:
            self.var_scope[var_name].pop()

    def _get_current_var_name(self, var_name):
        """
        Returns the current variable name (the one on top of the stack).
        """
        if var_name in self.var_scope and self.var_scope[var_name]:
            return self.var_scope[var_name][-1]
        return var_name  # If no stack entry, return the original name

    def visit_var(self, exp, prog):
        """
        Usage:
            >>> e = Var('x')
            >>> p = AsmModule.Program({"x":1}, [])
            >>> g = GenVisitor()
            >>> v = e.accept(g, p)
            >>> p.eval()
            >>> p.get_val(v)
            1
        """
        return self._get_current_var_name(exp.identifier)

    def visit_bln(self, exp, prog):
        """
        Usage:
            >>> e = Bln(True)
            >>> p = AsmModule.Program({}, [])
            >>> g = GenVisitor()
            >>> v = e.accept(g, p)
            >>> p.eval()
            >>> p.get_val(v)
            1

            >>> e = Bln(False)
            >>> p = AsmModule.Program({}, [])
            >>> g = GenVisitor()
            >>> v = e.accept(g, p)
            >>> p.eval()
            >>> p.get_val(v)
            0
        """
        if exp.bln:
            var_name = self.next_var_name()
            prog.add_inst(AsmModule.Addi(var_name, "x0", 1))
            return var_name
        else:
            return "x0"

    def visit_num(self, exp, prog):
        """
        Usage:
            >>> e = Num(13)
            >>> p = AsmModule.Program({}, [])
            >>> g = GenVisitor()
            >>> v = e.accept(g, p)
            >>> p.eval()
            >>> p.get_val(v)
            13
        """
        var_name = self.next_var_name()
        prog.add_inst(AsmModule.Addi(var_name, "x0", exp.num))
        return var_name
        

    def visit_eql(self, exp, prog):
        """
        >>> e = Eql(Num(13), Num(13))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1

        >>> e = Eql(Num(13), Num(10))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Eql(Num(-1), Num(1))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0
        >>> e = Eql(Num(1), Num(1))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1
        """
        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)

        # Calcula a diferença entre os dois números
        res = self.next_var_name()
        prog.add_inst(AsmModule.Sub(res, l_name, r_name))

        # Calcula o negativo do resultado
        neg = self.next_var_name()
        prog.add_inst(AsmModule.Sub(neg, "x0", res))

        # Verifica se menor que 1, então salva 1 no registrador, senão 0
        prog.add_inst(AsmModule.Slti(neg, neg, 1))
        prog.add_inst(AsmModule.Slti(res, res, 1))

        # Calcula o xor entre os dois resultados, se for 1, então são diferentes
        res3 = self.next_var_name()
        prog.add_inst(AsmModule.Xor(res3, res, neg))

        # Se for 1, então salva 0, senão 1
        prog.add_inst(AsmModule.Xori(res3, res3, 1))
        return res3




    def visit_add(self, exp, prog):
        """
        >>> e = Add(Num(13), Num(-13))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Add(Num(13), Num(10))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        23
        """
        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Add(v_name, l_name, r_name))
        return v_name

    def visit_sub(self, exp, prog):
        """
        >>> e = Sub(Num(13), Num(-13))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        26

        >>> e = Sub(Num(13), Num(10))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        3
        """
        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Sub(v_name, l_name, r_name))
        return v_name

    def visit_mul(self, exp, prog):
        """
        >>> e = Mul(Num(13), Num(2))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        26

        >>> e = Mul(Num(13), Num(10))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        130
        """
        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Mul(v_name, l_name, r_name))
        return v_name

    def visit_div(self, exp, prog):
        """
        >>> e = Div(Num(13), Num(2))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        6

        >>> e = Div(Num(13), Num(10))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1
        """
        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Div(v_name, l_name, r_name))
        return v_name

    def visit_leq(self, exp, prog):
        """
        >>> e = Leq(Num(3), Num(2))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Leq(Num(3), Num(3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1

        >>> e = Leq(Num(2), Num(3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1

        >>> e = Leq(Num(-3), Num(-2))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1

        >>> e = Leq(Num(-3), Num(-3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1

        >>> e = Leq(Num(-2), Num(-3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0
        """
        name_left = exp.left.accept(self, prog)
        name_right = exp.right.accept(self, prog)

        sub = self.next_var_name()
        prog.add_inst(AsmModule.Sub(sub, name_left, name_right))
    
        res = self.next_var_name()
        prog.add_inst(AsmModule.Slti(res, sub, 1))

        return res
        

    def visit_lth(self, exp, prog):
        """
        >>> e = Lth(Num(3), Num(2))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Lth(Num(3), Num(3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Lth(Num(2), Num(3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1
        """
        name_left = exp.left.accept(self, prog)
        name_right = exp.right.accept(self, prog)
        res = self.next_var_name()
        prog.add_inst(AsmModule.Slt(res, name_left, name_right))
        return res

    def visit_neg(self, exp, prog):
        """
        >>> e = Neg(Num(3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        -3

        >>> e = Neg(Num(0))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Neg(Num(-3))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        3
        """
        new_name = self.next_var_name()
        old_name = exp.exp.accept(self, prog)
        prog.add_inst(AsmModule.Sub(new_name, "x0", old_name))
        return new_name

    def visit_not(self, exp, prog):
        """
        >>> e = Not(Bln(True))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Not(Bln(False))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1

        >>> e = Not(Num(0))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        1

        >>> e = Not(Num(-2))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0

        >>> e = Not(Num(2))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        0
        """
        pos = exp.exp.accept(self, prog)
        
        neg = self.next_var_name()
        prog.add_inst(AsmModule.Sub(neg, "x0", pos))

        comp1 = self.next_var_name()
        comp2 = self.next_var_name()
        prog.add_inst(AsmModule.Slti(comp1, pos, 1))
        prog.add_inst(AsmModule.Slti(comp2, neg, 1))

        res = self.next_var_name()
        prog.add_inst(AsmModule.Xor(res, comp1, comp2))
        res2 = self.next_var_name()
        prog.add_inst(AsmModule.Slti(res2, res, 1))

        return res2

    def visit_let(self, exp, prog):
        """
        Usage:
            >>> e = Let('v', Not(Bln(False)), Var('v'))
            >>> p = AsmModule.Program({}, [])
            >>> g = GenVisitor()
            >>> v = e.accept(g, p)
            >>> p.eval()
            >>> p.get_val(v)
            1

            >>> e = Let('v', Num(2), Add(Var('v'), Num(3)))
            >>> p = AsmModule.Program({}, [])
            >>> g = GenVisitor()
            >>> v = e.accept(g, p)
            >>> p.eval()
            >>> p.get_val(v)
            5

            >>> e0 = Let('x', Num(2), Add(Var('x'), Num(3)))
            >>> e1 = Let('y', e0, Mul(Var('y'), Num(10)))
            >>> p = AsmModule.Program({}, [])
            >>> g = GenVisitor()
            >>> v = e1.accept(g, p)
            >>> p.eval()
            >>> p.get_val(v)
            50
        """
        name_value = exp.exp_def.accept(self, prog)

        unique_name = self._generate_unique_name(exp.identifier)
        prog.add_inst(AsmModule.Add(unique_name, name_value, 'x0'))
        ans =  exp.exp_body.accept(self, prog)
        self._pop_variable(exp.identifier)
        return ans