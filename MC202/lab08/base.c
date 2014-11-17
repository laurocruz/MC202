/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratório 08 - Base de Dados com Arvore AVL - base.c              *
 * Last modified: 14-11-14                                              *
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

void RotacaoSimples(ImplBase *b, ImplBase *b1, ImplBase *b2) {
    /* Realiza a rotacao simples dados os enderecos dos ponteiros dos nos */
    ImplBase aux = *b2;
    *b2 = *b;
    *b = *b1;
    *b1 = aux;
}

void RotacaoDupla(ImplBase *b, ImplBase *b1, ImplBase *b2, ImplBase *b3, ImplBase *b4) {
    /* Realiza a rotacao dupla dados os enderecoes dos ponteiros dos nos */
    ImplBase aux3 = *b3,  aux4 = *b4;
    *b3 = *b1;
    *b4 = *b;
    *b = *b2;
    *b1 = aux4;
    *b2 = aux3;
}

Boolean InsereBase(Base *p, Aluno a) {
/* Insere o registro 'a' na base 'p' se n�o existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contr�rio devolve 'false' */
    ImplBase* b = (ImplBase*) p;

    if (*b == NULL) { /* Nao encontrou o aluno, ent�ão pode iserir */
        *b = MALLOC(sizeof(NoArv));
        (*b)->esq = (*b)->dir = NULL; /* E uma folha */
        /* Passa as informacoes do aluno paro o no */
        (*b)->bal = 0;
        ((*b)->info).ra = a.ra;
        ((*b)->info).nome = a.nome;
        altIn = true; /* Houve alteracao na altura */
        return true;

    } else {
        int info = ((*b)->info).ra;
        if (a.ra == info) /* Encontrou o ra */
            return false;
        else if (a.ra < info) { /* Desce a esquerda */
            Base *es = (Base*) &((*b)->esq);
            if (!InsereBase(es, a)) return false; /* Nao consegue inserir o RA */

            if (altIn) { /* Houve mudanca na altura */
                 ImplBase *b1, *b2;
                switch ((*b)->bal) {
                    case 1: /* Insercao no lado mais baixo */
                        (*b)->bal = 0; 
                        altIn = false;
                        break;
                    case 0: /* Insercao com lados de alturas iguais */
                        (*b)->bal = -1;
                        break;
                    case -1: /* Insercao no lado mais alto */
                        b1 = &((*b)->esq);
                        b2 = &((*b1)->dir);

                        if ((*b1)->bal == -1) { /* Rotacao simples (LL) */
                            /* Alterando o balanceamento dos nos */
                            (*b)->bal = (*b1)->bal = 0;
                            RotacaoSimples(b, b1, b2);

                        } else { /* Rotacao dupla (LR) */
                            /* Alterando o balanceamento dos nos */
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
                            RotacaoDupla(b, b1, b2, &((*b2)->esq), &((*b2)->dir));
                        }
                        altIn = false;
                        break;
                }
            }
        } else { /* Desce a direita */
            Base *di = (Base*) &((*b)->dir);
            if (!InsereBase(di, a)) return false; /* Nao consegue inserir o RA */

            if (altIn) { /* Houve mudanca na altura */
                ImplBase *b1, *b2;
                switch ((*b)->bal) {
                    case -1: /* Insercao no lado mais baixo */
                        (*b)->bal = 0; 
                        altIn = false;
                        break;
                    case 0: /* Insercao com lados de alturas iguais */
                        (*b)->bal = 1;
                        break;
                    case 1: /* Insercao no lado mais alto */
                        b1 = &((*b)->dir);
                        b2 = &((*b1)->esq);

                        if ((*b1)->bal == 1) { /* Rotação sples (RR) */
                            /* Alterando o balanceamento dos nos */
                            (*b)->bal = (*b1)->bal = 0;
                            RotacaoSimples(b, b1, b2);

                        } else { /* Rotação dua (RL) */
                            /* Alterando o balenceamento dos nos */
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
                            RotacaoDupla(b, b1, b2, &((*b2)->dir), &((*b2)->esq));
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
        if ((b->info).ra > ra) /* Desce a esquerda */
            b = b->esq;
        else if ((b->info).ra < ra) /* Desde a direita */
            b = b->dir;
        else { /* Encontra o aluno com o RA passado como parametro */
            /* Copia suas informacoes */
            (*a).ra = ra;
            (*a).nome = (b->info).nome;
            return true;
        }
    }
    return false; /* Não encontra o aluno na arvore */
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

void EncontraFolha (ImplBase* b) {
    /* Encontra a menor folha da subarvore direita do no a ser removido.
     * Copia as informacoes dessa folha ao no que tem de ser removido
     * Chama a recursao pare remover essa folha */
    ImplBase aux = *b;
    Base* p = (Base*) &((*b)->dir);

    aux = aux->dir;

    /* Encontra o no mais a esquerda da subarvore direita */
    while ((aux)->esq != NULL) aux = aux->esq;

    /* Copia as informacoes */
    ((*b)->info).ra = (aux->info).ra;
    ((*b)->info).nome = (aux->info).nome;

    (aux->info).nome = NULL;

    /* Remocao da folha */
    RemoveBase (p, (aux->info).ra);
}

Boolean RemoveBase(Base *p, int ra) {
/* Devolve 'true' se um registro com 'ra' p�de ser removido da
   base 'p';  caso contr�rio devolve 'false'. */

    ImplBase* b = (ImplBase*) p;

    if (*b == NULL) /* Nao encontra o no a ser removido */
        return false;
    else {
        int RAno = ((*b)->info).ra;

        if (ra < RAno) { /* Desce a esquerda */
            Base* es = (Base*) &((*b)->esq);
            if(!RemoveBase(es, ra)) return false; /* Nao encontrou o no */

            if (altRe) { /* Houve variacao de altura */
                ImplBase *b1, *b2;
                switch ((*b)->bal) {
                    case -1: (*b)->bal = 0; break; /* Remocao no lado mais alto */
                    case 0: (*b)->bal = 1; altRe = false; break; /* Remocao com lados de alturas iguais */
                    case 1: /* Remocao no lado mais baixo */
                        b1 = &((*b)->dir);
                        b2 = &((*b1)->esq);

                        if ((*b1)->bal == 0 || (*b1)->bal == 1) { /* Rotacao simples (RR) */
                            /* Alterando o balanceamento dos nos */
                            if ((*b1)->bal == 0) {
                                (*b1)->bal = -1;
                                altRe = false;
                            } else (*b)->bal = (*b1)->bal = 0;
                            RotacaoSimples(b, b1, b2);

                        } else { /* Rotacao dupla (RL) */
                            /* Alterando o balanceamento dos nos */
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
                            RotacaoDupla(b, b1, b2, &((*b2)->dir), &((*b2)->esq));
                        }
                        break;
                }

            }

        } else if (ra > RAno) { /* Desce a direita */
            Base* di = (Base*) &((*b)->dir);
            if(!RemoveBase(di, ra)) return false;

            if (altRe) { /* Houve variacao de altura */
                ImplBase *b1, *b2;
                switch ((*b)->bal) {
                    case 1: (*b)->bal = 0; break; /* Remocao no lado mais alto */
                    case 0: (*b)->bal = -1; altRe = false; break; /* Remocao com lados de alturas iguais */
                    case -1: /* Remocao no lado mais baixo */
                        b1 = &((*b)->esq);
                        b2 = &((*b1)->dir);

                        if ((*b1)->bal == 0 || (*b1)->bal == -1) { /* Rotacao simples (LL) */
                            /* Alterando balanceamento dos nos */
                            if ((*b1)->bal == 0) {
                                (*b1)->bal = 1;
                                altRe = false;
                            } else (*b)->bal = (*b1)->bal = 0;

                            RotacaoSimples (b, b1, b2);

                        } else { /* Rotacao dupla (LR) */
                            /* Alterando balanceamento dos nos */
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
                            RotacaoDupla(b, b1, b2, &((*b2)->esq), &((*b2)->dir));
                        }
                        break;
                }
            }
       
        } else { /* Encontra o no a ser removdo */
            if ((*b)->esq == NULL || (*b)->dir == NULL) { /* No pode ser removido diretamente */
                ImplBase aux = *b;
               
                /* Determina em que lado esta o filho (se houver), e o no pai apontara para ele */
                if ((*b)->esq == NULL) *b = (*b)->dir;
                else *b = (*b)->esq;
                
                /* Libera a string e no */
                FREE((aux->info).nome);
                FREE(aux);
                altRe = true; /* Ocorre variacao de altura */

            } else { /* No nao pode ser removido diretamente */
                FREE(((*b)->info).nome);
                /* Encontra o aluno de menor RA da subarvore direita */
                EncontraFolha (b);
            }
        }


    }
    return true;
}

