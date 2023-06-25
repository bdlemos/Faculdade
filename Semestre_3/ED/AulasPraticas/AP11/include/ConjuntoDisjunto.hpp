typedef struct node{
	long data;
	node* parent;
	int rank;
}node;


class ConjuntoDisjunto {
private:
	node* sets[10000];

public:	
	ConjuntoDisjunto();
	~ConjuntoDisjunto();
	void makeSet(long x);
	void unionSet(long x, long y);
	long findSet(long x);
};
