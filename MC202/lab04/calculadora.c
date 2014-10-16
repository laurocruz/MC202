/***************************************************************** 
 * Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laboratório 04 - Calculadora de polinômios - calculadora.c    *
 *****************************************************************/

/* Módulo de cálculo de expressões pós-fixas sobre uma base de dados     */
/* formada por polinômios em uma variável.                               */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "pilha.h"
#include "polinomios.h"
#include "balloc.h"
#include "boolean.h"

/* Mensagens de erro para este módulo.                                     */

#define MSG_ERRO_NOME_INVALIDO "nome inválido para a base de polinômios."
#define MSG_ERRO_POLINOMIO_NAO_INICIALIZADO "tentativa de recuperar polinômio não inicializado."
#define MSG_ERRO_FALTA_OPERANDO "número insuficiente de operandos."
#define MSG_ERRO_FALTA_OPERADOR  "número insuficiente de operandores."
#define MSG_ERRO_CARACTERE_INVALIDO "caractere inválido."

#define IMPRIME_ERRO(msg)  {printf("Erro: %s\n",msg); exit(0); }

#define TAM_BASE 5
Polinomio vetorPoli[TAM_BASE];

void InicializaBasePolinomios() {
/* Inicializa polinômios com NULL, indicando que não há polinômios       */
/* válidos na base.                                                      */ 
  int i;
  for (i = 0; i < TAM_BASE; i++)
    vetorPoli[i] = NULL;
}

Polinomio RecuperaPolinomio(char x) {
/* Retorna o polinômio de nome x.                                        */
  Polinomio poli;
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    poli =  vetorPoli[x - 'A'];
  else {
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
    return NULL;
  }
  
  if (poli == NULL)
    IMPRIME_ERRO(MSG_ERRO_POLINOMIO_NAO_INICIALIZADO);

  return poli;
}

void ArmazenaPolinomio(char x, Polinomio p) {
/* Armazena o polinômio p sob o nome x na base.                          */
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    vetorPoli[x - 'A'] = p;
  else 
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
}

/*** Cálculo da expressão                                                 */

/* Definição dos elementos da pilha. Polinômios temporários devem ser     */
/* liberados após terem sido utilizados. Polinômios da base só são        */
/* liberados quando o usuário invoca libera.                              */ 
typedef struct ElemPilha {
  Polinomio poli;
  Boolean temp; 
} ElemPilha;

ElemPilha* VerificaDesempilha (Pilha* pilha) {
/* Desempilha um elemento, enviando uma mensagem de erro caso a pilha      */
/* esteja vazia.                                                           */
  if (PilhaVazia(pilha)) {
    IMPRIME_ERRO(MSG_ERRO_FALTA_OPERANDO);
    return NULL;
  }
  return (ElemPilha*) Desempilha(pilha);
}

void EmpilhaOperando(Pilha* pilha, Polinomio poli, Boolean temp) {
/* Cria e empilha um nó do tipo ElemPilha.                                 */
  ElemPilha *elem = MALLOC (sizeof(ElemPilha));
  elem->poli = poli; 
  elem->temp = temp; 
  Empilha (pilha, elem);
}

 Boolean Operando(char c) {
/* Verifica se um caractere corresponde a um operando válido.              */
   return (c >= 'a' && c < 'a'+TAM_BASE) || (c >= 'A' && c < 'A'+TAM_BASE);
 }

Polinomio CalcExpr(char* expr) { 
/* Retorna o polinômio referente à expressão dada.                       */
/* O polinômio devolvido é sempre uma nova cópia, mesmo que a            */
/* expressão seja uma variável simples.    */

	int i;
	ElemPilha *elem1, *elem2;
	Polinomio poli1;
	Pilha p;

	CriaPilha(&p); /* Topo da pilha começa na posição -1 */
	
	for (i = 0; expr[i] != '\0'; i++) {
		/* Recebendo um polinômio permanente */
		if (Operando(expr[i])){
			poli1 = RecuperaPolinomio(expr[i]);
			EmpilhaOperando(&p, poli1, false);
		/* Operador unário */
		} else if (expr[i] == '~') {
			
			/* Se a pilha estiver fazia, falta um operando */
			elem1 = VerificaDesempilha(&p);
			
			/* Multiplica todo o vetor por -1 */
			poli1 = MultTermo(elem1->poli, 0, -1.0);
			
			/* Libera o polinômio caso ele for temporário */
			if (elem1->temp)
				LiberaPolinomio(elem1->poli);
			
			FREE(elem1);
			
			EmpilhaOperando(&p, poli1, true);
		
		/* Operadores binários */
		} else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*') {
			
			/* Se a pilha não tiver pelo menos dois elementos empilhados, falta operando */
			elem2 = VerificaDesempilha(&p);
			elem1 = VerificaDesempilha(&p);
			
			switch (expr[i]) {
				case '+':
					poli1 = SomaPolinomios(elem1->poli, elem2->poli);
					break;
				case '-':
					poli1 = SubPolinomios(elem1->poli, elem2->poli);
					break;
				case '*':
					poli1 = MultPolinomios(elem1->poli, elem2->poli);
					break;
			}
			
			/* Caso os polinômios do topo da pilha sejam temporários, eles são liberados */
			if (elem2->temp)
				LiberaPolinomio(elem2->poli);

			if (elem1->temp)
				LiberaPolinomio(elem1->poli);
			
			FREE(elem1);
			FREE(elem2);
			
			EmpilhaOperando(&p, poli1, true);
			
		} else IMPRIME_ERRO(MSG_ERRO_CARACTERE_INVALIDO);
	}
	
	/* Se ao final sobrer apenas um elemenento na pilha, a operação foi válida e gerou um polinômio 
	 * final */
	elem1 = VerificaDesempilha(&p);
	
	if (PilhaVazia(&p)) {
		/* Se o último polinômio na pilha não for temporário, é feita uma cópia dele, que será 
		 * retornada */
		if (!elem1->temp) {
			poli1 = MultTermo(elem1->poli, 0, 1.0);
			FREE(elem1);
			return poli1;
		}
		
		/* Se ele for temporário, o prórpio polinômio será retornado */
		poli1 = elem1->poli;
		FREE(elem1);
		return poli1;
		
	/* Caso sobre mais de um elemento na pilha a operação falhou */
	} else {
		/* Desempilhando o resto dos elementos que sobraram na pilha */
		FREE(elem1);
		
		while (!PilhaVazia(&p)) {
			elem1 = Desempilha(&p);
			
			if (elem1->temp)
				LiberaPolinomio(elem1->poli);
			
			FREE(elem1);
		}
		/* Nesse caso, o erro se deve a falta de operadores */
		IMPRIME_ERRO(MSG_ERRO_FALTA_OPERADOR);
	}

	return NULL;

}
