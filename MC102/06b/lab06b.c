/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 06b - Fruit Crush Saga - Part II */

#include <stdio.h>

/* Prototipo da funcao jogada */
int jogada(char tabuleiro[50][51], int linhas, int colunas, int lin, int col);

int main() {
    /* Declaracao da matriz que recebera a strings das frutas */
    char tabuleiro[50][51];
    /* Quantidade de linhas e colunas da matriz e de jogadas */
    int linhas, colunas, jogadas;
    /* Posicao da fruta escolhida pelo jogador */
    int lin, col;
    /* Variaveis do contador de pontos, a pontuacao do jogador e marcador de iteracao */
    int cont, score = 0, l;

    /* Leitura das quantidades de linhas e colunas da matriz e jogadas */
    scanf("%d %d %d", &linhas, &colunas, &jogadas);
    
    /* Leitura das strings de posicao das frutas */
    for (l = 0; l < linhas; l++) {
        scanf("%s", tabuleiro[l]);
    }

    /* Realizador das jogadas */
    for (l = 1; l <= jogadas; l++) {
        /* Leitura da posicao da fruta */
        scanf("%d %d", &lin, &col);
        if (tabuleiro[lin-1][col-1] != '.') {
            /* Realizacao da funcao 'jogada' atribuindo o contador de pontos a cont */
            cont = jogada(tabuleiro, linhas, colunas, lin, col);
            /* Calculando a pontuacao */
            score += cont*cont;
        }
    }

    /* Imprimindo a pontuacao */
    printf("Score: %d\n", score);
    
    /* Imprimindo a matriz apos todas as jogadas */
    for (l = 0; l < linhas; l++) {
        printf("%s\n", tabuleiro[l]);
    }
    return 0;
}

/* Funcao para calcular os pontos e promover o efeito gravidade */
int jogada(char tabuleiro[50][51], int linhas, int colunas, int lin, int col) {
    /* Declaracao das variaveis contador dos pontos, contador de frutas atingidas na
     * vertical, flag de frutas sequenciais e de quebra e sequencia coluna acima, marcador
     * do ponto em que as frutas pararam de ser atingidas na vertical */
    int contador = 1, vertical = 1, row, acima = 0, pontomax, i, k, j;
    /* Variavel que guardara o valor da fruta escolhida */
    char fruta;
    
    /* Atribuicao do valor da fruta a variavel 'fruta */
    fruta = tabuleiro[lin-1][col-1];
    tabuleiro[lin-1][col-1] = '.';

    /* Testes de frutas equivalentes coluna abaixo */
    for (i = 0, row = 1; (lin+i < linhas) && (row != 0); i++) {
        if (tabuleiro[lin+i][col-1] == fruta) {
            contador++;
            vertical++;
            tabuleiro[lin+i][col-1] = '.';
        } else {
            row = 0;
        }
    }

    /* Testes de frutas equivalentes coluna acima */
    for (i = 1, row = 1; (lin-i-1 >= 0) && (row != 0); i++) {
        if (tabuleiro[lin-i-1][col-1] == fruta) {
            contador++;
            vertical++;
            tabuleiro[lin-i-1][col-1] = '.';
        } else {
            pontomax = lin-i-1;
            row = 0;
            acima = 1;
        }
    }

    /* "Efeito gravidade" na vertical*/
    for (k = pontomax; (k >= 0) && (acima != 0); k--) {
        tabuleiro[k + vertical][col-1] = tabuleiro[k][col-1];
        if (k < vertical) {
            tabuleiro[k][col-1] = '.';
        }
    }

    /* Teste de frutas equivalentes a direita da linha */
    for (j = 0, row = 1; (col+j < colunas) && (row != 0); j++) {
        if (tabuleiro[lin-1][col+j] == fruta) {
            contador++;
            /* "Efeito Gravidade" na horizontal */
            for (k = lin - 2; k >= 0; k--) {
                tabuleiro[k+1][col+j] = tabuleiro[k][col+j];
            }
            tabuleiro[0][col+j] = '.';
        } else {
            row = 0;
        }
    }

    /* Teste de frutas equivalentes a esquerda da linha */
    for (j = 1, row = 1; (col-1-j >= 0) && (row != 0); j++) {
        if (tabuleiro[lin-1][col-1-j] == fruta) {
            contador++;
            /* "Efeito Gravidade" na horizontal */
            for (k = lin - 2; k >= 0; k--) {
                tabuleiro[k+1][col-1-j] = tabuleiro[k][col-1-j];
            }
            tabuleiro[0][col-1-j] = '.';
        } else {
            row = 0;
        }
    }
    
    /* Retorna o contador de pontos */
    return contador;

}