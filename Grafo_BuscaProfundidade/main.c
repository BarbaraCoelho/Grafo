/******************************************************************************************

    Nome: Bárbara Coelho.
    IfSC - Câmpus Florianópolis
    Engenharia Eletrônica
    Programação de Computadores II - 2015/1

                    GRAFO -  BUSCA EM PROFUNDIDADE (DFS)

******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define Vertex int
#define DIGRAPH_VALUES 6

typedef struct digraph *Digraph;
struct digraph /* A estrutura digraph representa um digrafo */
{
   int V;       // contém o número de vértices
   int A;       // contém o número de arcos
   int **adj;   // ponteiro para a matriz de adjacência
};

/** Protótipo de Funções **/

Digraph DIGRAPHinit( int V);
int **MATRIXint( int r, int c, int val);
void DIGRAPHremoveA( Digraph G, Vertex v, Vertex w);
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w);
void DIGRAPHshow( Digraph G);
void DOT_OUTPUT( Digraph G);

/** Funcões de busca por profundidade **/

int DIGRAPHreach( Digraph G, Vertex s, Vertex t,int *lbl);
void reachR( Digraph G, Vertex v,int *lbl);

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Digraph A = DIGRAPHinit(DIGRAPH_VALUES);
    static int lbl[DIGRAPH_VALUES];     // Variavel para a busca em profundidade
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

    printf("\nResultado: %d",DIGRAPHreach(A,2,2,lbl));

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////

/** Funções **/

/* A função DIGRAPHinit devolve um novo digrafo com vértices 0 1 .. V-1 e nenhum arco. */
Digraph DIGRAPHinit( int V)
{
   Digraph G = malloc( sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}

/* A função MATRIXint aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. */
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

/* A função DIGRAPHinsertA insere um arco v-w no digrafo G. */
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w)
{
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1;
      G->A++;
   }
}

/* A função DIGRAPHremoveA remove do digrafo G o arco que tem ponta inicial v e ponta final w. */
void DIGRAPHremoveA( Digraph G, Vertex v, Vertex w)
{
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0;
      G->A--;
   }
}

/* Para cada vértice v do digrafo G, esta função imprime, em uma linha, todos os vértices adjacentes a v. */
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

/* Função para verificar se tem caminho */
int DIGRAPHreach( Digraph G, Vertex s, Vertex t,int *lbl)
{
   Vertex v;
   for (v = 0; v < G->V; v++)
      lbl[v] = 0;
   reachR(G,s,lbl);
   if (lbl[t] == 0) return 0;
   else return 1;
}

/* A função vai em todos os vértices que podem ser atingidos a partir de v, não passando nos qie lbl é 0 */
void reachR( Digraph G, Vertex v,int *lbl)
{
   Vertex w;
   lbl[v] = 1;
   for (w = 0; w < G->V; w++)
      if (G->adj[v][w] == 1 && lbl[w] == 0)
         reachR(G,w,lbl);
}
