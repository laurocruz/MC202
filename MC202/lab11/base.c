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

/* FUNCOES AUXILIARES */
/* ------------------ */


/* COMPLETAR SE NECESSARIO */


/* FUNCOES DA INTERFACE */
/* -------------------- */

Base CriaBase() {
/* Devolve apontador para uma base vazia com tabela inicializada */
    ImplBase b = MALLOC(sizeof(RegBase));

    b->numregs = 0;

    for (int i = 0; i < MaxHash; i++) {
        b->tabela[i] = NULL;
    }
    return (Base) b;
} /* CriaBase */

Boolean InsereBase(Base p, Aluno *a) {
/* Insere o registro 'a' na base 'p' se nao existe aluno
   com o mesmo valor de 'ra', e devolve 'true';  caso
   contrario devolve 'false' */

    ImplBase b = p;
    int hash = Espalha((*a).ra);
    Lista aux = b->tabela[hash];

    if (aux == NULL || (aux->aluno).ra > (*a).ra) {
        b->tabela[hash] = MALLOC(sizeof(RegLista));
        (b->tabela[hash])->prox = aux;
        (b->tabela[hash])->aluno = *a;
        return true;
    } else {
        while (true) {
            if ((aux->aluno).ra == (*a).ra)
                return false;

            if ((aux->aluno).ra < (*a).ra) {
                if ((aux->prox == NULL) || (((aux->prox)->aluno).ra > (*a).ra)) {
                    Lista aux1 = aux->prox;
                    aux->prox = MALLOC(sizeof(RegLista));
                    aux = aux->prox;
                    aux->prox = aux1;
                    aux->aluno = *a;
                    return true;
                } else aux = aux->prox;
            }
        }
    } 
} /* InsereBase */

Boolean RemoveBase(Base p, int ra) {
/* Remove da base 'p' o aluno com 'ra' dado; devolve 'true'
   se ele existiu e 'false' caso contrario. */
    
    ImplBase b = p;
    Lista aux;
    int hash = Espalha(ra);

    if (b->tabela[hash] == NULL) return false;

    if (((b->tabela[hash])->aluno).ra == ra) {
        aux = (b->tabela[hash])->prox;
        FREE(((b->tabela[hash])->aluno).nome);
        FREE(b->tabela[hash]);
        b->tabela[hash] = aux;
        return true;
    } else {
        aux = b->tabela[hash];
        while (aux->prox != NULL) {
            if (((aux->prox)->aluno).ra == ra) {
                Lista aux1 = aux->prox->prox;
                FREE(((aux->prox)->aluno).nome);
                FREE(aux->prox);
                aux->prox = aux1;
                return true;
            } else aux = aux->prox;
        }
        return false;
    }

} /* RemoveBase */

Boolean ConsultaBase(Base p, int ra, Aluno *a) {
/* Devolve 'true' se existe um registro com 'ra' dado na
   base 'p';  caso contrario devolve 'false'.  'a' contera 
   os dados do aluno, se encontrado. */
    ImplBase b = p;
    int hash = Espalha(ra); 
    Lista aux = b->tabela[hash];

    while (aux != NULL) {
        if ((aux->aluno).ra == ra) {
            (*a).nome = (aux->aluno).nome;
            (*a).ra = (aux->aluno).ra;
            return true;
        }
        aux = aux->prox;
    }
    return false;
} /* ConsultaBase */

int NumeroRegsBase(Base p) {
/* Devolve o numero de registros (alunos) na base 'p'. */
    ImplBase b = p;
    Lista aux = NULL;
    int i, n = 0;

    for (i = 0; i < MaxHash; i++) {
        aux = b->tabela[i];
        while (aux != NULL)  {
            n++;
            aux = aux->prox;
        }
    }
    return n;
} /* NumeroRegsBase */

void ImprimeBase(Base p) {
/* Imprime, os registros contidos na base 'p', um por linha.  A ordem
   de impressao segue a ordem das entradas da tabela, e para cada
   entrada, a ordem da lista ligada.  Cada linha começa com o índice
   correspondente na tabela de espalhamento. Deve ser usado o formato
   "(%3d) %06d %s\n". */
    ImplBase b = p;
    Lista aux;
    
    for (int i = 0; i < MaxHash; i++) {
        aux = b->tabela[i];
        while (aux != NULL) {
            printf("(%3d) %06d %s\n", i, (aux->aluno).ra, (aux->aluno).nome);
            aux = aux->prox;
        }
    }

} /* ImprimeBase */

void LiberaBase(Base p) {
/* Libera toda a memoria utilizada pela base 'p', bem como
   todas as cadeias que guardam os nomes. */
    ImplBase b = p;
    Lista aux1, aux2;

    for (int i = 0; i < MaxHash; i++) {
        aux1 = b->tabela[i];
        while (aux1 != NULL) {
            aux2 = aux1->prox;
            FREE((aux1->aluno).nome);
            FREE(aux1);
            aux1 = aux2;
        }
    }
    FREE(b);

} /* LiberaBase */

