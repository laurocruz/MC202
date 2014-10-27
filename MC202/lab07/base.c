/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laborat�rio 07 - Base de dados com �rvores de busca simples - base.c *
 * Last modified: 19-10-14                                              *
 ************************************************************************/

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
  

Base CriaBase() {
/* Devolve apontador para uma base vazia */
	Base p = (ImplBase)MALLOC(sizeof(NoArv));

	p->esq = p->dir = NULL
	p->(info.ra) = 0;
	p->(info.nome[0]) = '\0';
	
	return p;;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */

	while (*p != NULL) {
		if (a.ra < (*p)->info.ra)
			*p = (*p)->esq;
		else if (a.ra > (*p)->info.ra)
			*p = (*p)->dir;
		else return false;
	}
	
	*p = (ImplBase)MALLOC(sizeof(NoArv));
	
	(*p)->info = a;
	(*p)->esq = (*p)->dir = NULL;

	return true;

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
   

  return false; /* PROVIS�RIO */
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */

  /****** COMPLETAR ***********/
  return false; /* PROVIS�RIO */

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVIS�RIO */

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o n�mero de n�s da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVIS�RIO */

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */

    /****** COMPLETAR ***********/

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

  /****** COMPLETAR ***********/

} /* LiberaBase */
