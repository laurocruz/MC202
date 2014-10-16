/***************************************************************** 
 * Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laborat�rio 04 - Calculadora de polin�mios - calculadora.c    *
 *****************************************************************/

/* M�dulo de c�lculo de express�es p�s-fixas sobre uma base de dados     */
/* formada por polin�mios em uma vari�vel.                               */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "pilha.h"
#include "polinomios.h"
#include "balloc.h"
#include "boolean.h"

/* Mensagens de erro para este m�dulo.                                     */

#define MSG_ERRO_NOME_INVALIDO "nome inv�lido para a base de polin�mios."
#define MSG_ERRO_POLINOMIO_NAO_INICIALIZADO "tentativa de recuperar polin�mio n�o inicializado."
#define MSG_ERRO_FALTA_OPERANDO "n�mero insuficiente de operandos."
#define MSG_ERRO_FALTA_OPERADOR  "n�mero insuficiente de operandores."
#define MSG_ERRO_CARACTERE_INVALIDO "caractere inv�lido."

#define IMPRIME_ERRO(msg)  {printf("Erro: %s\n",msg); exit(0); }

#define TAM_BASE 5
Polinomio vetorPoli[TAM_BASE];

void InicializaBasePolinomios() {
/* Inicializa polin�mios com NULL, indicando que n�o h� polin�mios       */
/* v�lidos na base.                                                      */ 
  int i;
  for (i = 0; i < TAM_BASE; i++)
    vetorPoli[i] = NULL;
}

Polinomio RecuperaPolinomio(char x) {
/* Retorna o polin�mio de nome x.                                        */
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
/* Armazena o polin�mio p sob o nome x na base.                          */
  x = toupper(x);
  if (x >= 'A' && x < 'A' + TAM_BASE) 
    vetorPoli[x - 'A'] = p;
  else 
    IMPRIME_ERRO(MSG_ERRO_NOME_INVALIDO);
}

/*** C�lculo da express�o                                                 */

/* Defini��o dos elementos da pilha. Polin�mios tempor�rios devem ser     */
/* liberados ap�s terem sido utilizados. Polin�mios da base s� s�o        */
/* liberados quando o usu�rio invoca libera.                              */ 
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
/* Cria e empilha um n� do tipo ElemPilha.                                 */
  ElemPilha *elem = MALLOC (sizeof(ElemPilha));
  elem->poli = poli; 
  elem->temp = temp; 
  Empilha (pilha, elem);
}

 Boolean Operando(char c) {
/* Verifica se um caractere corresponde a um operando v�lido.              */
   return (c >= 'a' && c < 'a'+TAM_BASE) || (c >= 'A' && c < 'A'+TAM_BASE);
 }

Polinomio CalcExpr(char* expr) { 
/* Retorna o polin�mio referente � express�o dada.                       */
/* O polin�mio devolvido � sempre uma nova c�pia, mesmo que a            */
/* express�o seja uma vari�vel simples.    */

	int i;
	ElemPilha *elem1, *elem2;
	Polinomio poli1;
	Pilha p;

	CriaPilha(&p); /* Topo da pilha come�a na posi��o -1 */
	
	for (i = 0; expr[i] != '\0'; i++) {
		/* Recebendo um polin�mio permanente */
		if (Operando(expr[i])){
			poli1 = RecuperaPolinomio(expr[i]);
			EmpilhaOperando(&p, poli1, false);
		/* Operador un�rio */
		} else if (expr[i] == '~') {
			
			/* Se a pilha estiver fazia, falta um operando */
			elem1 = VerificaDesempilha(&p);
			
			/* Multiplica todo o vetor por -1 */
			poli1 = MultTermo(elem1->poli, 0, -1.0);
			
			/* Libera o polin�mio caso ele for tempor�rio */
			if (elem1->temp)
				LiberaPolinomio(elem1->poli);
			
			FREE(elem1);
			
			EmpilhaOperando(&p, poli1, true);
		
		/* Operadores bin�rios */
		} else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*') {
			
			/* Se a pilha n�o tiver pelo menos dois elementos empilhados, falta operando */
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
			
			/* Caso os polin�mios do topo da pilha sejam tempor�rios, eles s�o liberados */
			if (elem2->temp)
				LiberaPolinomio(elem2->poli);

			if (elem1->temp)
				LiberaPolinomio(elem1->poli);
			
			FREE(elem1);
			FREE(elem2);
			
			EmpilhaOperando(&p, poli1, true);
			
		} else IMPRIME_ERRO(MSG_ERRO_CARACTERE_INVALIDO);
	}
	
	/* Se ao final sobrer apenas um elemenento na pilha, a opera��o foi v�lida e gerou um polin�mio 
	 * final */
	elem1 = VerificaDesempilha(&p);
	
	if (PilhaVazia(&p)) {
		/* Se o �ltimo polin�mio na pilha n�o for tempor�rio, � feita uma c�pia dele, que ser� 
		 * retornada */
		if (!elem1->temp) {
			poli1 = MultTermo(elem1->poli, 0, 1.0);
			FREE(elem1);
			return poli1;
		}
		
		/* Se ele for tempor�rio, o pr�rpio polin�mio ser� retornado */
		poli1 = elem1->poli;
		FREE(elem1);
		return poli1;
		
	/* Caso sobre mais de um elemento na pilha a opera��o falhou */
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
