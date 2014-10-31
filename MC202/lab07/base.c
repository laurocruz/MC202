/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laborat�rio 07 - Base de dados com �rvores de busca simples - base.c *
 * Last modified: 31-10-14                                              *
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
  
int maiorValor(int a, int b) {
/* Retorna o maior valor inteiro */
	if (a > b) return a;
	else return b;
}

String removeFolha (ImplBase *p, int *ra) {
/* Fun��o que remove o aluno em um n� com dois filhos */
	String s;
	ImplBase out;

	/* Encontra o menor n� de menor ra da sub�rvore */
	while ((*p)->esq != NULL)
		p = &((*p)->esq); 

	/* Armazena o ponteiro da string do nome do aluno que ser� retornado */
	s = ((*p)->info).nome;
	/* Troca o valor do RA no n� que era pra ser originalmente retirado */
	*ra = ((*p)->info).ra;	

	
	out = *p;
	/* Altera o apontador do n� pai */
	*p = (*p)->dir;
	/* Libera a mem�ria alocada pela n� */
	FREE(out);

	return s;
}

Base CriaBase() {
/* Devolve apontador para uma base vazia */
	return NULL;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */
	Boolean entrou = false;
	ImplBase* b = (ImplBase*) p; /* Casting da Base para ImplBase */

	/* Se n�o entrar nem uma vez, *b � nulo e a base � vazia */
	while (*b != NULL) {
		entrou = true;
		/* Percorre a �rvore de acordo com as propriedades de �rvore de busca */
		if (a.ra < ((*b)->info).ra)
			b = &((*b)->esq);
		else if (a.ra > ((*b)->info).ra)
			b = &((*b)->dir);
		else return false; /* Se encontro ra, o aluno j� esxiste e n�o � poss�vel inser�-lo */
	}
	
	/* Cria o novo n� com as informa��es do aluno */
	*b = MALLOC(sizeof(NoArv));
	
	(*b)->info = a;
	(*b)->esq = (*b)->dir = NULL;
	
	/* Se a �rvore for vazia, � preciso passar para o apontador da raiz o n� raiz */
	if (!entrou)
		*p = *b;

	return true;

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */
	ImplBase b = (ImplBase) *p; /* Casting de Base para ImplBase */

	while (b != NULL) {
		/* Percorre a �rvore de acordo com as propriedades de �rvore de busca */
		if (ra < (b->info).ra)
			b = b->esq;
		else if (ra > (b->info).ra)
			b = b->dir;
		else {
		/* Se encontra o RA, o aluno existe na �rvore e suas informa��es armazenadas */
			*a = b->info;
			return true;
		}
	}
	
	/* N�o encontrou o aluno */
	return false; 
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */
	ImplBase* b = (ImplBase*) p; /* Casting de *Base para *ImplBase */
	ImplBase aux;
	
	while (*b != NULL) {
		/* Percorre a �rvore de acordo com as propriedades de �rvore de busca */
		if (ra < ((*b)->info).ra)
			b = &((*b)->esq);
		else if (ra > ((*b)->info).ra)
			b = &((*b)->dir);
		else { /* Encontra o RA */	
			/* Se pelo menos uma das sub�rvores do n� for nula � poss�vel remov�-lo */
			if ((*b)->dir == NULL || (*b)->esq == NULL) {
				aux = *b;
			
				/* Se a sub�rvore direita for nula, o pai passa a aponta para a sub�rvore esquerda */
				if ((*b)->dir == NULL) *b = (*b)->esq;
				/* Se a sub�rvore esquerda for nula, o pai passa a apontar para a sub�rvore direita*/
				else *b = (*b)->dir;
				
				/* Liberando o vetor do nome do aluno e o n� da �rvore */
				FREE((aux->info).nome);
				FREE(aux);
				
			/* O n� a ser tirado apresenta ambas as sub�rvores */
			} else { 
				/* Libera o vetor do nome do aluno a ser removido */
				FREE(((*b)->info).nome);
				/* Retorna o apomtador para o nome do novo aluno e altera o valor do ra do n� */
				((*b)->info).nome = removeFolha(&((*b)->dir), &(((*b)->info).ra));
			}
			/* Foi poss�vel realizar a remo��o */
			return true;
		}
	}

	/* O aluno a se remover n�o existe na �rvore */
	return false;

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
	int hEsq, hDir;
	ImplBase* b = (ImplBase*) p; /* Casting de *Base para *ImplBase */
	Base* es, di;
	
	/* Quando a �rvore for nula, sua altura � 0 */
	if (*b == NULL)
		return 0;

	/* Casting de *ImplBase para *Base */
	es = (Base*) &((*b)->esq);
	di = (Base*) &((*b)->dir);
	
	/* Obt�m a altura das sub�rvores esquerda e direita */
	hEsq = AlturaBase(es);
	hDir = AlturaBase(di);
	
	/* A altura da �rvore � a altura da maior sub�rvore mais 1 (n� raiz) */
	return maiorValor(hEsq, hDir) + 1;

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o n�mero de n�s da base 'p'. */
	ImplBase* b = (ImplBase*) p; /* Casting de *Base para *ImplBase */
	Base* es, di;
	
	/* Se a �rvore for nula, ela n�o tem nenhum n� */
	if (*b == NULL)
		return 0;
	
	/* Casting de *ImplBase para *Base */
	es = (Base*) &((*b)->esq);
	di = (Base*) &((*b)->dir);
	
	/* A quantidade de n�s da �rvore � igual a quantidade de n�s das sub�rvores esquerda e direita
	 * mais 1 (n� raiz) */
	return NumeroNosBase(es) + NumeroNosBase(di) + 1;

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a fun��o Visita
   para todos os elementos. */
	ImplBase b = (ImplBase) *p; /* Casting de Base para ImplBase */
	Base* es, in;
	
	while (b != NULL) {
		/* Casting de *ImplBase para *Base */
		es = (Base*) &(b->esq);
		in = (Base*) &(b->info);
		PercorreBase(es, Visita); /* Percorre �rvore esquerda */
		Visita(in); /* Visita as informa��es do n� */
		b = b->dir; /* Percorre �rvore direita */
	}

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os n�s da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
	ImplBase b = (ImplBase) *p; /* Casting de Base para ImplBase */
	Base* es, di;
	
	if (b != NULL) {
		/* Casting de *ImplBase para *Base */
		es = (Base*) &(b->esq);
		di = (Base*) &(b->dir);
		LiberaBase(es); /* Libera sub�rvore esquerda */
		LiberaBase(di); /* Libera sub�rvores esquerda */
		FREE((b->info).nome); /* Libera string do nome do aluno */
		FREE(b); /* Libera n� */
	}

} /* LiberaBase */
