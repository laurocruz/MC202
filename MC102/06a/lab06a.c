/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 06a - Fruit Crush Saga - Part I */

#include <stdio.h>

int main() {
    /* Declaracao da matriz que recebera a strings das frutas */
    char tabuleiro[50][51];
    /* Quantidade de linhas e colunas da matriz */
    int linhas, colunas;
    /* Posicao da fruta escolhida pelo jogador */
    int lin, col;
    /* Variaveis do contador de pontos, flag de parada, a pontuacao do jogador  
     * dois marcadores de iteracao */
    int contador = 1, row = 1, pontuacao, i, j;
    
    /* Leitura das quantidades de linhas e coluna e posicao da fruta */
    scanf("%d %d %d %d", &linhas, &colunas, &lin, &col);
    
    /* Leitura das strings de posicao das frutas */
    for (i = 0; i < linhas; i++) {
        scanf("%s", tabuleiro[i]);
    }
    
    /* Testes de frutas equivalentes coluna abaixo */
    for (i = 0, row = 1; (lin+i < linhas) && (row != 0); i++) {
        if (tabuleiro[lin+i][col-1] == tabuleiro[lin-1][col-1]) {
            contador++;
            tabuleiro[lin+i][col-1] = 'X';
        } else {
            row = 0;
        }
    }
    
    /* Testes de frutas equivalentes coluna acima */
    for (i = 1, row = 1; (lin-1-i >= 0) && (row != 0); i++) {
        if (tabuleiro[lin-1-i][col-1] == tabuleiro[lin-1][col-1]) {
            contador++;
            tabuleiro[lin-1-i][col-1] = 'X';
        } else {
            row = 0;
        }
    }
    
    /* Teste de frutas equivalentes a direita da linha */
    for (j = 0, row = 1; (col+j < colunas) && (row != 0); j++) {
        if (tabuleiro[lin-1][col+j] == tabuleiro[lin-1][col-1]) {
            contador++;
            tabuleiro[lin-1][col+j] = 'X';
        } else {
            row = 0;
        }
    }
    
    /* Teste de frutas equivalentes a esquerda da linha */
    for (j = 1, row = 1; (col-1-j >= 0) && (row != 0); j++) {
        if (tabuleiro[lin-1][col-1-j] == tabuleiro[lin-1][col-1]) {
            contador++;
            tabuleiro[lin-1][col-1-j] = 'X';
        } else {
            row = 0;
        }
    }
    
    /* Atribuicao do numero da fruto escolhida como X */
    tabuleiro[lin-1][col-1] = 'X';
    
    /* Calculando a posicao */
    pontuacao = contador*contador;
    
    /* Imprimindo a pontuacao */
    printf("Score: %d\n", pontuacao);
    
    /* Imprimindo a matriz apos as substituicoes por X */
    for (i = 0; i < linhas; i++) {
        printf("%s\n", tabuleiro[i]);
    }
    
    return 0;
}
