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
    def visit_or(self, exp, arg):
        pass

    @abstractmethod
    def visit_and(self, exp, arg):
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

    @abstractmethod
    def visit_ifThenElse(self, exp, arg):
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
    def visit_ifThenElse(self, exp, arg):
        return
    
    def visit_or(self, exp, arg):
        return
    
    def visit_and(self, exp, arg):
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

        return self._get_current_var_name(exp.identifier)

    def visit_bln(self, exp, prog):

        if exp.bln:
            var_name = self.next_var_name()
            prog.add_inst(AsmModule.Addi(var_name, "x0", 1))
            return var_name
        else:
            var_name = self.next_var_name()
            prog.add_inst(AsmModule.Addi(var_name, "x0", 0))
            return var_name

    def visit_num(self, exp, prog):

        var_name = self.next_var_name()
        prog.add_inst(AsmModule.Addi(var_name, "x0", exp.num))
        return var_name
        

    def visit_eql(self, exp, prog):
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

        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Add(v_name, l_name, r_name))
        return v_name

    def visit_sub(self, exp, prog):

        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Sub(v_name, l_name, r_name))
        return v_name

    def visit_mul(self, exp, prog):

        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Mul(v_name, l_name, r_name))
        return v_name

    def visit_div(self, exp, prog):

        l_name = exp.left.accept(self, prog)
        r_name = exp.right.accept(self, prog)
        v_name = self.next_var_name()
        prog.add_inst(AsmModule.Div(v_name, l_name, r_name))
        return v_name

    def visit_leq(self, exp, prog):
        name_left = exp.left.accept(self, prog)
        name_right = exp.right.accept(self, prog)

        sub = self.next_var_name()
        prog.add_inst(AsmModule.Sub(sub, name_left, name_right))
    
        res = self.next_var_name()
        prog.add_inst(AsmModule.Slti(res, sub, 1))

        return res
        

    def visit_lth(self, exp, prog):
    
        name_left = exp.left.accept(self, prog)
        name_right = exp.right.accept(self, prog)
        res = self.next_var_name()
        prog.add_inst(AsmModule.Slt(res, name_left, name_right))
        return res

    def visit_neg(self, exp, prog):

        new_name = self.next_var_name()
        old_name = exp.exp.accept(self, prog)
        prog.add_inst(AsmModule.Sub(new_name, "x0", old_name))
        return new_name

    def visit_not(self, exp, prog):

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

        name_value = exp.exp_def.accept(self, prog)

        unique_name = self._generate_unique_name(exp.identifier)
        prog.add_inst(AsmModule.Add(unique_name, name_value, 'x0'))
        ans =  exp.exp_body.accept(self, prog)
        self._pop_variable(exp.identifier)
        return ans
    
    def visit_ifThenElse(self, exp, prog):
        """
        >>> e = IfThenElse(Bln(True), Num(3), Num(5))
        >>> p = AsmModule.Program({}, [])
        >>> g = GenVisitor()
        >>> v = e.accept(g, p)
        >>> p.eval()
        >>> p.get_val(v)
        3

        # >>> e = IfThenElse(Bln(False), Num(3), Num(5))
        # >>> p = AsmModule.Program({}, [])
        # >>> g = GenVisitor()
        # >>> v = e.accept(g, p)
        # >>> p.eval()
        # >>> p.get_val(v)
        # 5

    #     >>> e = IfThenElse(And(Bln(True), Bln(True)), Num(3), Num(5))
    #     >>> p = AsmModule.Program({}, [])
    #     >>> g = GenVisitor()
    #     >>> v = e.accept(g, p)
    #     >>> p.eval()
    #     >>> p.get_val(v)
    #     3

    #     >>> e0 = Mul(Num(2), Add(Num(3), Num(4)))
    #     >>> e1 = IfThenElse(And(Bln(True), Bln(False)), Num(3), e0)
    #     >>> p = AsmModule.Program({}, [])
    #     >>> g = GenVisitor()
    #     >>> v = e1.accept(g, p)
    #     >>> p.eval()
    #     >>> p.get_val(v)
    #     14

    #     >>> e0 = Div(Num(2), Num(0))
    #     >>> e1 = IfThenElse(Bln(True), Num(3), e0)
    #     >>> p = AsmModule.Program({}, [])
    #     >>> g = GenVisitor()
    #     >>> v = e1.accept(g, p)
    #     >>> p.eval()
    #     >>> p.get_val(v)
    #     3

    #     >>> e0 = Div(Num(2), Num(0))
    #     >>> e1 = IfThenElse(Bln(False), e0, Num(3))
    #     >>> p = AsmModule.Program({}, [])
    #     >>> g = GenVisitor()
    #     >>> v = e1.accept(g, p)
    #     >>> p.eval()
    #     >>> p.get_val(v)
    #     3
        """
        # TODO: Implement this method.

        cond = exp.cond.accept(self, prog)
        ans = self.next_var_name()

        beq = AsmModule.Beq(cond, "x0")
        prog.add_inst(beq)
        
        # If true
        true_if = exp.e0.accept(self, prog)
        beq_end = AsmModule.Beq("x0", "x0")
        prog.add_inst(AsmModule.Addi(ans, true_if, 0))
        prog.add_inst(beq_end)

        beq.set_target(prog.get_number_of_instructions())
        # If false
        false_if = exp.e1.accept(self, prog)
        prog.add_inst(AsmModule.Addi(ans, false_if, 0))
        beq_end.set_target(prog.get_number_of_instructions())


        return ans
    
    def visit_and(self, exp, prog):
        # """
        # Example:
        #     >>> y0 = Var('x')
        #     >>> y1 = Var('x')
        #     >>> x0 = And(Lth(y0, Num(2)), Leq(Num(2), y1))
        #     >>> x1 = Var('x')
        #     >>> e0 = Let('x', Num(2), Add(x0, Num(3)))
        #     >>> e1 = Let('x', e0, Mul(x1, Num(10)))
        #     >>> r = RenameVisitor()
        #     >>> e1.accept(r, {})
        #     >>> y0.identifier == y1.identifier
        #     True

        #     >>> y0 = Var('x')
        #     >>> y1 = Var('x')
        #     >>> x0 = And(Lth(y0, Num(2)), Leq(Num(2), y1))
        #     >>> x1 = Var('x')
        #     >>> e0 = Let('x', Num(2), Add(x0, Num(3)))
        #     >>> e1 = Let('x', e0, Mul(x1, Num(10)))
        #     >>> r = RenameVisitor()
        #     >>> e1.accept(r, {})
        #     >>> y0.identifier == x1.identifier
        #     False
        # """
        # TODO: Implement this method.
        ans = self.next_var_name()

        exp1 = exp.left.accept(self, prog)
        beq_end = AsmModule.Beq(exp1, "x0")
        prog.add_inst(AsmModule.Addi(ans, "x0", 0))
        prog.add_inst(beq_end)

        exp2 = exp.right.accept(self, prog)
        prog.add_inst(AsmModule.Addi(ans, exp2, 0))
        beq_end.set_target(prog.get_number_of_instructions())
        return ans

    def visit_or(self, exp, prog):
        # """
        # Example:
        #     >>> y0 = Var('x')
        #     >>> y1 = Var('x')
        #     >>> x0 = Or(Lth(y0, Num(2)), Leq(Num(2), y1))
        #     >>> x1 = Var('x')
        #     >>> e0 = Let('x', Num(2), Add(x0, Num(3)))
        #     >>> e1 = Let('x', e0, Mul(x1, Num(10)))
        #     >>> r = RenameVisitor()
        #     >>> e1.accept(r, {})
        #     >>> y0.identifier == y1.identifier
        #     True

        #     >>> y0 = Var('x')
        #     >>> y1 = Var('x')
        #     >>> x0 = Or(Lth(y0, Num(2)), Leq(Num(2), y1))
        #     >>> x1 = Var('x')
        #     >>> e0 = Let('x', Num(2), Add(x0, Num(3)))
        #     >>> e1 = Let('x', e0, Mul(x1, Num(10)))
        #     >>> r = RenameVisitor()
        #     >>> e1.accept(r, {})
        #     >>> y0.identifier == x1.identifier
        #     False
        # """
        # TODO: Implement this method.
        ans = self.next_var_name()

        # Evaluate the first operand
        exp1 = exp.left.accept(self, prog)

        # If exp1 is true (non-zero), jump to the end
        beq_end = AsmModule.Beq(exp1, "x0")  # Skip if exp1 is true
        prog.add_inst(beq_end)

        # Evaluate the second operand
        exp2 = exp.right.accept(self, prog)

        # Set ans to the result of exp2
        prog.add_inst(AsmModule.Addi(ans, exp2, 0))

        # Jump to the final label to avoid overwriting ans
        beq_end2 = AsmModule.Beq("x0", "x0")  # Unconditional jump
        prog.add_inst(beq_end2)

        # Label for when exp1 is true
        beq_end.set_target(prog.get_number_of_instructions())

        # Set ans to true (non-zero) if exp1 is true
        prog.add_inst(AsmModule.Addi(ans, "x0", 1))

        # Final label
        beq_end2.set_target(prog.get_number_of_instructions())

        return ans

