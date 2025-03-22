mochila([],[],_,0).
mochila([A|B],[C|D],P,W):- 
    A =< P,
    Z is P - A,
    mochila(B,D,Z,J), % tu bota nao bota?
    W1 is C + J ,
    mochila(B,D,P,J1), % tu nao bota 
    W2 is J1 ,
	W is max(W1,W2).

mochila([_|B],[_|D],P,W):- % nao cabe
    mochila(B,D,P,W).