/************************************************************************
 * Lauro Cruz e Souza - RA: 156175                                      *
 * MC202 - Turma F                                                      *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br        *
 * Laboratorio 10 - Arvores Digitais (tries)                            *
 * Last modified: 23-11-14                                              *
 ************************************************************************/

/* Arquivo trie.c:

   Implementação de árvores digitais (ADs) através de um tipo
   abstrato de dados usando apontadores "void *".

   Todas as definições estão no arquivo "trie.h".

*/

#include <stdio.h>
#include <ctype.h>

#include "trie.h"
#include "balloc.h"

typedef struct RegTrie * ImplTrie;

typedef struct RegTrie {
  Boolean fim;                 /* término de uma cadeia */
  ImplTrie subarv[TAM_ALFABETO]; /* vetor de subárvores */
} RegTrie;



/* ------------------------------------------------------------ */
/*          Sugestões de algumas funções auxiliares             */
/* ------------------------------------------------------------ */

ImplTrie criaInicializaNo() {
/* Devolve um nó com a marca de fim de cadeia falsa e todas as
   subárvores vazias; usada para criar a AD inicial e durante a
   inserção.
*/
    ImplTrie p = MALLOC(sizeof(RegTrie));

    if (p == NULL) {
        printf("Memória esgotada\n");
        exit(0);
    }
    p->fim = false;
    
    for (int k = 0; k < TAM_ALFABETO; k++)
        p->subarv[k] = NULL;
    
    return p;
}


Boolean livre(ImplTrie t) {
/* Devolve verdadeiro se o nó 't' não é final e é uma folha; usada
   durante a remoção.
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
/* Percorre a AD em ordem lexicográfica; constroi as cadeias em 'buf'
  e aplica a função 'v' quando termina uma cadeia, colocando no fim o
  caractere '\0'; 'm' é o índice do próximo caractere em 'buf'.
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
/*                      Fim das sugestões                       */
/* ------------------------------------------------------------ */


Trie CriaAD() {
/* Devolve uma AD vazia. Supõe uma implementação que não modifica mais
   o apontador para a raiz da AD. */

    return criaInicializaNo();

} /* CriaAD */


Boolean consultaAD(Trie t, char *s) {
/* Verifica se a cadeia de caracteres 's' foi inserida na AD 't'. */

    ImplTrie it = t;

    while (*s != '\0') {
        /* Se a subarvore for nula, entÃ£o a palavra nao esta na Trie */
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
   verdadeiro se houve inserção; devolve o valor falso se a cadeia já
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
/* Devolve o número de cadeias contidas na AD. */

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
   verdadeiro se houve remoção; devolve o valor falso se a cadeia não
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
/* Visita, em ordem alfabética, as cadeias contidas na AD 't' e
   aplica, a cada cadeia, a função 'v', sob a forma "v(s)", supondo
   que 's' é um apontador para a cadeia que deve terminar com o
   caractere nulo '\0'.
*/
    char buf[TAM_MAX_CADEIA];
  
    percorreAux((ImplTrie)t, v, buf, 0);

} /* percorreAD */


void liberaAD(Trie t) {
/* Libera a memória dinâmica alocada na construção da AD 't'. */

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
  Funções usadas somente para verificação; conceitualmente
  não fazem parte da implementação.
*/
   
int numNosAD(Trie t) {
/* Devolve o número de nós da AD. */

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


