/*****************************************************************
 * Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laboratório 04 - Calculadora de polinomios - pilha.c          *
 ******************************************************************/

/* Implementação de pilhas. Os elementos empilhados são do tipo void*.     */

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

/* Mensagens de erro para este módulo.                                     */
#define MSG_ERRO_PILHA_CHEIA "número máximo de elementos na pilha excedido."
#define MSG_ERRO_PILHA_VAZIA "tentativa de desempilhar elemento de pilha vazia."

#define IMPRIME_ERRO(msg)  {printf("%s\n",msg); exit(0); }

void CriaPilha (Pilha* p) {
/* Inicializa uma pilha.                                                    */

	p->topo = -1;
}

Boolean PilhaVazia (Pilha* p) {
/* Verifica se a pilha está vazia.                                         */
	
	if (p->topo == -1)
		return true;
	else 
		return false;
}

void Empilha (Pilha* p, void *elem) {
/* Empilha um elemento na pilha.                                           */
	
	if (p->topo == MAX_ELEM_PILHA) 
		IMPRIME_ERRO(MSG_ERRO_PILHA_CHEIA);
		
	(p->topo)++;
	p->vetor[p->topo] = elem;
}

void* Desempilha (Pilha* p) {
/* Desempilha um elemento da pilha.                                        */

	(p->topo)--;

	return p->vetor[p->topo + 1];
	
}

