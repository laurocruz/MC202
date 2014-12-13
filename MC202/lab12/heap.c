/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratorio 09 - Fila de prioridades (heap)                          *
 * Last modified: 19-11-14                                              *
 ************************************************************************/

/*
  Implementação das funções de manipulação de filas de prioridade
  (FP). Vide o arquivo heap.h com as especificações.
 */  

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "balloc.h"

typedef enum {false, true} Boolean;

typedef struct {
    int tamMax;
    int tam;
    funcCompara *comp;/* função de comparação */
    void *vetor[1];   /* tamanho alocado será 'tamMax' */
} RegHeap, *ImplHeap;


/* Funções auxiliares para manipulação de FPs. */
void Sobe(ImplHeap h, int m) {
/* Sobe o valor de um nÃ³ na"Ã¡rvore" da  */
    void* x = h->vetor[m];
    int pai = (m-1)/2; /* Calculo do pai do no m na heap */

    /* Enquanto o valor do no pai for maior que do no sendo subido, deve-se subir ainda mais */
    while ((m > 0) && (h->comp(h->vetor[pai], x) < 0)) {
        h->vetor[m] = h->vetor[pai];
        m = pai;
        pai = (pai-1)/2;
    }

    /* No momento em que no no "pai" for menor que o no sendo subido, entao o no para de ser subido,
     * ja que nessa FP, os menores valores ficam acima dos maiores */
    h->vetor[m] = x;
  
} /* Sobe */

void Desce(ImplHeap h, int m) {
/* Desce o valor de um no na "arvore" da FP */
    int k = 2*m + 1;
    void* x = h->vetor[m];
    Boolean stop = false;

    while ((k < h->tam) && (!stop)) {
        /* Se o no direito for menor que o esquerdo, da-se prioridade ao direito */
        if ((k < h->tam-1) && (h->comp(h->vetor[k], h->vetor[k+1]) < 0))
            k++;
        /* Se o valor do no sendo descido for maior que o no "k", entao ele deve ser descido ainda
         * mais */
        if (h->comp(x, h->vetor[k]) < 0) {
            h->vetor[m] = h->vetor[k];
            m = k;
            k = 2*k + 1;
        } else stop = true; 
    }
    /* Quando o no "k" for menor que o no sendo descido, entao o no para de ser descido, ja que
     * nessa FP, os maiores valores ficam abaixo dos menores */
    h->vetor[m] = x;
 
} /* Desce */

void ConstroiHeap(ImplHeap ih) {
/* Recebe uma lista qualquer e a transforma em uma heap */
    for (int i = (ih->tam-2)/2; i >= 0; i--)
        Desce(ih, i);
} /* Constroi Heap */

Heap CriaHeapAux(int n, funcCompara *comp, void *elems[]) {
  /* Cria um heap vazio; se 'elems' não é nulo, preenche com os
     valores do vetor 'elems' e transforma num heap.
  */
    ImplHeap ih = MALLOC(sizeof(RegHeap)+(n-1)*sizeof(void *));

    ih->comp = comp;
    ih->tam = 0;
    ih->tamMax = n;

    if (elems != NULL) {
        for (int i = 0; i < n; i++) {
            ih->vetor[ih->tam] = elems[i];
            (ih->tam)++;
        }
        ConstroiHeap(ih);
    }

    return ih;
  
} /* CriaHeapAux */

Heap CriaHeap(int n, funcCompara *comp) {
/* Cria uma FP vazia com espaço de até 'n' elementos que serão
   apontadores; 'comp' será a função de comparação para estes elementos.
*/
    return CriaHeapAux(n, comp, NULL);

} /* CriaHeap */

Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]) {
/* Cria uma FP de 'n' elementos apontadores fornecidos no vetor 'elems'.
   'comp' será a função de comparação para estes elementos.
*/
    return CriaHeapAux(n, comp, elems);

} /* CriaInicializaHeap */

int TamanhoHeap(Heap h) {
/* Devolve o número de elementos contidos na FP. */
    ImplHeap ih = h;

    return ih->tam;

} /* TamanhoHeap */

void InsereHeap(Heap h, void *e) {
/* Insere o elemento 'e' na FP 'h'. Interrompe a execução do programa
   se houver estouro da FP.
*/
    ImplHeap ih = h;

    /* Se o tamanho da fila for igual ao tamanho mÃ¡ximo, entÃ£o aP estoura */
    if (ih->tam == ih->tamMax) {
        printf("Estouro da FP\n");
        exit(0);
    }
    
    /* Colaca-se o elemento na ultima posicao da FP e o sobe atÃ© sua poscao correta */
    ih->vetor[ih->tam] = e;
    ih->tam++;
    Sobe(ih, ih->tam-1);
 
} /* insereHeap */


void * RemoveHeap(Heap h) {
/* Remove e devolve o elemento máximo (de acordo com a função 'comp')
   da FP.  Interrompe a execução do programa se a FP está vazia.
*/
    ImplHeap ih = h;
    void *ret = NULL; /* ArmazenarÃ o elemento a ser removido */

    /* Se o tamanho da Fp for 0, nap ha mais elemento para serem removidos */
    if (ih->tam == 0) {
         printf("FP vazia\n");
         exit(0);
    }

    /* Remove o primeiro elemento da fila e coloca o Ãºltimono lugar, descendo-o para seu lugar
     * correto */
    ret = ih->vetor[0];
    ih->vetor[0] = ih->vetor[ih->tam-1];
    ih->tam--;
    Desce(ih, 0);

    return ret;
  
} /* removeHeap */

void LiberaHeap(Heap h) {
/* Libera toda a memória dinâmica ocupada pela FP 'h', mas não por
   seus elementos.
*/
    FREE(h);

} /* liberaHeap */


void * Elemento(Heap h, int k) {
/* Retorna o elemento de posicao "k" na FP */
    ImplHeap ih = h;
  
    if ((k < 0) || (k >= ih->tam))
        return NULL;

    return ih->vetor[k];

} /* Elemento */
