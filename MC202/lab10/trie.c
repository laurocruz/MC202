/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratorio 10 - Arvores Digitais (tries)                            *
 * Last modified: 23-11-14                                              *
 ************************************************************************/

/* Arquivo trie.c:

   Implementa��o de �rvores digitais (ADs) atrav�s de um tipo
   abstrato de dados usando apontadores "void *".

   Todas as defini��es est�o no arquivo "trie.h".

*/

#include <stdio.h>
#include <ctype.h>

#include "trie.h"
#include "balloc.h"

typedef struct RegTrie * ImplTrie;

typedef struct RegTrie {
  Boolean fim;                 /* t�rmino de uma cadeia */
  ImplTrie subarv[TAM_ALFABETO]; /* vetor de sub�rvores */
} RegTrie;



/* ------------------------------------------------------------ */
/*          Sugest�es de algumas fun��es auxiliares             */
/* ------------------------------------------------------------ */

ImplTrie criaInicializaNo() {
/* Devolve um n� com a marca de fim de cadeia falsa e todas as
   sub�rvores vazias; usada para criar a AD inicial e durante a
   inser��o.
*/
    ImplTrie p = MALLOC(sizeof(RegTrie));

    if (p == NULL) {
        printf("Mem�ria esgotada\n");
        exit(0);
    }
    p->fim = false;
    
    for (int k = 0; k < TAM_ALFABETO; k++)
        p->subarv[k] = NULL;
    
    return p;
}


Boolean livre(ImplTrie t) {
/* Devolve verdadeiro se o n� 't' n�o � final e � uma folha; usada
   durante a remo��o.
*/
    if (t->fim == false) {
        for (int i = 0; i < TAM_ALFABETO; i++) {
            if (t->subarv[i] != NULL)
                return false; /* Nao e final, mas nao e uma folha */
        }
        return true; /* Nao e final e e folha */
    }
    return false; /* E final */
}


void percorreAux(ImplTrie t, funcVisita *v, char *buf, int m) {
/* Percorre a AD em ordem lexicogr�fica; constroi as cadeias em 'buf'
  e aplica a fun��o 'v' quando termina uma cadeia, colocando no fim o
  caractere '\0'; 'm' � o �ndice do pr�ximo caractere em 'buf'.
*/
    int i;

    /* Sempre que forma uma cadeia, a visita */
    if (t->fim) { 
        buf[m] = '\0';
        v(buf);
    }

    /* Verifica todas as subarvores dos nos para encontrar todas as cadeias */
    for (i = 0; i < TAM_ALFABETO; i++) {
        if (t->subarv[i] != NULL) {
            buf[m] = i + 'a';
            percorreAux(t->subarv[i], v, buf, m+1);
        }
    }
}


/* ------------------------------------------------------------ */
/*                      Fim das sugest�es                       */
/* ------------------------------------------------------------ */


Trie CriaAD() {
/* Devolve uma AD vazia. Sup�e uma implementa��o que n�o modifica mais
   o apontador para a raiz da AD. */

    return criaInicializaNo();

} /* CriaAD */


Boolean consultaAD(Trie t, char *s) {
/* Verifica se a cadeia de caracteres 's' foi inserida na AD 't'. */

    ImplTrie it = t;

    while (*s != '\0') {
        /* Se a subarvore for nula, então a palavra nao esta na Trie */
        if (it->subarv[toupper(*s)-'A'] == NULL)
            return false;
        it = it->subarv[toupper(*s)-'A'];
        s++;
    }
    
    /* Se it->fim == true, a palavra esta na trie      *
     * Se it->fim == false, a palavra nao esta na trie */
    return it->fim;

} /* consultaAD */


Boolean insereAD(Trie t, char *s) {
/* Insere na AD 't' a cadeia de caracteres 's'.  Devolve o valor
   verdadeiro se houve inser��o; devolve o valor falso se a cadeia j�
   ocorre em 't'.  A cadeia 's' pode ser vazia (de comprimento zero).
*/
    ImplTrie it = t;
    Boolean nCriou = true;

    while (*s != '\0') {
        /* Se a subarvore nao existe, tem que ser criada para formar a cadeia */
        if (it->subarv[toupper(*s)-'A'] == NULL) {
            it->subarv[toupper(*s)-'A'] = criaInicializaNo();
            nCriou = false; /* Houve a criacao de um novo no para inserar a palavra */
        }
        it = it->subarv[toupper(*s)-'A'];
        s++;
    }
    
    /* Caso nao tenha ocorrido criacao de no e o ultimo no for final,
     * a palavra ja existia na trie */
    if (nCriou && it->fim) return false;

    /* Marca o ultimo no da cadeia como final */
    it->fim = true;
    return true;

} /* insereAD */

  
int numCadeiasAD(Trie t) { 
/* Devolve o n�mero de cadeias contidas na AD. */

    ImplTrie it = t;
    int i, n = 0;

    for (i = 0; i < TAM_ALFABETO; i++) {
        /* Conta a quantidade de cadeias nas subarvores */
        if (it->subarv[i] != NULL)
            n += numCadeiasAD((Trie)it->subarv[i]);
    }
    
    /* A quatidade de cadeias a partir da raiz em questao e a quatidade 
     * de cadeias em suas subarvores mais a cadeia terminada na raiz 
     * (caso seja no final) */
    return (int)it->fim + n;

} /* numCadeiasAD */


