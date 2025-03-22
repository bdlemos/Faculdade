btree(nil).
btree(btree(Left, _, Right)) :-
    btree(Left),
    btree(Right).

sum_tree(nil,0).
sum_tree(btree(L,Q,R),X):-
    sum_tree(L,Y),
    sum_tree(R,Z),
    X is Y+Z+Q.

sum_leafs(nil,0).
sum_leafs(btree(nil,Q,nil),Q).
sum_leafs(btree(L,_,R),X):-
    sum_leafs(L,Y),
    sum_leafs(R,Z),
    X is Y+Z.


reverse([],[]).
reverse([Hd|Tl],X):-
    reverse(Tl,Y),
    append(Y,[Hd],X).

myLen([],0).
myLen([_|Tl],X):-
    myLen(Tl,Y),
    X is Y+1.

sum([],0).
sum([Hd|Tl],X):-
    sum(Tl,Y),
    X is Y+Hd.

    # Arvore = btree(btree(nil, 10, btree(nil, 15, nil)), 2, btree(nil, 13, nil)),
#    sum_leafs(Arvore, Soma).


