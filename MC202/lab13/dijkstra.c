/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratorio 13 - Algoritmo de Dijkstra                               *
 * Last modified: 13-12-14                                              *
 ************************************************************************/

/* A especificação das funções encontra-se no arquivo dijkstra.h */

#include <stdio.h>
#include <limits.h>

#include "dijkstra.h"
#include "balloc.h"

typedef enum {false, true} Boolean;

/* Aresta */
typedef struct aux {
    int dest;
    int peso;
    struct aux *prox;
} Aresta;

/* Implementação de grafo */
typedef struct {
    int tam;               /* número de vértices */
    Aresta * vertices[1];  /* tamanho final será 'tam' */
} RegGrafo, *ImplGrafo;


Grafo CriaGrafoVazio(int n) {
/* Devolve um grafo de 'n' vértices numerados de 0 a n-1, sem arestas. */

    /* Aloca a memÃ³ria para o grafo e seu vetor de vertices */
    ImplGrafo grafo = MALLOC(sizeof(RegGrafo) + (n-1)*sizeof(Aresta*));

    if (grafo != NULL) {
        grafo->tam = n;
        for (int i = 0; i < n; i++)
            grafo->vertices[i] = NULL;
    }

    return (Grafo) grafo;

} /* CriaGrafoVazio */

Erro AcrescentaAresta(Grafo g, int u, int v, int p) {
/* Acrescenta ao grafo 'g' a aresta 'u->v' de peso 'p'.  Casos de erro
    detectados: valores de 'u' ou 'v' inválidos, ou a aresta já existe,
    ou o peso não é positivo. As listas de adjacência devem estar em
    ordem crescente dos vértices de destino. */

    ImplGrafo grafo = g;

    /* Verifica se os vertices passado e o peso da aresta entre eles sao validos */
    if (u >= grafo->tam || u < 0 || v >= grafo->tam || v < 0 || p < 0)
        return ERRADO;

    Aresta *lista = grafo->vertices[u], *aux;

    if (lista == NULL || lista->dest > v ) {
    /* Caso em que o vertice u ainda nao e ligado a nenhum outro vertice ou
     * o primeiro vertice listado ja e maior que o que deseja-se acrescentar */
        grafo->vertices[u] = MALLOC(sizeof(Aresta));
        grafo->vertices[u]->dest = v;
        grafo->vertices[u]->peso = p;
        grafo->vertices[u]->prox = lista;
        return CERTO;
    }

    while (lista != NULL) {
        if (lista->dest >= v) break;
        aux = lista;
        lista = lista->prox;
    }
    /* Se o vertice v ja estiver listado, a aresta ja existe */
    if (lista != NULL && lista->dest == v) return ERRADO;

    Aresta *aresta = MALLOC(sizeof(Aresta));

    aresta->dest = v;
    aresta->peso = p;
    aresta->prox = lista;
    aux->prox = aresta;

    return CERTO; 

} /* AcrescentaAresta */

void ImprimeGrafo(Grafo g) {
/* Imprime as listas de adjacência do grafo sob a forma indicada neste exemplo:

      1:   2 (   2)   4 (   7)   6 (  12)
      
   onde os vértices adjacentes ao vértice 1 são 2, 4 e 6 (em ordem
   crescente).  Cada vértice e seu peso deve ser impresso no formato
   %4d.  Esta função permite a verificação da representação do grafo e
   ajuda na depuração do programa.
   
*/ 
    ImplGrafo ig = g;
    int i, n;
    Aresta *v;

    n = ig->tam;
    printf("Grafo de %d vértices:\n",n);
    for (i = 0; i < n; i++) {
        printf("%4d:",i);
        v = ig->vertices[i];
        while (v != NULL) {
            printf("%4d (%d)", v->dest, v->peso);
            v = v->prox;
        }
        printf("\n");
    }

} /* ImprimeGrafo */

void AuxDijkstra(ImplGrafo g, int r, int dist[]) {
/* Funcao que realiza o algoritmo de Dijkstra, como descrito na funcao abaixo */

    Aresta *aresta = g->vertices[r];
    int visitVertice[g->tam], j = 0;

    while (aresta != NULL) {
    /* Verifica os vertices com menor distancia a partir do vertice r e os armazena
     * no vetor visitVertice para visita-los depois de alterar suas distancias minimas */
        if (dist[r] + aresta->peso < dist[aresta->dest]) {
            dist[aresta->dest] = dist[r] + aresta->peso;
            visitVertice[j++] = aresta->dest;
        }
        aresta = aresta->prox;
    }

    /* Visita os vertices com a funcao */
    for (int i = 0; i < j; i++)
        AuxDijkstra(g, visitVertice[i], dist);

} /* AuxDijkstra */

void Dijkstra(Grafo g, int r, int dist[]) {
/* Para cada vértice 'v' do grafo 'g', calcula a distância mínima
   (soma dos pesos) de 'r' a 'v', e coloca seu valor em dist[v].  Caso
   o caminho não exista, deve colocar o valor INT_MAX importado de
   <limits.h>; o valor de dist[r] deve ser 0.
   
   Antes de retornar, deve liberar toda a memória dinâmica alocada
   para as variáveis auxiliares internas, exceto o grafo propriamente
   dito.  Deve permitir outras chamadas desta função com outro valor
   de 'r'.

*/   
    ImplGrafo grafo = g;

    /* Inicializa o vetor de distancias colocando a distancia de r como 0
     * e a de todos os outros vertices igual a infinito (INT_MAX) */
    for (int i = 0; i < grafo->tam; i++)
        dist[i] = INT_MAX;
    dist[r] = 0;

    AuxDijkstra(grafo, r, dist);

} /* Dijkstra */


void LiberaGrafo(Grafo g) {
/* Libera a memória dinâmica usada para representar o grafo */

    ImplGrafo grafo = g;
    Aresta *aux1 = NULL, *aux2 = NULL;

    for (int i = 0; i < grafo->tam; i++) {
    /* Libera a memoria alocada para as listas de arestas */
        aux1 = grafo->vertices[i];
        while (aux1 != NULL) {
            aux2 = aux1->prox;
            FREE(aux1);
            aux1 = aux2;
        }
    }
    FREE(grafo);

} /* LiberaGradfo */

