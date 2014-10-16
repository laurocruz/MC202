/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Email: laurocruzsouza@gmail.com
 * Laboratorio 14b - Liber8 */

#include <stdio.h>
#include <stdlib.h>

/* Alocacao dinamica de matriz de caracteres */
char ** alloc_matrix(int lines, int columns);
/* Desalocacao da matriz alocada dinamicamente */
void free_matrix (char **matrix, int lines);
/* Funcao recursiva que realiza as explosoes de uma bomba e de todas as outras
 * dentro do raio de explosao */
void explosion(char **map, int lines, int columns, int x, int y);

int main() {
	int lines, columns, linx, coly;
	int i;
	char **map;
	
	/* Quantidadede linhas e colunas do matriz e a posicao da bomba escolhida */
	scanf("%d %d %d %d", &lines, &columns, &linx, &coly);
	
	/* Alocacao da matriz */
	map = alloc_matrix(lines, columns + 1);
	
	/* Leitura da matriz */
	for (i = 0; i < lines; i++)
		scanf("%s", map[i]);
	
	/* Realizacao das explosoes */
	explosion(map, lines, columns, linx-1, coly-1);
	
	/* Impressao do mapa apos as explosoes */
	for (i = 0; i < lines; i++)
		printf("%s\n", map[i]);
	
	/* Desalocacao da matriz */
	free_matrix(map, lines);
	
	return 0;
}

/* Alocacao dinamica de matriz */
char ** alloc_matrix(int lines, int columns) {
	int i;
	char **matrix;
	
	matrix = malloc(lines * sizeof(char *));
	
	for (i = 0; i < lines; i++)
		matrix[i] = malloc(columns * sizeof(char));
	
	return matrix;
}

/* Desalocacao de matriz */
void free_matrix (char **matrix, int lines) {
	int i;
	
	for (i = 0; i < lines; i++)
		free(matrix[i]);
	
	free(matrix);
}

void explosion(char **map, int lines, int columns, int x, int y) {
	int r, space, xi, yi;
	int i, j;
	
	/* Raio da explosao (pela tabela ASCII: '0' == 48) */
	r = map[x][y] - 48;
	/* Tranforma a posicao em que estava a bomba que foi explodida em 'B' */
	map[x][y] = 'B';
	
	/* Tamanho dos lados do quadrado no qual ocorre a explosao */
	space = 2*r + 1;
	
	/* Posicoes iniciais da submatriz na qual ocorrera a explosao */
	xi = x - r;
	yi = y - r;
	
	for (i = 0; i < space; i++) {
		for (j = 0; j < space; j++) {
			/* Condicao para que assegure-se que a posicao pertence ao mapa */
			if ((xi + i >= 0) && (xi + i < lines) && (yi + j >= 0) && 
				(yi + j < columns)) {
				/* Se houver um ponto, a regiao é 'explodida' */
				if (map[xi+i][yi+j] == '.')
					map[xi+i][yi+j] = 'x';
				/* Se houver outra bomba, é feita a chamada recursiva da funcao
				 * para promover a explosao da outra bomba achada */
				else if ((map[xi+i][yi+j] >= '0') && (map[xi+i][yi+j] <= '9'))
					explosion(map, lines, columns, xi+i, yi+j);
			}
		}
	}
}