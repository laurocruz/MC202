/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 09b - Concurso Público para Professor da UNICAMP */

#include <stdio.h>
#include <stdlib.h> 

/* Quantidade de membros que irão dar as notas aos candidatos */
#define MEMBERS 5

/* Alocacao dinamica de uma matriz do tipo int */
int ** int_matrixAllocation(int lines, int columns);

/* Alocacao dinamica de uma matriz do tipo double */ 
double ** double_matrixAllocation(int lines, int columns);

/* Desalocacao de uma matriz do tipo int */
void int_matrixFree(int **matrix, int lines);

/* Desalocacao de uma matriz do tipo double */
void double_matrixFree(double **matrix, int lines);

/* Imprime as preferencias dos membros */
void print_pref(int **pref, int lines, int candidates);

/* Leitura das notas dos candidatos */
void read_grades(double **grades, int **pref, int lines, int columns);

/* Ordenacao das notas dos candidatos para determinar suas preferencias */
void selectionSort(double **grades, int **pref, int lines, int columns);

/* Faz a classificacao final dos candidatos */
void classificate(int *classification, int **pref, double *medias,
                  int candidates);

int main() {
    /* Quantidade de candidatos e dois marcadores de iteracao */
    int candidates, i, j;
    /* Ponteiros da matriz de preferencias dos membros e a do vetor de 
     * classificacao dos candidatos */
    int **pref, *classification;
    /* Ponteiros da matriz de notas dadas a cada candidato e do vetor das 
     * medias de cada candidato */
    double **grades, *medias;
    
    /* Leitura da quantidade de candidatos */
    scanf("%d", &candidates);
    
    /* Alocacao dinamica de memoria para as matrizes pref e grades */
    pref = int_matrixAllocation(MEMBERS, candidates);
    grades = double_matrixAllocation(MEMBERS, candidates);
    /* Alocacao dinamica de memoria para os vetores classification e medias */
    classification = malloc(candidates * sizeof(int));
    medias = malloc(candidates * sizeof(double));
    
    /* Leitura da matriz de notas */
    read_grades(grades, pref, MEMBERS, candidates);
    
    /* Zerando o vetor para calcular as medias */
    for (i = 0; i < candidates; i++)
        medias[i] = 0.0;
    
    /* Calculo das medias, somando as notas de cada professor para cada 
     * candidato e dividindo pelo numero de membros (notas) no passo [2] */
    for (i = 0; i < MEMBERS; i++) {
        for (j = 0; j < candidates; j++) {
            medias[j] += grades[i][j];
        }
    }
    /* Passo [2] */
    for (i = 0; i < candidates; i++)
        medias[i] = medias[i]/MEMBERS;
    
    /* Usando o metodo de ordenacao selection sort para ordenar as notas dadas 
     * por cada membro para cada candidato, e assim formar a matriz de 
     * preferencias dos membros */
    selectionSort(grades, pref, MEMBERS, candidates);
    
    /* Imprimindo as notas medias dos candidatos */
    printf("Nota Media:");
    for (i = 0; i < candidates; i++)
        printf(" %.1f", medias[i]);
    
    printf("\n\n");
    
    /* Imprimindo as preferencias dos membros em relacao aos candidatos */
    printf("Preferencia:\n");
    print_pref(pref, MEMBERS, candidates);
    
    printf("\n");
    
    /* Fazendo a classificacao final dos candidatos */
    classificate(classification, pref, medias, candidates);
    
    /* Imprimindo a classificacao final */
    printf("Classificacao:");
    for (i = 0; i < candidates; i++)
        printf(" %d", classification[i]);
    
    printf("\n");
    
    /* Liberando a memoria alocada dinamicamente */
    int_matrixFree(pref, MEMBERS);
    double_matrixFree(grades, MEMBERS);
    free(classification);
    free(medias);
    
    return 0;
}

/* Feita para alocar a matriz de preferencias dos membros */
int ** int_matrixAllocation(int lines, int columns) {
    int i, **matrix;
    
    matrix = malloc(lines * sizeof(int *));
    
    for (i = 0; i < lines; i++) {
        matrix[i] = malloc(columns * sizeof(int));
    }
    
    return matrix;
}

/* Feita para alocar a matriz das notas dadas a cada candidato */
double ** double_matrixAllocation(int lines, int columns) {
    int i;
    double **matrix;
    
    matrix = malloc(lines * sizeof(double *));
    
    for (i = 0; i < lines; i++) {
        matrix[i] = malloc(columns * sizeof(double));
    }
    
    return matrix;
}

