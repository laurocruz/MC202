/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratório 07 - Base de dados com árvores de busca simples - base.c *
 * Last modified: 31-10-14                                              *
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
/* Retorna o maior valor inteiro */
	if (a > b) return a;
	else return b;
}

String removeFolha (ImplBase *p, int *ra) {
/* Função que remove o aluno em um nó com dois filhos */
	String s;
	ImplBase out;

	/* Encontra o menor nó de menor ra da subárvore */
	while ((*p)->esq != NULL)
		p = &((*p)->esq); 

	/* Armazena o ponteiro da string do nome do aluno que será retornado */
	s = ((*p)->info).nome;
	/* Troca o valor do RA no nó que era pra ser originalmente retirado */
	*ra = ((*p)->info).ra;	

	
	out = *p;
	/* Altera o apontador do nó pai */
	*p = (*p)->dir;
	/* Libera a memória alocada pela nó */
	FREE(out);

	return s;
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
	ImplBase* b = (ImplBase*) p; /* Casting da Base para ImplBase */

	/* Se não entrar nem uma vez, *b é nulo e a base é vazia */
	while (*b != NULL) {
		entrou = true;
		/* Percorre a árvore de acordo com as propriedades de árvore de busca */
		if (a.ra < ((*b)->info).ra)
			b = &((*b)->esq);
		else if (a.ra > ((*b)->info).ra)
			b = &((*b)->dir);
		else return false; /* Se encontro ra, o aluno já esxiste e não é possível inserí-lo */
	}
	
	/* Cria o novo nó com as informações do aluno */
	*b = MALLOC(sizeof(NoArv));
	
	(*b)->info = a;
	(*b)->esq = (*b)->dir = NULL;
	
	/* Se a árvore for vazia, é preciso passar para o apontador da raiz o nó raiz */
	if (!entrou)
		*p = *b;

	return true;

} /* InsereBase */
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrário devolve 'false'. 'a' conterá 
   os dados do aluno, se encontrado. */
	ImplBase b = (ImplBase) *p; /* Casting de Base para ImplBase */

	while (b != NULL) {
		/* Percorre a árvore de acordo com as propriedades de árvore de busca */
		if (ra < (b->info).ra)
			b = b->esq;
		else if (ra > (b->info).ra)
			b = b->dir;
		else {
		/* Se encontra o RA, o aluno existe na árvore e suas informações armazenadas */
			*a = b->info;
			return true;
		}
	}
	
	/* Não encontrou o aluno */
	return false; 
  
} /* ConsultaBase */

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' pôde ser removido da
   base 'p';  caso contrário devolve 'false'. */
	ImplBase* b = (ImplBase*) p; /* Casting de *Base para *ImplBase */
	ImplBase aux;
	
	while (*b != NULL) {
		/* Percorre a árvore de acordo com as propriedades de árvore de busca */
		if (ra < ((*b)->info).ra)
			b = &((*b)->esq);
		else if (ra > ((*b)->info).ra)
			b = &((*b)->dir);
		else { /* Encontra o RA */	
			/* Se pelo menos uma das subárvores do nó for nula é possível removê-lo */
			if ((*b)->dir == NULL || (*b)->esq == NULL) {
				aux = *b;
			
				/* Se a subárvore direita for nula, o pai passa a aponta para a subárvore esquerda */
				if ((*b)->dir == NULL) *b = (*b)->esq;
				/* Se a subárvore esquerda for nula, o pai passa a apontar para a subárvore direita*/
				else *b = (*b)->dir;
				
				/* Liberando o vetor do nome do aluno e o nó da árvore */
				FREE((aux->info).nome);
				FREE(aux);
				
			/* O nó a ser tirado apresenta ambas as subárvores */
			} else { 
				/* Libera o vetor do nome do aluno a ser removido */
				FREE(((*b)->info).nome);
				/* Retorna o apomtador para o nome do novo aluno e altera o valor do ra do nó */
				((*b)->info).nome = removeFolha(&((*b)->dir), &(((*b)->info).ra));
			}
			/* Foi possível realizar a remoção */
			return true;
		}
	}

	/* O aluno a se remover não existe na árvore */
	return false;

} /* RemoveBase */

int AlturaBase(Base *p) {
/* Devolve a altura da base 'p'. */
	int hEsq, hDir;
	ImplBase* b = (ImplBase*) p; /* Casting de *Base para *ImplBase */
	Base* es, di;
	
	/* Quando a árvore for nula, sua altura é 0 */
	if (*b == NULL)
		return 0;

	/* Casting de *ImplBase para *Base */
	es = (Base*) &((*b)->esq);
	di = (Base*) &((*b)->dir);
	
	/* Obtém a altura das subárvores esquerda e direita */
	hEsq = AlturaBase(es);
	hDir = AlturaBase(di);
	
	/* A altura da árvore é a altura da maior subárvore mais 1 (nó raiz) */
	return maiorValor(hEsq, hDir) + 1;

} /* AlturaBase */

int NumeroNosBase(Base *p) {
/* Devolve o número de nós da base 'p'. */
	ImplBase* b = (ImplBase*) p; /* Casting de *Base para *ImplBase */
	Base* es, di;
	
	/* Se a árvore for nula, ela não tem nenhum nó */
	if (*b == NULL)
		return 0;
	
	/* Casting de *ImplBase para *Base */
	es = (Base*) &((*b)->esq);
	di = (Base*) &((*b)->dir);
	
	/* A quantidade de nós da árvore é igual a quantidade de nós das subárvores esquerda e direita
	 * mais 1 (nó raiz) */
	return NumeroNosBase(es) + NumeroNosBase(di) + 1;

} /* NumeroNosBase */


void PercorreBase(Base *p, void (*Visita)(Aluno*)) {
/* Executa um percurso inordem na base, invocando a função Visita
   para todos os elementos. */
	ImplBase b = (ImplBase) *p; /* Casting de Base para ImplBase */
	Base* es, in;
	
	while (b != NULL) {
		/* Casting de *ImplBase para *Base */
		es = (Base*) &(b->esq);
		in = (Base*) &(b->info);
		PercorreBase(es, Visita); /* Percorre árvore esquerda */
		Visita(in); /* Visita as informações do nó */
		b = b->dir; /* Percorre árvore direita */
	}

}   /* PercorreBase */

void LiberaBase(Base *p) {
/* Libera todos os nós da base apontada por 'p', bem 
   como todas as cadeias que guardam os nomes. */
	ImplBase b = (ImplBase) *p; /* Casting de Base para ImplBase */
	Base* es, di;
	
	if (b != NULL) {
		/* Casting de *ImplBase para *Base */
		es = (Base*) &(b->esq);
		di = (Base*) &(b->dir);
		LiberaBase(es); /* Libera subárvore esquerda */
		LiberaBase(di); /* Libera subárvores esquerda */
		FREE((b->info).nome); /* Libera string do nome do aluno */
		FREE(b); /* Libera nó */
	}

} /* LiberaBase */
