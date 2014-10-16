/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 07b - Modern Word Search */

#include <stdio.h>

/* Prototipo da funcao de comparacao entre os caracteres da matriz e da palavra */
int igual(char letra_mat, char letra_pal);

int main() {
    /* Declaracao da matrize do caca-palavras, matriz com as palavras encontradas em
     * "highlight" e vetor da palavra procurada */
    char cacapal[50][51], final[50][50], palavra[26];
    /* Quatro marcadores de iteracao, quantidade de linhas e colunas da matriz do
     * caca-palavras, tamanho da palavra procurada, contador de palavras encontradas e
     * flag para procurar as palavras */
    int i, j, k, l, linhas, colunas, tam = 0, contador = 0, achou = 1;
    
    /* Inicialmente todas as posicoes da matriz 'final' tem o caracter '.' */
    for (i = 0; i < 50; i++) {
        for (j = 0; j < 50; j++) {
            final[i][j] = '.';
        }
    }
    
    /* Leitura das quantidades de linhas e colunas do caca-palavras e da palavra
     * procurada */
    scanf("%d %d %s", &linhas, &colunas, palavra);
    
    /* Calculando o tamanho da palavra procurada */
    while (palavra[tam] != '\0') {
        tam++;
    }

    /* Leitura da matriz do caca-palavras */
    for (i = 0; i < linhas; i++) {
        scanf("%s", cacapal[i]);
    }

    /* Procurando palavras na horizontal */
    for (i = 0; i < linhas; i++) {
        for (j = 0; j <= colunas-tam; j++) {
            /* Ao encontrar a primeira letra da palavra inicia-se a procura pelas
             * subsequentes */
            if (igual(cacapal[i][j], palavra[0])) {
                achou = 1;
                /* Procura pelas subsequentes */
                for (k = 1; (k < tam) && (achou != 0); k++) {
                    /* Caso algum caractere seja diferente do esperado, o flag e zerado e
                     * a procura pela palavra em outras posicoes inicia-se novamente */
                    if (igual(cacapal[i][j+k], palavra[k]) == 0) {
                        achou = 0;
                    /* Entrar nessa condicional significa que a palavra foi devidamente
                     * encontrada */
                    } else if (k == tam - 1) {
                        /* Aumenta-se uma unidade ao contador de palavras */
                        contador++;
                        /* A palavra e marcada sobre a matriz que sera impressa ao final
                         * do programa */
                        for (k = 0; k < tam; k++) {
                            final[i][j+k] = cacapal[i][j+k];
                        }
                    }
                }
            }
        }
    }

    /* Procurando palavras na vertical */
    for (j = 0; j < colunas; j++) {
        for (i = 0; i <= linhas-tam; i++) {
            /* Ao encontrar a primeira letra da palavra inicia-se a procura pelas
             * subsequentes */
            if (igual(cacapal[i][j], palavra[0])) {
                achou = 1;
                /* Procura pelas subsequentes */
                for (k = 1; (k < tam) && (achou != 0); k++) {
                    /* Caso algum caractere seja diferente do esperado, o flag e zerado e
                     * a procura pela palavra em outras posicoes inicia-se novamente */
                    if (igual(cacapal[i+k][j], palavra[k]) == 0) {
                        achou = 0;
                    /* Entrar nessa condicional significa que a palavra foi devidamente
                     * encontrada */
                    } else if (k == tam - 1) {
                        /* Aumenta-se uma unidade ao contador de palavras */
                        contador++;
                        /* A palavra e marcada sobre a matriz que sera impressa ao final
                         * do programa */
                        for (k = 0; k < tam; k++) {
                            final[i+k][j] = cacapal[i+k][j];
                        }
                    }
                }
            }
        }
    }

    /* Procurando palavras na diagonal */
    for (i = 0; i <= linhas-tam; i++) {
        for (j = 0; j <= colunas-tam; j++) {
            /* Ao encontrar a primeira letra da palavra inicia-se a procura pelas
             * subsequentes */
            if (igual(cacapal[i][j], palavra[0])) {
                achou = 1;
                /* Procura pelas subsequentes */
                for (k = 1, l = 1; (k < tam) && (achou != 0); k++, l++) {
                    /* Caso algum caractere seja diferente do esperado, o flag e zerado e
                     * a procura pela palavra em outras posicoes inicia-se novamente */
                    if (igual(cacapal[i+l][j+k], palavra[k]) == 0) {
                        achou = 0;
                    /* Entrar nessa condicional significa que a palavra foi devidamente
                     * encontrada */
                    } else if (k == tam - 1) {
                        /* Aumenta-se uma unidade ao contador de palavras */
                        contador++;
                        /* A palavra e marcada sobre a matriz que sera impressa ao final
                         * do programa */
                        for (k = 0, l = 0; k < tam; k++, l++) {
                            final[i+l][j+k] = cacapal[i+l][j+k];
                        }
                    }
                }
            }
        }
    }
    /* Imprimindo a palavra procurada e quantas foram encontradas */
    printf("%s %d\n", palavra, contador);
    
    /* Imprimindo a matriz final com apenas as palavras encontradas em "highlight" e
     * todos os outros caracteres trocados por '.' */
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            printf("%c", final[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
/* Funcao de comparacao */
/* Retorna 1 se os caracteres forem iguais (verdadeira) e 0 se foram diferentes (falsa) */
int igual(char letra_mat, char letra_pal) {
    int z;
    /* Se ambos fores letras e foram iguais, então a funcao é "verdadeira */
    if (letra_mat == letra_pal) {
        z = 1;
    /* Como '_' pode ser trocada por qualquer caractere, sera igual a letra da palavra,
     * nao importa qual seja */
    } else if (letra_mat == '_') {
        z = 1;
    /* O caractere '#' pode ser substituido por qualquer vogal */
    } else if (letra_mat == '#') {
        /* Se a letra da palavra for uma vogal, ela é igual a '#' */
        if ((letra_pal == 'a') || (letra_pal == 'e') || (letra_pal == 'i') || (letra_pal
== 'o') || (letra_pal == 'u')) {
            z = 1;
        /* Se for uma consoante são diferentes */
        } else {
            z = 0;
        }
    /* O caractere '%' pode ser substituido por qualquer consoante */
    } else if (letra_mat == '%') {
        /* Se a letra da palavra for uma vogal, ela é diferente de '%' */
        if ((letra_pal == 'a') || (letra_pal == 'e') || (letra_pal == 'i') || (letra_pal
== 'o') || (letra_pal == 'u')) {
            z = 0;
        /* Se for uma consoante são iguais */
        } else {
            z = 1;
        }
    /* Se ambos foram letras e foram diferentes, a funcao é "falsa" */
    } else if (letra_mat != letra_pal) {
        z = 0;
    }
    return z;
}