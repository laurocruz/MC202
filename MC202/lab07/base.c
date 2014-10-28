/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laborat�rio 07 - Base de dados com �rvores de busca simples - base.c *
 * Last modified: 19-10-14                                              *
 ************************************************************************ /

/*
 * Arquivo base.c: implementa��o das fun��es de manipula��o da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

typedef struct AuxNoArv {
	Aluno info;                   /* registros de informa��o */
	struct AuxNoArv *esq,*dir;   /* sub�rvores */
} NoArv, * ImplBase;
  
int maiorValor(int a, int b) {
	if (a > b)
		return a;
	else return b;
}

Aluno removeFolha (Base *p) {
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
	Base bas;
	ImplBase p = MALLOC(sizeof(NoArv));

	p->esq = p->dir = NULL
	(p->info).ra = 0;
	((p->info).nome)[0] = '\0';
	
	bas = p;
	
	return bas;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */

	while (*p != NULL) {
		if (a.ra < ((*p)->info).ra)
			*p = (*p)->esq;
		else if (a.ra > ((*p)->info).ra)
			*p = (*p)->dir;
		else return false;
	}
	
	*p = MALLOC(sizeof(NoArv));
	
	(*p)->info = a;
	(*p)->esq = (*p)->dir = NULL;

	return true;

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
	
	while (*p != NULL) {
		if (ra < ((*p)->info).ra)
			*p = (*p)->esq;
		else if (ra > ((*p)->info).ra)
			*p = (*p)->dir;
		else {
			*a = (*p)->info;
			return true;
		}
	}

	return false; /* PROVIS�RIO */
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */
	ImplBase aux;
	
	while (*p != NULL) {
		if (ra < ((*p)->info).ra)
			*p = (*p)->esq;
		else if (ra > ((*p)->info).ra)
			*p = (*p)->dir;
		else {
			if ((*p)->dir == NULL) {
				aux = *p;
				*p = (*p)->esq;
				FREE(aux);
				
			} else (*p)->info = removeFolha(p);
			
			return true;
		}
	}

	return false;

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
	int hEsq, hDir;
	
	if (*p == NULL)
		return 0;
	
	hEsq = AlturaBase(&((*p)->esq));
	hDir = AlturaBase(&((*p)->dir));
	
	return maiorValor(hEsq, hDir) + 1;

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o n�mero de n�s da base 'p'. */
	if (*p == NULL)
		return 0;
	
	return NumeroNosBase(&((*p)->esq)) + NumeroNosBase(&((*p)->dir)) + 1;

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */

	while (*p != NULL) {
		PercorreBase(&((*p)->esq), Visita());
		Visita(&((*p)->info));
		*p = (*p)->dir;
	}

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

	if (*p != NULL) {
		LiberaBase(&((*p)->esq));
		LiberaBase(&((*p)->dir));
		FREE (*p);
	}

} /* LiberaBase */
