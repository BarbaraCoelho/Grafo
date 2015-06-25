/******************************************************************************************

    Nome: B�rbara Coelho.
    IfSC - C�mpus Florian�polis
    Engenharia Eletr�nica
    Programa��o de Computadores II - 2015/1

                            REPRESENTA��O POR VETOR DE ARCOS

******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define Vertex int

/* Um objeto do tipo Arc representa um arco com ponta inicial v e ponta final w */
typedef struct
{
   Vertex v, w;
} Arc;

/* A estrutura digraph representa um digrafo */
typedef struct digraph *Digraph;
struct digraph
{
   int V;           // cont�m o n�mero de v�rtices
   int A;           // cont�m o n�mero de arcos
   Arc *arcs;       // ponteiro para o vetor de arcos
   int maxA;        // cont�m o n�mero m�ximo de arcos que o vetor arcs comporta
};

/** Prot�tipo de Fun��es **/

Arc ARC( Vertex v, Vertex w);
void DIGRAPHshow( Digraph G);
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w);
Digraph DIGRAPHinit( int V);

//////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Digraph DIG = DIGRAPHinit(5);
    DIGRAPHinsertA(DIG,1,9);
    DIGRAPHinsertA(DIG,2,13);
    DIGRAPHinsertA(DIG,2,15);
    DIGRAPHshow(DIG);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/** Fun��es **/

/* A fun��o ARC devolve um arco com ponta inicial v e ponta final w */
Arc ARC( Vertex v, Vertex w)
{
   Arc a;
   a.v = v, a.w = w;
   return a;
}

/* A fun��o DIGRAPHinit constr�i um digrafo com V v�rtices e zero arcos */
Digraph DIGRAPHinit( int V)
{
   Digraph G = malloc( sizeof (struct digraph));
   G->V = V;
   G->A = 0;
   G->maxA = V;
   G->arcs = malloc( V * sizeof (Arc)); // reserva espa�o para at� V arcos a serem inseridos futuramente
   return G;
}

/* A fun��o DIGRAPHinsertA insere no digrafo G um (novo) arco com ponta inicial v e ponta final w */
void DIGRAPHinsertA( Digraph G, Vertex v, Vertex w)
{
   int i;
   for (i = 0; i < G->A; ++i) {
      Arc a = G->arcs[i];
      if (a.v == v && a.w == w) return;
   }
   if (G->A == G->maxA) {
      G->maxA *= 2;
      G->arcs = realloc( G->arcs, G->maxA * sizeof (Arc));
   }
   G->arcs[G->A] = ARC( v, w);
   G->A++;
}

/* A fun��o DIGRAPHshow imprime, em uma linha, todos os arcos do digrafo G */
void DIGRAPHshow( Digraph G)
{
   int i;
   for (i = 0; i < G->A; i++) {
      Arc a = G->arcs[i];
      printf( "%d-%d ", a.v, a.w);
   }
   printf( "\n");
}
