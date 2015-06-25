/******************************************************************************************

    Nome: B�rbara Coelho.
    IfSC - C�mpus Florian�polis
    Engenharia Eletr�nica
    Programa��o de Computadores II - 2015/1

                        REPRESENTA��O POR MATRIZ DE ADJAC�NCIA

******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define Vertex int
#define DIGRAPH_VALUES 6

typedef struct digraph *Digraph;
struct digraph /* A estrutura digraph representa um digrafo */
{
   int V;       // cont�m o n�mero de v�rtices
   int A;       // cont�m o n�mero de arcos
   int **adj;   // ponteiro para a matriz de adjac�ncia
};

/** Prot�tipo de Fun��es **/

Digraph DIGRAPHinit( int V);
int **MATRIXint( int r, int c, int val);
void DIGRAPHremoveA( Digraph G, Vertex v, Vertex w);
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w);
void DIGRAPHshow( Digraph G);
void DOT_OUTPUT( Digraph G);

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Digraph A = DIGRAPHinit(DIGRAPH_VALUES);
    DIGRAPHinsertA(A,0,0);
    DIGRAPHinsertA(A,1,2);
    DIGRAPHinsertA(A,2,2);
    DIGRAPHinsertA(A,3,5);
    DIGRAPHinsertA(A,4,5);
    DIGRAPHinsertA(A,5,3);
    DIGRAPHinsertA(A,4,5);
    DIGRAPHshow(A);

    int line,col;
    for(line=0;line<6;line++)
    {
        printf("\n");
        for(col=0;col<6;col++)
            printf("%d",A->adj[line][col]);
    }

    printf("\n\n");
    DOT_OUTPUT(A);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////

/** Fun��es **/

/* A fun��o DIGRAPHinit devolve um novo digrafo com v�rtices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit( int V)
{
   Digraph G = malloc( sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}

/* A fun��o MATRIXint aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. */
int **MATRIXint( int r, int c, int val)
{
   Vertex i, j;
   int **m = malloc( r * sizeof (int *));
   for (i = 0; i < r; i++)
      m[i] = malloc( c * sizeof (int));
   for (i = 0; i < r; i++)
      for (j = 0; j < c; j++)
         m[i][j] = val;     // Cada elemento da matriz recebe valor val
   return m;
}

/* A fun��o DIGRAPHinsertA insere um arco v-w no digrafo G. */
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w)
{
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1;
      G->A++;
   }
}

/* A fun��o DIGRAPHremoveA remove do digrafo G o arco que tem ponta inicial v e ponta final w. */
void DIGRAPHremoveA( Digraph G, Vertex v, Vertex w)
{
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0;
      G->A--;
   }
}

/* Para cada v�rtice v do digrafo G, esta fun��o imprime, em uma linha, todos os v�rtices adjacentes a v. */
void DIGRAPHshow( Digraph G)
{
   Vertex v, w;
   for (v = 0; v < G->V; v++) {
      printf( "%2d:", v);
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1)
            printf( " %2d", w);
      printf( "\n");
   }
}
/* Salva no formato .dot*/
void DOT_OUTPUT(Digraph G)
{
    char url[]="dados.txt";
    FILE *arq;

    arq = fopen(url, "w");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		fprintf(arq,"digraph G{\n");
		int line,col;
        for(line=0;line<6;line++)
        {
            for(col=0;col<6;col++)
            {
                if(G->adj[line][col]==1)
                     fprintf(arq,"%d->%d;\n",line,col);
            }
        }
        fprintf(arq,"}");
	}
	fclose(arq);
}
