merge([],[],[]).
merge([], L2, L2).
merge(L1, [], L1).

merge([H1|T1],[H2|T2], [H2|Z]):-
    H1 >= H2,
    merge([H1|T1],T2,Z).

merge([H1|T1],[H2|T2], [H1|Z]):-
    H1 < H2,
    merge(T1,[H2|T2],Z).

split([], [], []). % Caso base: lista vazia
split([A], [A], []). % Caso base: um elemento na lista original

split([A, B | T], [A | L1], [B | L2]) :-
    split(T, L1, L2).

mergeSort([],[]).
mergeSort([A],[A]).
mergeSort(A,Z):-
    split(A,L1,L2),
    mergeSort(L1,X),
    mergeSort(L2,Y),
    merge(X,Y,Z).


getIndex([],_,nil).
getIndex([A|_],0,A).
getIndex([_|T],X,Y):-
    W is X-1,
    getIndex(T,W,Y).
   

myLength([],0).
myLength([_|B],Y):-
    myLength(B,Z),
    Y is 1+Z.

mediana(A,X):-
    mergeSort(A,Z),
    myLength(A,W),
    L is W // 2,
    write(Z),
    getIndex(Z,L,X).