/* Feita para desalocar a matriz de preferencias */
void int_matrixFree(int **matrix, int lines) {
    int i;
    
    for (i = 0; i < lines; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/* Feita para desalocar a matriz das notas */
void double_matrixFree(double **matrix, int lines) {
    int i;
    
    for (i = 0; i < lines; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/* Imprimir a matriz de preferencias */
void print_pref(int **pref, int lines, int candidates) {
    int i, j;
    
    for (i = 0; i < lines; i++) {
        /* Imprime na frente de cada membro suas preferencias de candidatos, do 
         * que recebeu a maior nota ao que recebeu a menor nota */
        printf("Membro %d:", i+1);
        for (j = 0; j < candidates; j++) {
            printf(" %d", pref[i][j]);
        }
        printf("\n");
    }
}

/* Ler as notas dadas aos candidatos por cada membro */
void read_grades(double **grades, int **pref, int lines, int columns) {
    int i, j;
    
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            scanf("%lf", &grades[i][j]);
            /* Ao mesmo tempo que le a matriz de notas, atribui os valores de 1 
             * ate candidates nas posicoes de 0 a candicates-1, possibilitando 
             * assim ordenar essa essas posicoes tendo como base o selection 
             * sort que sera feito na matriz de notas */
            pref[i][j] = j + 1;
        }
    }
}

/* Ordenando as preferencias com base na ordenacao das notas na matriz das 
 * notas */
void selectionSort(double **grades, int **pref, int lines, int columns) {
    int i, j, k, max, aux1, aux2;
    
    /* Pelo metodo de selection sort a funcao faz a ordencao das notas da maior 
     * para a menor em cada linha. */
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns-1; j++) {
            max = j;
            for (k = j+1; k < columns; k++) {
                if (grades[i][max] < grades[i][k]) {
                    max = k;
                    
                } else if (grades[i][max] == grades[i][k]) {
                    if (pref[i][max] > pref[i][k])
                        max = k;
                }
            }
            
            /* Chegando no momento de promover a troca das posicoes das notas 
             * dentro da linha da matriz, promove-se uma troca nas mesmas 
             * posicoes na mesma linha da matriz de preferencias, na qual 
             * inicialmente os valores em cada posicao representavam o numero 
             * do candidato que tinha a sua nota na mesma posicao da linha da 
             * matriz de notas, antes de ser ordenada */
            aux1 = grades[i][max];
            grades[i][max] = grades[i][j];
            grades[i][j] = aux1;
            
            aux2 = pref[i][max];
            pref[i][max] = pref[i][j];
            pref[i][j] = aux2;
            
        }
    }
}

/* Classificando os candidatos */
void classificate(int *classification, int **pref, double *medias,
                  int candidates) {
    int i, j, k, l, m, z, max, *aux;
    
    /* Alocacao dinamica da matriz auxiliar que sera usada para fazer a 
     * contagem de de vezes que cada candidato aparece na primeira posicao de 
     * preferencia dos membros */
    aux = malloc(candidates * sizeof(int));
    
    for (j = 0; j < candidates; j++) {
        /* Zerando a matriz auxiliar a toda nova iteracao, já que é uma matriz 
         * contador */
        for (i = 0; i < candidates; i++) {
            aux[i] = 0;
        }
        
        /* Fazendo a contagem de vezes que cada candidato aparece como primeira 
         * opcao na lista de candidatos */
        for (i = 0; i < MEMBERS; i++) {
            aux[pref[i][0]-1]++;
        }
        
        max = 0;
        for (k = 1; k < candidates; k++) {
            /* Encontrando o candidato com o maior valor de aparicoes, sendo 
             * esse que ficara na respectiva posicao que esta sendo considerada 
             */
            if (aux[k] > aux[max]) {
                max = k;
            /* Se dois candidatos tiverem a mesma quantidade de aparicoes...*/
            } else if (aux[k] == aux[max]) {
                /*... o que tiver a maior media sera o escolhido */
                if (medias[k] > medias[max]) {
                    max = k;
                /* E caso tenham medias iguais, o de menor numero se inscricao 
                 * sera o escolhido, sendo esse o que ja esta armazenado na 
                 * variavel max */
                }
            }
        }
        /* Atribuicao do classificado na posicao j+1 ao vetor da classificacao 
         * final */
        classification[j] = max + 1;
        
        /* Retirada da matriz de preferencias o candidato ja alocado a sua 
         * posicao, para assim poder analisar apenas os restantes */ 
        for (l = 0; l < MEMBERS; l++) {
            for (m = 0; m < candidates - j; m++) {
                if (pref[l][m] == max + 1) {
                    for (z = m + 1; z < candidates - j; z++) {
                        pref[l][z-1] = pref[l][z];
                    }
                }
            }
        }
    }
}