/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Email: laurocruzsouza@gmail.com
 * Laboratorio 13b - Fruit Crush Saga - Part III */

#include <stdio.h>
#include <stdlib.h>

char ** alloc_matrix(int lines, int columns);
void free_matrix(char **matrix, int lines);
void play(char **board, int lines, int columns, int lin, int col, int fruit, 
		 int *count);
void down(char **board, int i, int j);
void gravity (char **board, int lines, int columns);

int main() {
	char **board;
	int lines, columns, plays;
	int fruit;
	int lin, col;
	int count, score = 0, l;
	
	/* Leitura da quantidades de linhas, colunas e jogadas a serem feitas */
	scanf("%d %d %d", &lines, &columns, &plays);
	
	/* Alocacao da matriz do tabuleiro */
	board = alloc_matrix(lines, columns + 1);
	
	/* Leitura das strings de posicao das frutas */
	for (l = 0; l < lines; l++)
		scanf("%s", board[l]);
	
	/* Realizador das jogadas */
	for (l = 1; l <= plays; l++) {
		/* Leitura da posicao da fruta */
		scanf("%d %d", &lin, &col);
		count = 0;
		if ((board[lin-1][col-1] != '.') && (board[lin-1][col-1] != '*')) {
			count++;
			/* Armazena o numero da fruta escolhida */
			fruit = board[lin-1][col-1];
			/* Realiza a jogada */
			play(board, lines, columns, lin, col, fruit, &count);
			/* Promove o efeito gravidade */
			gravity(board, lines, columns);
			/* Calcula a pontuacao */
			score += count*count;
		}
	}
	
	/* Imprimindo a pontuacao */
	printf("Score: %d\n", score);
	
	/* Imprimindo a matrix apos todas as plays */
	for (l = 0; l < lines; l++)
		printf("%s\n", board[l]);
	
	/* Desalocando a matriz do tabuleiro */
	free_matrix(board, lines);
	
    return 0;
}

/* Funcao de alocacao da matriz do tabuleiro */
char ** alloc_matrix(int lines, int columns) {
	int i;
	char **matrix;
	
	matrix = malloc(lines * sizeof(char *));
	
	for (i = 0; i < lines; i++)
		matrix[i] = malloc(columns * sizeof(char));
	
	return matrix;
}

/* Funcao de desalocacao da matriz do tabuleiro */
void free_matrix(char **matrix, int lines) {
	int i;
	
	for (i = 0; i < lines; i++)
		free(matrix[i]);
	
	free(matrix);
}

/* Funcao que realiza as jogadas */
void play(char **board, int lines, int columns, int lin, int col, int fruit, 
		 int *count) {
	
	/* Cada fruta encontrada e trocada por um X */
	board[lin-1][col-1] = 'X';
	
	/* Caso haja uma fruta adjacente ACIMA */
	if ((lin - 2 >= 0) && (board[lin-2][col-1] == fruit)) {
		(*count)++;
		play(board, lines, columns, lin-1, col, fruit, count);
	}
	
	/* Caso haja uma fruta adjacente ABAIXO */
	if ((lin < lines) && (board[lin][col-1] == fruit)) {
		(*count)++;
		play(board, lines, columns, lin+1, col, fruit, count);
	}
	
	/* Caso haja uma fruta adjacente a ESQUERDA */
	if ((col - 2 >= 0) && (board[lin-1][col-2] == fruit)) {
		(*count)++;
		play(board, lines, columns, lin, col-1, fruit, count);
	}
	
	/* Caso haja uma fruta adjacente a DIREITA */
	if ((col < columns) && (board[lin-1][col] == fruit)) {
		(*count)++;
		play(board, lines, columns, lin, col+1, fruit, count);
	}
}

/* Funcao que faz a gravidade para cada X encontrado la linha pela funcao
 * gravity */
void down(char **board, int i, int j) {
	while ((i-1 >= 0) && (board[i-1][j] != '.') && (board[i-1][j] != '*')) {
		board[i][j] = board[i-1][j];
		i--;
	}
	board[i][j] = '.';
}

/* Funcao que realiza o efeito gravidade */
void gravity (char **board, int lines, int columns) {
	int i, j;
	
	for (i = 0; i < lines; i++) {
		for (j = 0; j < columns; j++) {
			/* Caso ache um X na linha, significa que essa fruta foi retirada */
			if (board[i][j] == 'X') { 
				down(board, i, j);
			}
		}
	}
}