/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 10b - DON'T PANIC - Part I */

#include <stdio.h>

/* Numero maximo de panquecas */
#define MAX_PAN 100

int find_i_j(int pancakes[], int *i, int *j, int *weight, int npan);
void permute(int pancakes[], int i , int j);
int pancake_sort(int pancakes[], int *i, int *j, int *weight, int npan);

int main() {
    int pancakes[MAX_PAN+2], npan, weight = 0;
    int i, j, l;

    /* Le o numero de panquecas */
    scanf("%d", &npan); 

    /* Atribuindo as posicoes iniciais e finais do vetor de panquecas */
    pancakes[0] = 0;
    pancakes[npan+1] = npan + 1;

    /* Lendo a ordenacao das panquecas */
    for (l = 1; l <= npan; l++) {        
        scanf("%d", &pancakes[l]);
    }
    
    /* Imprime a ordem das panquecas antes de se iniciar a ordenacao */
    printf("(");
    for (l = 1; l < npan; l++) {
        printf("%d ", pancakes[l]);
    }
    printf("%d)\n", pancakes[npan]);
    
    /* Enquanto a funcao pancake sort retornar um valor diferente de 1, ou 
     * seja, enquanto a ordenacao ainda nao estiver completamente feita, o 
     * loop se repetira */
    while (pancake_sort(pancakes, &i, &j, &weight, npan)) {
        /* Imprimindo a ordem das panquecas apos cada permutacao */
        printf("(");
        for (l = 1; l < npan; l++) {
            printf("%d ", pancakes[l]);
        }
        printf("%d)\n", pancakes[npan]);
    }
    /* Imprimindo o peso total ao final da ordenacao */
    printf("Peso: %d\n", weight);
    
    return 0;
}

/* Funcao responsavel por promover cada permutacao e retorar 0 quando o vetor
 * de panquecas estiver ordenado */
int pancake_sort(int pancakes[], int *i, int *j, int *weight, int npan) {
    int flag;
    /* Procura o i e j da permutacao e retorna 0 se estiver ordenad */
    flag = find_i_j(pancakes, i, j, weight, npan);
    /* Se as panquecas ja estiverem ordenadas, retorna 0 */
    if (flag == 0)
        return 0;
    
    /* Faz a permutacao tendo os valor de i e j */
    permute(pancakes, *i, *j);
    
    return 1;
}

/* Funcao responsavel por achar os indices i e j a partir dos quais sera feita
 * a permutacao */
int find_i_j(int pancakes[], int *i, int *j, int *weight, int npan) {
    int it;
    
    /* Procura o i fazendo uma procura de strip no inicio */
    (*i) = 2;
    while ((pancakes[*i-1] == pancakes[*i]-1) && (*i != npan+1)) {
        (*i)++;
    }
    
    /* Retorna 0 se a strip for o vetor inteiro (panquecas ordenadas) */
    if (*i == npan+1)
        return 0;
    
    /* Procura o j para o qual havera a destruicao de um breakpoint ao se fazer 
     * permutacao com o prefixo determinado pelo i anterior */
    (*j) = (*i) + 1;
    while ((pancakes[1] - pancakes[(*j)-1] != 1) && 
        (pancakes[(*j)] - pancakes[(*i)-1] != 1)) {
        (*j)++;
    }
    
    /* Sabendo o J (e consequentemente o peso), procura por uma strip na qual 
     * a permutacao destruira dois breakpoints */
    if (pancakes[1] - pancakes[(*j)-1] == 1) {
        for (it = 2; it < (*j); it++) {
            if (pancakes[(*j)] - pancakes[it-1] == 1) {
                /* Se achar, altera o valor de i */
                (*i) = it;
                /* Atribui o valor do peso */
                (*weight) += (*j) - 1;
                /* E retorn 1, saindo da funcao */
                return 1;
            }
        }
    }
    /* Caso não ache o i referido acima, atribui o valor do peso e sai da
     * funcao normalmente */
    (*weight) += (*j) - 1;
        
    return 1;
}

/* Funcao responsavel por permutar os dois prefixos determinados pelos indices
 * i e j */
void permute(int pancakes[], int i , int j) {
    int auxi[MAX_PAN-1], auxj[MAX_PAN-1];
    int k, m, n, p = 0, l;
    
    for (m = 1; m < i; m++) {
        auxi[m-1] = pancakes[m];
    }
    for (n = i; n < j; n++) {
        auxj[n-i] = pancakes[n];
    }
    
    for (k = 0; k < n-i; k++) {
        pancakes[k+1] = auxj[k];
    }
    
    for (l = k+1; l < j; l++) {
        pancakes[l] = auxi[p++];
    }
    
}