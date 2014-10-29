/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratório 07 - Base de dados com árvores de busca simples - base.c *
 * Last modified: 29-11-14                                              *
 ************************************************************************/

/*
 * Arquivo base.c: implementação das funções de manipulação da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

typedef struct AuxNoArv {
	Aluno info;                   /* registros de informação */
	struct AuxNoArv *esq,*dir;   /* subárvores */
} NoArv, * ImplBase;
  
int maiorValor(int a, int b) {
	if (a > b)
		return a;
	else return b;
}

Aluno removeFolha (ImplBase *p) {
	Aluno a;
	ImplBase aux;
	
	*p = (*p)->dir;
	
	while ((*p)->esq != NULL)
		*p = (*p)->esq;
	
	a = (*p)->info;
	aux = *p;
	*p = (*p)->dir;
	FREE(aux);
	
	return a;
}

Base CriaBase() {
/* Devolve apontador para uma base vazia */
	
	return NULL;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se não existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */
	Boolean entrou = false;
	ImplBase* b = (ImplBase*) p;

	while (*b != NULL) {
		entrou = true;
		if (a.ra < ((*b)->info).ra)
			b = &((*b)->esq);
		else if (a.ra > ((*b)->info).ra)
			b = &((*b)->dir);
		else return false;
	}
	
	*b = MALLOC(sizeof(NoArv));
	
	(*b)->info = a;
	(*b)->esq = (*b)->dir = NULL;
	
	if (!entrou)
		*p = *b;

	return true;

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
	ImplBase b = (ImplBase) *p;

	while (b != NULL) {
		if (ra < (b->info).ra)
			b = b->esq;
		else if (ra > (b->info).ra)
			b = b->dir;
		else {
			*a = b->info;
			return true;
		}
	}

	return false; /* PROVISÓRIO */
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. */
	ImplBase* b = (ImplBase*) p;
	ImplBase aux;
	
	while (*b != NULL) {
		if (ra < ((*b)->info).ra)
			b = &((*b)->esq);
		else if (ra > ((*b)->info).ra)
			b = &((*b)->dir);
		else {
			if ((*b)->dir == NULL) {
				aux = *b;
				*b = (*b)->esq;
				FREE(aux);
			} else if ((*b)->esq == NULL) {
				aux = *b;
				*b = (*b)->dir;
				FREE(aux);
				
			} else (*b)->info = removeFolha(b);
			
			return true;
		}
	}

	return false;

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
	int hEsq, hDir;
	ImplBase* b = (ImplBase*) p;
	Base* es, di;
	
	if (*b == NULL)
		return 0;
	
	es = (Base*) &((*b)->esq);
	di = (Base*) &((*b)->dir);
	
	hEsq = AlturaBase(es);
	hDir = AlturaBase(di);
	
	return maiorValor(hEsq, hDir) + 1;

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */
	ImplBase* b = (ImplBase*) p;
	Base* es, di;
	
	if (*b == NULL)
		return 0;
	
	es = (Base*) &((*b)->esq);
	di = (Base*) &((*b)->dir);
	
	
	return NumeroNosBase(es) + NumeroNosBase(di) + 1;

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */
	ImplBase b = (ImplBase) *p;
	Base* es, in;
	
	while (b != NULL) {
		es = (Base*) &(b->esq);
		in = (Base*) &(b->info);
		PercorreBase(es, Visita);
		Visita(in);
		b = b->dir;
	}

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
	ImplBase* b = (ImplBase*) p;
	Base* es, di;
	
	if (*p != NULL) {
		es = (Base*) &((*b)->esq);
		di = (Base*) &((*b)->dir);
		LiberaBase(es);
		LiberaBase(di);
		FREE(*p);
	}

} /* LiberaBase */
