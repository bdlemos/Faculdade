#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
#include <getopt.h>
#include <string.h>
#include <math.h>

int *pre; int sizepre = 0;
int *in; int sizein = 0;
int *post; int sizepost = 0;


// Syntax tree structure
typedef long TipoChave;
typedef struct TipoRegistro {
  TipoChave Chave;
} TipoRegistro;
typedef struct TipoNo * TipoApontador;
typedef struct TipoNo {
  TipoRegistro Reg;
  TipoApontador Esq, Dir;
} TipoNo;

typedef struct prm{
  char nomesaida[200];
  int semente;
  int numno;
  FILE * saida;
  int treesize;
  int numlevel;
} prm_t;

void uso()
// Descricao: imprime as instrucoes de uso do programa
// Entrada:  N/A
// Saida: instrucoes
{
  fprintf(stderr,"geraexp\n");
  fprintf(stderr,"\t-o <arq>\t(arquivo de saida) \n");
  fprintf(stderr,"\t-s <num>\t(semente)\n");
  fprintf(stderr,"\t-n <num>\t(numero de nos)\n");
  fprintf(stderr,"\t-h\t(opcoes de uso)\n");
}

void parse_args(int argc, char ** argv, prm_t * prm)
// Descricao: analisa a linha de comando a inicializa variaveis
// Entrada: argc e argv
// Saida: prm
{
     extern char * optarg;
     extern int optind;
     int c ;
     // valores padrao
     prm->nomesaida[0] = 0;
     prm->semente = 0;
     prm->numno = 3;
     prm->numlevel = 2;
     // percorre a linha de comando buscando identificadores
     while ((c = getopt(argc, argv, "o:s:n:iph")) != EOF){
       switch(c) {
         case 'o':
	          // arquivo de saida
	          strcpy(prm->nomesaida,optarg);
                  break;
         case 's':
	          // semente aleatoria
	          prm->semente = atoi(optarg);
		  srand48((long) prm->semente);
		  break;
         case 'n':
	          // numero de nos
	          prm->numno = atoi(optarg);
		  prm->numlevel = ((int) log2((double) prm->numno))+2;
		  break;
         case 'h':
         default:
                  uso();
                  exit(1);

       }
     }
     // verifica apenas o nome do arquivo de saida
     if (!prm->nomesaida[0]) {
       printf("Arquivo de saida nao definido.");
       exit(1);
     }
}

void dumpTree(TipoApontador * T, int level, prm_t * prm) {
  if ((*T) != NULL) {
    for(int i=0; i<level; i++) fprintf(prm->saida,"    ");
    fprintf(prm->saida," %3ld (%d)\n", (*T)->Reg.Chave,level);
    dumpTree(&(*T)->Esq,level+1,prm);
    dumpTree(&(*T)->Dir,level+1,prm);
  }
}

int createTree(TipoNo ** curr, int level, prm_t * prm){
  // create node
  (*curr) = (TipoNo*) malloc(sizeof(TipoNo));
  (*curr)->Esq = (*curr)->Dir = NULL;
  // set type
  if (drand48()>((8.0*(1<<level)*prm->treesize))/(((1<<prm->numlevel)*prm->numno))){
    (*curr)->Reg.Chave = prm->treesize;
    prm->treesize++;
    if (prm->treesize<prm->numno) createTree(&((*curr)->Esq),level+1,prm);
    if (prm->treesize<prm->numno) createTree(&((*curr)->Dir),level+1,prm);
  } else {
    (*curr)->Reg.Chave = prm->treesize;
    prm->treesize++;
  }
  return prm->treesize;
}

void preorder(TipoApontador p){
  if(p != NULL){
    pre[sizepre++] = p->Reg.Chave;
    //printf("%ld ", p->Reg.Chave);
    preorder(p->Esq);
    preorder(p->Dir);
  }
}

void inorder(TipoApontador p){
  if(p != NULL){
    inorder(p->Esq);
    in[sizein++] = p->Reg.Chave;
    //printf("%ld ", p->Reg.Chave);
    inorder(p->Dir);
  }
}

void postorder(TipoApontador p){
  if(p != NULL){
    postorder(p->Esq);
    postorder(p->Dir);
    post[sizepost++] = p->Reg.Chave;
    //printf("%ld ", p->Reg.Chave);
  }
}

int ancestral(int i, int j){
  int raiz = pre[0], indexR, indexI, indexJ;
  if(i==raiz) return 1;
  //condição 1
  for (int z = 0; z < sizein; z++){
    if(raiz == in[z]) indexR = z;
    if(i == in[z]) indexI = z;
    if(j == in[z]) indexJ = z;
  }
  if(!((indexI > indexR && indexJ > indexR) || (indexI < indexR && indexJ < indexR))) return 0;

  //condição 2
  for (int z = 0; z < sizepost; z++){
    if (i == post[z]) indexI = z;
    else if (j == post[z]) indexJ = z;
  }
  if(indexJ > indexI) return 0;

  //condição 3
  for (int z = 0; z < sizepre; z++){
    if (i == pre[z]) indexI = z;
    else if (j == pre[z]) indexJ = z;
  }
  if(indexJ < indexI) return 0;

  return 1;
}

int main(int argc, char *argv[])
{
  TipoNo *root;
  prm_t prm;
  int i,j;

  parse_args(argc,argv,&prm);
  prm.saida = fopen(prm.nomesaida,"wt");
  prm.treesize = 0;

  createTree(&root,0,&prm);
  dumpTree(&root,0,&prm);
  int size = prm.treesize;
  pre = (int*) malloc(size*sizeof(int));
  in = (int*) malloc(size*sizeof(int));
  post = (int*) malloc(size*sizeof(int));
  inorder(root);
  preorder(root);
  postorder(root);
  fprintf(prm.saida,"Se for ancestral retorna 1, caso nao retorna 0\n");
  for (int k=0; k<prm.treesize; k++){
    i = j = 0;
    while (i==j){
      i = (int) (drand48()*prm.treesize);
      j = (int) (drand48()*prm.treesize);
    }
    fprintf(prm.saida,"%d testando ancestral(%d,%d) = %d\n",k,i,j,ancestral(i,j));
    ancestral(i,j); 
  }
  fclose(prm.saida);
  return 0;
} 