Boolean removeAD(Trie t, char *s) {
/* Remove da AD 't' a cadeia de caracteres 's'. Devolve o valor
   verdadeiro se houve remo��o; devolve o valor falso se a cadeia n�o
   ocorre em '*t'.
*/

/* A remocao e feita com a criacao de uma pilha que armazena os enderecos
 * dos apontadores para os nos formadores da palavra a ser retirada */
    int i = -1;
    ImplTrie *it, **pilha;
    it = (ImplTrie*) &t;
    pilha = MALLOC((TAM_MAX_CADEIA + 1) * sizeof(ImplTrie*));

    while (*s != '\0') {
        if ((*it)->subarv[toupper(*s) - 'A'] != NULL) {
            it = &((*it)->subarv[toupper(*s)- 'A']);
            pilha[++i] = it; /* Armazena o endereco do apontador do no na pilha */
            s++;
        } else {
        /* Caso a subarvore for nula, entao a cadeia nao esta na trie */
            FREE(pilha);
            return false;
        }
    }

    /* Se o ultimo no for final a cadeia esta na trie */
    if ((*it)->fim) 
        (*it)->fim = false;
    else { 
    /* Caso contrario, nao esta */
        FREE(pilha); 
        return false; 
    }

    Boolean out = false;
    while (i >= 0 && !out) {
        /* Caso um no nao for final e nao tiver nos, entao tem de ser liberado */
        if (livre(*(pilha[i]))) {
            FREE(*(pilha[i]));
            *pilha[i--] = NULL;
        } else out = true;
    }

    /* Cadeia retirada */
    FREE(pilha);
    return true;

} /* removeAD */


void percorreAD(Trie t, funcVisita *v) {
/* Visita, em ordem alfab�tica, as cadeias contidas na AD 't' e
   aplica, a cada cadeia, a fun��o 'v', sob a forma "v(s)", supondo
   que 's' � um apontador para a cadeia que deve terminar com o
   caractere nulo '\0'.
*/
    char buf[TAM_MAX_CADEIA];
  
    percorreAux((ImplTrie)t, v, buf, 0);

} /* percorreAD */


void liberaAD(Trie t) {
/* Libera a mem�ria din�mica alocada na constru��o da AD 't'. */

    ImplTrie it = t;

    /* Semelhante a liberacao em pos-ordem em arvores binarias, mas ao inves de
     * descer na subarvore esquerda, direita e depois liberar a raiz, desce em
     * todas as subarvores e depois libera a raiz */
    if (it != NULL) {
        for (int i = 0; i < TAM_ALFABETO; i++)
            liberaAD((Trie)it->subarv[i]);

        FREE(it);
    }

} /* liberaAD */


/* 
  Fun��es usadas somente para verifica��o; conceitualmente
  n�o fazem parte da implementa��o.
*/
   
int numNosAD(Trie t) {
/* Devolve o n�mero de n�s da AD. */

    ImplTrie it = t;
    int n = 0;

    if (it != NULL) {
        for (int i = 0; i < TAM_ALFABETO; i++) {
        /* Contabiliza a quantidade de nos das subarvores */
            n += numNosAD((Trie)it->subarv[i]);
        }
        /* Retorna a quantidade de nos da subarvore de raiz 't' */
        return n + 1;
    }
  
  return 0;

} /* numNosAD */


int maior(int x, int y) {
/* Retorna o maior valor inteiro */

    if (x >= y) return x;
    else return y;

} /* maior */


int alturaAD(Trie t) {
/* Devolve a altura de AD. */

    int h;
    ImplTrie it = t;

    if (it != NULL) {
        h = alturaAD((Trie)it->subarv[0]);
        for (int i = 1; i < TAM_ALFABETO; i++) {
            h = maior(h, alturaAD((Trie)it->subarv[i]));
        } /* A altura da arvore e igual a altura da maior subarvore mais 1 (raiz) */
        return h + 1;
    }
    return 0;

} /* alturaAD */


