/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratório 07 - Base de dados com árvores de busca simples - base.c *
 * Last modified: 19-10-14                                              *
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
  

Base CriaBase() {
/* Devolve apontador para uma base vazia */
	Base p = (ImplBase)MALLOC(sizeof(NoArv));

	p->esq = p->dir = NULL
	p->(info.ra) = 0;
	p->(info.nome[0]) = '\0';
	
	return p;;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se não existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrário devolve 'false' */

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
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
   

  return false; /* PROVISÓRIO */
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. */

  /****** COMPLETAR ***********/
  return false; /* PROVISÓRIO */

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVISÓRIO */

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */

  /****** COMPLETAR ***********/
  return 0; /* PROVISÓRIO */

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */

    /****** COMPLETAR ***********/

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */

  /****** COMPLETAR ***********/

} /* LiberaBase */
