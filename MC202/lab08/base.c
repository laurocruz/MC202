/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratório 08 - Base de Dados com Arvore AVL - base.c              *
 * Last modified: 31-10-14                                              *
 ************************************************************************/

/*
 * Arquivo base.c: implementa��o das fun��es de manipula��o da base.
 */

#include <stdio.h>
#include "base.h"
#include "balloc.h"

#include "imprimearvore.h"

typedef struct AuxNoArv {
    Aluno info;                  /* registros de informa��o */
    struct AuxNoArv *esq,*dir;   /* sub�rvores */
    short int bal;               /* fator de balanceamento */
} NoArv, * ImplBase;

/* ============================================================ */

/* Fun��o ImprimeBase para produzir a representa��o gr�fica */
/* Pode ajudar na depura��o */

char cadeiainfo[7] = "0000000"; /* conter� os d�gitos do RA */
char *vazia = "�rvore vazia\n";
Boolean altIn = false, altRe = false;

int maiorValor(int a, int b) {
/* Retorna o maior valor inteiro */
	if (a > b) return a;
	else return b;
}

ImplBase esq(ImplBase a, int d) {
    /* Sup�e a!=NULL */
    return a->esq;
}

ImplBase dir(ImplBase a, int d) {
    /* Sup�e a!=NULL */
    return a->dir;
}

char *info(ImplBase a, int d) {
    /* Sup�e a!=NULL */
    sprintf(cadeiainfo,"%6d", (a->info).ra);
    /* cadeiainfo[0] = (a->info)->ra;*/
    return cadeiainfo;
}

void ImprimeBase(Base *p) {
    /* Imprime a base sob a forma de uma �rvore 'deitada'. */
    ImplBase q = (ImplBase)(*p);
    printf("\n");
    ImprimeArvore(q,(subarvfunc*)esq,(subarvfunc*)dir,(infofunc*)info,NULL,1,vazia);
    printf("\n");
}

/* ============================================================ */


Base CriaBase() {
/* Devolve apontador para uma base vazia */
    return NULL;
}

Base SubEsq(Base *p) {
/* Devolve a sub�rvore esquerda da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */
    ImplBase b = (ImplBase) (*p);

    return (Base) b->esq;
}

Base SubDir(Base *p) {
/* Devolve a sub�rvore direita da base 'p' se n�o for vazia; caso
   contr�rio devolve NULL. */
    ImplBase b = (ImplBase) (*p);

    return (Base) b->dir;

}

int FatorBal(Base *p) {
/* Devolve o fator de balanceamento da raiz da base: altura da
   sub�rvore direita menos a altura da sub�rvore esquerda; devolve
   zero se a �rvore � vazia. */
    ImplBase b = (ImplBase) (*p);

    if (b->esq == NULL && b->dir == NULL)
        return 0;

    return b->bal;

}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */
    ImplBase* b = (ImplBase*) p;

    if (*b == NULL) {
        *b = MALLOC(sizeof(NoArv));
        (*b)->esq = (*b)->dir = NULL;
        (*b)->bal = 0;
        ((*b)->info).ra = a.ra;
        ((*b)->info).nome = a.nome;
        altIn = true;
        return true;
    } else {
        int info = ((*b)->info).ra;
        if (a.ra == info) /* Encontrou o ra */
            return false;
        else if (a.ra < info) { /* Desce a esquerda */
            Base *es = (Base*) &((*b)->esq);
            Boolean res = InsereBase(es, a);

            if (!res) return false;

            if (altIn) {
                 ImplBase *b1, *b2, aux;
                switch ((*b)->bal) {
                    case 1: 
                        (*b)->bal = 0; 
                        altIn = false;
                        break;
                    case 0:
                        (*b)->bal = -1;
                        break;
                    case -1:
                        b1 = &((*b)->esq);
                        b2 = &((*b1)->dir);
                        if ((*b1)->bal == -1) { /* Rotaçãoimples */
                            aux = *b2;
                            (*b)->bal = (*b1)->bal = 0;
                            *b2 = *b;
                            *b = *b1;
                            *b1 = aux;
                        } else { /* Rotação pla */
                            ImplBase *b3 = &((*b2)->esq), *b4 = &((*b2)->dir), aux3, aux4;
                            if ((*b2)->bal == 1) {
                                (*b)->bal = 0;
                                (*b1)->bal = -1;
                            } else if ((*b2)->bal == -1) {
                                (*b)->bal = 1;
                                (*b1)->bal = 0;
                            } else {
                                (*b)->bal = (*b1)->bal = 0;
                            }

                            (*b2)->bal = 0;
                            aux3 = *b3;
                            aux4 = *b4;
                            *b3 = *b1;
                            *b4 = *b;
                            *b = *b2;
                            *b1 = aux4;
                            *b2 = aux3;
                        }
                        altIn = false;
                        break;
                }
            }
        } else { /* Desce a direita */
            Base *di = (Base*) &((*b)->dir);
            Boolean res = InsereBase(di, a);
            if (!res) return false;

            if (altIn) {
                ImplBase *b1, *b2, aux;
                switch ((*b)->bal) {
                    case -1: 
                        (*b)->bal = 0; 
                        altIn = false;
                        break;
                    case 0:
                        (*b)->bal = 1;
                        break;
                    case 1:
                        b1 = &((*b)->dir);
                        b2 = &((*b1)->esq);
                        if ((*b1)->bal == 1) { /* Rotação simples */
                            aux = *b2;
                            (*b)->bal = (*b1)->bal = 0;
                            *b2 = *b;
                            *b = *b1;
                            *b1 = aux;
                        } else { /* Rotação dupla */
                            ImplBase *b3 = &((*b2)->esq), *b4 = &((*b2)->dir), aux3, aux4;
                            if ((*b2)->bal == 1) {
                                (*b)->bal = -1;
                                (*b1)->bal = 0;
                            } else if ((*b2)->bal == -1) {
                                (*b)->bal = 0;
                                (*b1)->bal = 1;
                            } else {
                                (*b)->bal = (*b1)->bal = 0;
                            }
                            (*b2)->bal = 0;
                            aux3 = *b3;
                            aux4 = *b4;
                            *b4 = *b1;
                            *b3 = *b;
                            *b = *b2;
                            *b1 = aux3;
                            *b2 = aux4;
                        }
                        altIn = false;
                        break;
                }
            }
        }
    }
    return true;
}
   
