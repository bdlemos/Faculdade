from Expression import *
from Visitor import *
import sys


def unify(constraints, sets):
    """
    This function unifies all the type variables in the list of constraints;
    thus, producing a set of unifiers.

    Example:
        >>> sets = unify([('a', type(1))], {})
        >>> integers = sets[type(1)] - {type(1)}
        >>> sorted(integers)
        ['a']

        >>> sets = unify([(type(1), 'b'), ('a', type(1))], {})
        >>> integers = sets[type(1)] - {type(1)}
        >>> sorted(integers)
        ['a', 'b']

        >>> sets = unify([(type(True), 'b'), ('a', type(1))], {})
        >>> booleans = sets[type(True)] - {type(True)}
        >>> sorted(booleans)
        ['b']

        >>> sets = unify([(type(True), 'b'), ('a', type(1))], {})
        >>> integers = sets[type(1)] - {type(1)}
        >>> sorted(integers)
        ['a']

        >>> sets = unify([('a', 'TV_1'), ('b', 'TV_2'), ('TV_2', type(1)), ('TV_1', type(1))], {})
        >>> integers = sets[type(1)] - {type(1)}
        >>> sorted(integers)
        ['TV_1', 'TV_2', 'a', 'b']

    Notice that at this stage, we still allow sets with invalid types. For
    instance, the set associated with 'b' in the example below will contain
    four elements, namely: {<class 'bool'>, <class 'int'>, 'b', 'a'}:
        >>> sets = unify([(type(True), 'b'), ('a', type(1)), ('a', 'b')], {})
        >>> len(sets['b'])
        4
    """
    uf = UnionFind()
    # Adiciona todos os elementos ao Union-Find
    for t0, t1 in constraints:
        uf.add(t0)
        uf.add(t1)
    
    # Aplica a unificação para cada restrição
    for t0, t1 in constraints:
        uf.union(t0, t1)
    
    # Agrupa os elementos com o mesmo representante
    sets_og = {}
    for element in uf.parent:
        root = uf.find(element)
        if root not in sets_og:
            sets_og[root] = set()
        sets_og[root].add(element)
    
    sets = {}
    for element in uf.parent:
        root = uf.find(element)
        sets[element] = sets_og[root]
    # Retorna os conjuntos unificados como um dicionário de representantes
    return sets


class UnionFind:
    def __init__(self):
        self.parent = {}
        self.rank = {}
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x != root_y:
            if self.rank[root_x] > self.rank[root_y]:
                self.parent[root_y] = root_x
            elif self.rank[root_x] < self.rank[root_y]:
                self.parent[root_x] = root_y
            else:
                self.parent[root_y] = root_x
                self.rank[root_x] += 1
    
    def add(self, x):
        if x not in self.parent:
            self.parent[x] = x
            self.rank[x] = 0


def name_sets(sets):
    """
    This method replaces type sets with "canonical type names". A canonical
    type name is the name of a type set. For instance, the type set
    {'a', 'b', type(int)} has the canonical name type(int)

    Notice that this method produces two types of error messages:
    * Polymorphic type: if any canonical type set is empty
    * Ambiguous type: if any canonical type set contains more than one element.
    In both cases, if any of these errors happen, the program should stop with
    the following error message: 'Type error'

    Example:
        >>> sets = name_sets({'a': {'a', 'b', type(1)}, 'b': {'a', 'b', type(1)}})
        >>> [sets['a'], sets['b']]
        [<class 'int'>, <class 'int'>]

        >>> sets = name_sets({'a': {'a', type(1)}, 'b': {'b', type(True)}})
        >>> [sets['a'], sets['b']]
        [<class 'int'>, <class 'bool'>]
    """
    def canonicalize(s):
        aux = set(s)
        for e in aux:
            if not isinstance(e, type):
                s.remove(e)
        if len(s) == 0 or len(s) > 1:
            sys.exit("Type error")

    for type_set in sets.values():
        canonicalize(type_set)
    return {v: list(e)[0] for v, e in sets.items()}




def infer_types(expression):
    """
    This method maps all the program variables to type names. We have
    implemented this method for you. This implementation might help you to
    understand how the other two methods, unify and name_sets are meant to
    work.

    Example:
        >>> e = Let('v', Num(42), Var('v'))
        >>> type_names = infer_types(e)
        >>> type_names['v']
        <class 'int'>

        >>> e = Let('v', Num(1), Let('y', Var('v'), Var('y')))
        >>> type_names = infer_types(e)
        >>> [type_names['v'], type_names['y']]
        [<class 'int'>, <class 'int'>]

        >>> e0 = Let('v', Num(1), Let('y', Var('v'), Var('y')))
        >>> e1 = IfThenElse(Lth(e0, Num(2)), Bln(True), Bln(False))
        >>> e2 = Let('w', e1, And(Var('w'), Var('w')))
        >>> type_names = infer_types(e2)
        >>> [type_names['v'], type_names['w'], type_names['y']]
        [<class 'int'>, <class 'bool'>, <class 'int'>]
    """
    ev = CtrGenVisitor()
    constraints = list(expression.accept(ev, ev.fresh_type_var()))
    type_sets = unify(constraints, {})
    return name_sets(type_sets)