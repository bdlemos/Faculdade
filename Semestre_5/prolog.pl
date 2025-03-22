parent(kim,holly).
parent(margaret,holly).
parent(margaret,kent).
parent(esther,margaret).
parent(herbert,margaret).
parent(herbert,jean).

parent(julio,ganso).
parent(cla,julio).
parent(cla,marc).
parent(marc,gansa).

greatGrandParent(GGP,GGC):-
    parent(GGP,GP),
    parent(GP,P),
    parent(P,GGC).


sibling(X,Y):-
    not(X=Y),
    parent(P,X),
    parent(P,Y).

firstCousin(X,Y):-
    not(sibling(X,Y)),
    parent(P,X),
    parent(K,Y),
    sibling(P,K).

descendant(X,Y):- parent(Y,X).
descendant(X,Y):-
    parent(Z,X), % Acha o pai de X
    descendant(Z,Y). % Ve se o o pai de x é descendente de Y


third(X,Y):- 
    nth0(2,Y,Z),
   	X is Z.

dupList([],[]).
dupList([A|B],[A|[A|L]]):-
    dupList(B,L).
    

oddSize([]):- false.
oddSize([_|L]):- 
        not(oddSize(L)).
    
    
    
    
    
isMember([],_):- false.
isMember([X|_], X):- true.
isMember([_|T], X):-isMember(T,X).

isEqual([], []) :- true.
isEqual(_, []) :- false.
isEqual([], _) :- true.
isEqual([H|T], B) :-
    isMember(B, H),      
    isEqual(T, B).


isDiff([], _, []).
isDiff([H|T], Y, [H|Z]) :- 
    not(isMember(Y, H)), 
    isDiff(T, Y, Z).    
isDiff([H|T], Y, Z) :-
    isMember(Y, H),    
    isDiff(T, Y, Z).

isGreater(X, Y, Z) :- 
    X > Y, 
    Z is X.
isGreater(X, Y, Z) :- 
    Y >= X, 
    Z is Y.

maxList([A],A).
maxList([H|T],M):-
    maxList(T,Z),
    isGreater(H,Z,Max),
    M is Max.


prefix([],[]).
prefix([H],[H|_]).
prefix([H|Y],[H|T]):-
    prefix(Y,T).

subsetSum(_, 0,[]):-true.
subsetSum([], _,_):-false.
subsetSum([H|T], X, [H|Z]):-
    W is X-H,
    subsetSum(T,W,Z).

subsetSum([_|T], X, Z):-
    subsetSum(T,X,Z).
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    
    
    
    
    
    
    