Boolean ConsultaBase(Base *p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contr�rio devolve 'false'. 'a' conter� 
   os dados do aluno, se encontrado. */

    ImplBase b = (ImplBase) (*p);

    while (b != NULL) {
        if ((b->info).ra > ra)
            b = b->esq;
        else if ((b->info).ra < ra)
            b = b->dir;
        else {
            (*a).ra = (b->info).ra;
            (*a).nome = (b->info).nome;
            return true;
        }
    }

    return false;
}
  
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

void PercorreBase(Base *p, TipoVisita Visita) {
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
}

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
}

void EncontraFolha (ImplBase* b, int* ra, String* nome) {
    ImplBase aux = *b;

    aux = aux->dir;

    while ((aux)->esq != NULL) aux = aux->esq;

    *ra = (aux->info).ra;
    *nome = (aux->info).nome;

    RemoveBase (b, (aux->info).ra);
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */

    ImplBase* b = (ImplBase*) p;

    if (*b == NULL)
        return false;
    else {
        int RAno = ((*b)->info).ra;

        if (ra < RAno) { /* Desce a esquerda */
            Base* es = (Base*) &((*b)->esq);
            if(!RemoveBase(es, ra))
                return false;

            if (altRe) {
                ImplBase *b1, *b2, aux;
                switch ((*b)->bal) {
                    case -1: (*b)->bal = 0; break;
                    case 0: (*b)->bal = 1; altRe = false; break;
                    case 1:
                        b1 = &((*b)->dir);
                        b2 = &((*b)->esq);
                        if ((*b1)->bal == 0 || (*b1)->bal == 1) { /* Rotacao simples (RR) */
                            *b2 = *b;
                            *b = *b1;
                            *b1 = aux;
                            if ((*b1)->bal == 0) {
                                (*b1)->bal = -1;
                                altRe = false;
                            } else (*b)->bal = (*b1)->bal = 0;
                        } else { /* Rotacao dupla (RL) */
                            ImplBase *b3, *b4, aux3, aux4;
                            if ((*b2)->bal == 0) {
                                (*b)->bal = (*b1)->bal = 0;
                            } else if ((*b2)->bal == -1) {
                                (*b)->bal = 0;
                                (*b1)->bal = 1;
                                (*b2)->bal = 0;
                            } else {
                                (*b)->bal = -1;
                                (*b1)->bal = 0;
                                (*b2)->bal = 0;
                            }
                            aux3 = *b3;
                            aux4 = *b4;
                            *b4 = *b1;
                            *b3 = *b;
                            *b = *b2;
                            *b1 = aux3;
                            *b2 = aux4;
                        }
                        break;
                }

            }

        } else if (ra > RAno) { /* Desce a direita */
            Base* di = (Base*) &((*b)->dir);
            if(!RemoveBase(di, ra))
                return false;

            if (altRe) {
                ImplBase *b1, *b2, aux;
                switch ((*b)->bal) {
                    case 1: (*b)->bal = 0; break;
                    case 0: (*b)->bal = -;1 altRe = false; break;
                    case -1:
                }
            }
       
        } else { /* Encontra o no a ser removdo */
            if ((*b)->esq == NULL || (*b)->dir == NULL) {
                ImplBase aux = *b;

                if ((*b)->esq == NULL) *b = (*b)->dir;
                else *b = (*b)->esq;

                FREE((aux->info).nome);
                FREE(aux);
                altRe = true;

            } else {
                FREE(((*b)->info).nome);
                EncontraFolha (b, &(((*b)->info).ra), &(((*b)->info).nome));
            }
        }


    }
    return true;
}

