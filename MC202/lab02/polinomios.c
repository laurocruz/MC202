/* Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laborat�rio 02 - Polin�mios                                   */

/* Este m�dulo implementa opera��es sobre polin�mios em uma vari�vel.   */
/* Cada polin�mio � representado por uma lista ligada circular, com n�   */
/* cabe�a. Os n�s da lista representam os termos n�o nulos do polin�mio */
/* em ordem crescente dos seus expoentes. O n� cabe�a tem expoente '-1'.*/

#include "polinomios.h"
#include "balloc.h"
#include <stdio.h>

/*-----------------------  Fun��o auxiliar  ----------------------------*/

void InsereTermoAux(Polinomio p, int e, float c) {
/* Insere o termo '(e,c)' ap�s o n� apontado por 'p'.                  */

	Polinomio q;
	
	q = MALLOC(sizeof(Termo));
	
	q->prox = p->prox;
	p->prox = q;
	q->expo = e;
	q->coef = c;

} /* InsereTermoAux */



/*---------------- Implementa��o das fun��es da interface --------------*/


void ImprimePolinomio(Polinomio p) {
/* Imprime, em ordem crescente dos expoentes, os termos do              */
/* n�o nulos do 'p'. No caso do polin�mio identicamente nulo,           */
/* imprime as palavras "Polin�mio nulo".                                */

  if (p==NULL) {
    printf("Polin�mio inv�lido\n");
    return;
  }
  
  if (p->prox==p) {
    printf("Polin�mio nulo\n");
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
/* Devolve um novo polin�mio identicamente nulo.                        */

	Polinomio p;
	
	p = MALLOC(sizeof(Termo));
	
	p->expo = -1;
	p->prox = p;
	
	return p;

} /* CriaPolinomioNulo */



void LiberaPolinomio(Polinomio p) {
/* Libera toda a mem�ria din�mica ocupada por um polin�mio.             */

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
/* Verifica se o polin�mio 'p' � identicamente nulo.                    */

	if (p->prox == p)
		return true;
	else
		return false;

} /* PolinomioNulo */


void InsereTermo(Polinomio p, int e, float c) {
/* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os      */
/* termos ordenados. Sup�e que n�o existe ainda em 'p' um termo com     */
/* expoente 'e', e que 'c' n�o � zero.                                  */

	Polinomio q;

	q = p->prox;

	while ((q->expo < e) && (q->expo != -1)) {
		p = q;
		q = q->prox;
	}
	
	InsereTermoAux(p, e, c);

} /* InsereTermo */


Polinomio SomaPolinomios(Polinomio a, Polinomio b) {
/* Devolve a soma dos polin�mios 'a' e 'b'. N�o altera os polin�mios    */
/* dados. Termos nulos n�o s�o inseridos no resultados.                 */

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
/* Devolve o polin�mio 'p' multiplicado pelo termo '(e,c)'. Sup�e       */
/* que 'c' n�o � nulo. N�o altera o polin�mio dado.                    */

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
/* Devolve o produto dos polin�mios 'a' e 'b'. N�o altera os polin�mios */
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
