/* Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laboratório 02 - Polinômios                                   */

/* Este módulo implementa operações sobre polinômios em uma variável.   */
/* Cada polinômio é representado por uma lista ligada circular, com nó   */
/* cabeça. Os nós da lista representam os termos não nulos do polinômio */
/* em ordem crescente dos seus expoentes. O nó cabeça tem expoente '-1'.*/

#include "polinomios.h"
#include "balloc.h"
#include <stdio.h>

/*-----------------------  Função auxiliar  ----------------------------*/

void InsereTermoAux(Polinomio p, int e, float c) {
/* Insere o termo '(e,c)' após o nó apontado por 'p'.                  */

	Polinomio q;
	
	q = MALLOC(sizeof(Termo));
	
	q->prox = p->prox;
	p->prox = q;
	q->expo = e;
	q->coef = c;

} /* InsereTermoAux */



/*---------------- Implementação das funções da interface --------------*/


void ImprimePolinomio(Polinomio p) {
/* Imprime, em ordem crescente dos expoentes, os termos do              */
/* não nulos do 'p'. No caso do polinômio identicamente nulo,           */
/* imprime as palavras "Polinômio nulo".                                */

  if (p==NULL) {
    printf("Polinômio inválido\n");
    return;
  }
  
  if (p->prox==p) {
    printf("Polinômio nulo\n");
    return;
  }
  
  p = p->prox;
  while (p->expo!=-1) {
    printf("(%2d,%5.1f) ",p->expo,p->coef);
    p = p->prox;
  }
  printf("\n");

} /* ImprimePolinomio */


Polinomio CriaPolinomioNulo() {
/* Devolve um novo polinômio identicamente nulo.                        */

	Polinomio p;
	
	p = MALLOC(sizeof(Termo));
	
	p->expo = -1;
	p->prox = p;
	
	return p;

} /* CriaPolinomioNulo */



void LiberaPolinomio(Polinomio p) {
/* Libera toda a memória dinâmica ocupada por um polinômio.             */

	Polinomio q;
	
	if (PolinomioNulo(p))
		FREE(p);
	else {
		p = p->prox;
		q = p->prox;
		
		while (p->expo != -1) {
			FREE(p);
			p = q;
			q = q->prox;
		}
		FREE(p);
	}
}

Boolean PolinomioNulo(Polinomio p) {
/* Verifica se o polinômio 'p' é identicamente nulo.                    */

	if (p->prox == p)
		return true;
	else
		return false;

} /* PolinomioNulo */


void InsereTermo(Polinomio p, int e, float c) {
/* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os      */
/* termos ordenados. Supõe que não existe ainda em 'p' um termo com     */
/* expoente 'e', e que 'c' não é zero.                                  */

	Polinomio q;

	q = p->prox;

	while ((q->expo < e) && (q->expo != -1)) {
		p = q;
		q = q->prox;
	}
	
	InsereTermoAux(p, e, c);

} /* InsereTermo */


Polinomio SomaPolinomios(Polinomio a, Polinomio b) {
/* Devolve a soma dos polinômios 'a' e 'b'. Não altera os polinômios    */
/* dados. Termos nulos não são inseridos no resultados.                 */

	Polinomio q;
	
	q = CriaPolinomioNulo();
	
	a = a->prox;
	b = b->prox;
	
	while ((a->expo != -1) && (b->expo != -1)) {
		if (a->expo < b->expo) {
			InsereTermoAux(q, a->expo, a->coef);
			a = a->prox;
			q = q->prox;
		} else if (a->expo > b->expo) {
			InsereTermoAux(q, b->expo, b->coef);
			b = b->prox;
			q = q->prox;
		} else {
			if (a->coef + b->coef) {
				InsereTermoAux(q, a->expo, a->coef + b->coef);
				q = q->prox;
			}
			
			a = a->prox;
			b = b->prox;
		}
	}
	
	while (a->expo != -1) {
		InsereTermoAux(q, a->expo, a->coef);
		a = a->prox;
		q = q->prox;
	}
	while (b->expo != -1) {
		InsereTermoAux(q, b->expo, b->coef);
		b = b->prox;
		q = q->prox;
	}
	
	q = q->prox;

	return q;

} /* SomaPolinomios */


Polinomio MultTermo(Polinomio p, int e, float c) {
/* Devolve o polinômio 'p' multiplicado pelo termo '(e,c)'. Supõe       */
/* que 'c' não é nulo. Não altera o polinômio dado.                    */

	Polinomio q;
	
	q = CriaPolinomioNulo();
	
	p = p->prox;
	
	while (p->expo != -1) {
		InsereTermoAux(q, 0, 0);
		q = q->prox;
		q->expo = p->expo + e;
		q->coef = p->coef * c;
		p = p->prox;
	}
	
	q = q->prox;
	
	return q;

} /* MultTermo */

Polinomio MultPolinomios(Polinomio a, Polinomio b) {
/* Devolve o produto dos polinômios 'a' e 'b'. Não altera os polinômios */
/* dados.                                                               */

	Polinomio p, q, t;
	
	if (PolinomioNulo(a) || PolinomioNulo(b)) {
		p = CriaPolinomioNulo();
		return p;
	}
		
	
	b = b->prox;
	p = MultTermo(a, b->expo, b->coef);
	b = b->prox;
	
	while (b->expo != -1) {
		q = MultTermo(a, b->expo, b->coef);
		t = p;
		p = SomaPolinomios(t, q);
		LiberaPolinomio(t);
		LiberaPolinomio(q);
		b = b->prox;
	}
	
	return p;

} /* MultPolinomios */
