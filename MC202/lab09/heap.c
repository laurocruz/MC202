/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratorio 09 - Fila de prioridades (heap)                          *
 * Last modified: 17-11-14                                              *
 ************************************************************************/

/*
  Implementação das funções de manipulação de filas de prioridade
  (FP). Vide o arquivo heap.h com as especificações.
 */  

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "balloc.h"

typedef struct {
    int tamMax;
    int tam;
    funcCompara *comp;/* função de comparação */
    void *vetor[1];   /* tamanho alocado será 'tamMax' */
} RegHeap, *ImplHeap;


/* Funções auxiliares para manipulação de FPs. */
void Sobe(ImplHeap h, int m) {
    int x = h->vetor[m];
    int pai = (m-1)/2;

    while (m > 0 && h->vetor[pai] < x) {
        h->vetor[m] = h->vetor[pai];
        m = pai;
        pai = (pai-1)/2;
    }

    h->vetor[m] = x;
  
} /* Sobe */

void Desce(ImplHeap h, int m) {

  /* COMPLETAR */
  
} /* Desce */


Heap CriaHeapAux(int n, funcCompara *comp, void *elems[]) {
  /* Cria um heap vazio; se 'elems' não é nulo, preenche com os
     valores do vetor 'elems' e transforma num heap.
  */
    ImplHeap ih = MALLOC(sizeof(RegHeap)+(n-1)*sizeof(void *));

  /* COMPLETAR */
  
    return ih;
  
} /* CriaHeapAux */

Heap CriaHeap(int n, funcCompara *comp) {

    return CriaHeapAux(n,comp,NULL);

} /* CriaHeap */

Heap CriaInicializaHeap(int n, funcCompara *comp, void *elems[]) {

    return CriaHeapAux(n,comp,elems);

} /* CriaInicializaHeap */

int TamanhoHeap(Heap h) {

  /* COMPLETAR */
  
    return 0; /* provisório */
  
} /* TamanhoHeap */

void InsereHeap(Heap h, void *e) {
    ImplHeap ih = h;
    
    if (ih->tam == ih->tamMax) {
    printf("Estouro da FP\n");
    exit(0);
  }

  /* COMPLETAR */
 
} /* insereHeap */


void * RemoveHeap(Heap h) {
    ImplHeap ih = h;
    void *ret = NULL;

    if (ih->tam == 0) {
         printf("FP vazia\n");
         exit(0);
    }

  /* COMPLETAR */

    return ret;
  
} /* removeHeap */

void LiberaHeap(Heap h) {

  /* COMPLETAR */

} /* liberaHeap */


void * Elemento(Heap h, int k) {
    ImplHeap ih = h;
  
    if ((k < 0) || (k >= ih->tam))
        return NULL;
  
    return ih->vetor[k];

} /* Elemento */
