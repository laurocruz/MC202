/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratorio 11 - Base de dados com espalhamento encadeado            *
 * Last modified: 26-11-14                                              *
 ************************************************************************/


#include <stdio.h>
#include "base.h"

/* DECLARACOES DE TIPOS */
/* -------------------- */

typedef struct RegLista *Lista;
typedef struct RegLista {
    Aluno aluno;
    Lista prox;
} RegLista;

typedef struct RegBase *ImplBase;
typedef struct RegBase {
    int numregs;
    Lista tabela[MaxHash];
} RegBase;

/* FUNCAO DE ESPALHAMENTO */
/* ---------------------- */

int Espalha(int k) {
    return (k%MaxHash);
} /* Espalha */


/* FUNCOES DA INTERFACE */
/* -------------------- */

Base CriaBase() {
/* Devolve apontador para uma base vazia com tabela inicializada */
    ImplBase base = MALLOC(sizeof(RegBase));

    base->numregs = 0;

    for (int i = 0; i < MaxHash; i++) {
        base->tabela[i] = NULL;
    }
    return (Base) base;
} /* CriaBase */

Boolean InsereBase(Base p, Aluno *a) {
/* Insere o registro 'a' na base 'p' se nao existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrario devolve 'false' */

    ImplBase base = p;
    int hash = Espalha((*a).ra);
    Lista aux = base->tabela[hash];

    if (aux == NULL || (aux->aluno).ra > (*a).ra) {
    /* Se a lista for vazia ou o ra do aluno a ser inserido for menor que o ra do primeiro
     * aluno da lista, o aluno Ã© inserido na primira posicao */
        base->tabela[hash] = MALLOC(sizeof(RegLista));
        (base->tabela[hash])->prox = aux;
        (base->tabela[hash])->aluno = *a;
        (base->numregs)++;
        return true;
    } else {
        while (true) {
            /* Caso encontre aluno com o mesmo RA, nao sera possivel inserir o aluno na tabela */
            if ((aux->aluno).ra == (*a).ra)
                return false;

            if ((aux->aluno).ra < (*a).ra) {
            /* Caso o RA do aluno apontado por aux seja menos que o RA do aluno a ser inserido, este
             * sera inserido apos o aluno apontado por aux */
                if ((aux->prox == NULL) || (((aux->prox)->aluno).ra > (*a).ra)) {
                /* Caso nao tenha mais nenhum aluno na lista ou o proximo aluno tiver o RA maior, o
                 * aluno sera inserido em frente ao aluno apontado por aux */
                    Lista aux1 = aux->prox;
                    aux->prox = MALLOC(sizeof(RegLista));
                    aux = aux->prox;
                    aux->prox = aux1;
                    aux->aluno = *a;
                    (base->numregs)++;
                    return true;
                } else aux = aux->prox;
                /* Caso contrario, segue-se na lista */
            }
        }
    } 
} /* InsereBase */

Boolean RemoveBase(Base p, int ra) {
/* Remove da base 'p' o aluno com 'ra' dado; devolve 'true'
   se ele existiu e 'false' caso contrario. */
    
    ImplBase base = p;
    Lista aux;
    int hash = Espalha(ra);

    /* Se a lista for vazia, nao e possivel remover o aluno */
    if (base->tabela[hash] == NULL) return false;


    if (((base->tabela[hash])->aluno).ra == ra) {
    /* Caso o aluno da primeira posicao da lista tenha o RA procurado */
        aux = (base->tabela[hash])->prox;
        FREE(((base->tabela[hash])->aluno).nome);
        FREE(base->tabela[hash]);
        base->tabela[hash] = aux;
        (base->numregs)--;
        return true;
    } else {
        aux = base->tabela[hash];
        while (aux->prox != NULL) {
            if (((aux->prox)->aluno).ra == ra) {
            /* Caso o aluno em frente ao aluno apontado por aux tenha o RA procurado, ele e
             * removido */
                Lista aux1 = aux->prox->prox;
                FREE(((aux->prox)->aluno).nome);
                FREE(aux->prox);
                aux->prox = aux1;
                (base->numregs)--;
                return true;
            } else aux = aux->prox;
            /* Caso contrario, segue-se em frente na lista */
        }
        return false;
    }

} /* RemoveBase */

Boolean ConsultaBase(Base p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrario devolve 'false'.  'a' contera 
   os dados do aluno, se encontrado. */
    ImplBase base = p;
    int hash = Espalha(ra); 
    Lista aux = base->tabela[hash];

    while (aux != NULL) {
        if ((aux->aluno).ra == ra) {
            /* Encontra o aluno com o RA procurado */
            (*a).nome = (aux->aluno).nome;
            (*a).ra = (aux->aluno).ra;
            return true;
        }
        aux = aux->prox;
    }
    /* Nao encontra o aluno */
    return false;
} /* ConsultaBase */

int NumeroRegsBase(Base p) {
/* Devolve o numero de registros (alunos) na base 'p'. */
    ImplBase base = p;

    return base->numregs;
} /* NumeroRegsBase */

void ImprimeBase(Base p) {
/* Imprime, os registros contidos na base 'p', um por linha.  A ordem
   de impressao segue a ordem das entradas da tabela, e para cada
   entrada, a ordem da lista ligada.  Cada linha começa com o índice
   correspondente na tabela de espalhamento. Deve ser usado o formato
   "(%3d) %06d %s\n". */
    ImplBase base = p;
    Lista aux;

    if (base->numregs == 0) return;
    
    for (int i = 0; i < MaxHash; i++) {
    /* Percorre todas as listas da tabela */
        aux = base->tabela[i];
        while (aux != NULL) {
        /* Percorre os nos das listas */
            printf("(%3d) %06d %s\n", i, (aux->aluno).ra, (aux->aluno).nome);
            aux = aux->prox;
        }
    }

} /* ImprimeBase */

void LiberaBase(Base p) {
/* Libera toda a memoria utilizada pela base 'p', bem como
   todas as cadeias que guardam os nomes. */
    ImplBase base = p;
    Lista aux1, aux2;

    for (int i = 0; i < MaxHash; i++) {
    /* Percorre todas as listas da tabela */
        aux1 = base->tabela[i];
        while (aux1 != NULL) {
        /* Percorre os nos das listas */
            aux2 = aux1->prox;
            FREE((aux1->aluno).nome);
            FREE(aux1);
            aux1 = aux2;
        }
    }
    FREE(base);

} /* LiberaBase */

