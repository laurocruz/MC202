#include <stdio.h>
#include <stdlib.h>

struct Move {
	int line, column;
};

typedef struct Move Move;

int ** alloc_matrix(int lines, int columns) {
	int i, **matrix;
	
	matrix = malloc(lines * sizeof(int *));
	
	for (i = 0; i < lines; i++)
		matrix[i] = malloc(columns * sizeof(int));
	
	return matrix;
}

void free_matrix(int lines, int **matrix) {
	int i;
	
	for (i = 0; i < lines; i++)
		free(matrix[i]);
	
	free(matrix);
}

void imprimeLabirinto(int **M, int n, int m) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (M[i][j] == -2) printf(" XX");
			if (M[i][j] == -1) printf(" ");
			if (M[i][j] >= 0) printf(" %02d", M[i][j]);
		}
		printf("\n");
	}
}

void obtemLabirinto(int **M, int n, int m) {
	int i, j, d;
	
	/* Labirinto: 1 = parede ou obstaculo
	 0* = posicao livre */
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			scanf("%d", &d);
			if (d == 1)
				M[i][j] = -2;
			else
				M[i][j] = -1;
		}
}

int labirinto(int **lab, Move move[], int Li, int Ci, int Lf, int Cf) {
	int L, C, i, passos;
	
	if ((Li == Lf) && (Ci == Cf))
		return lab[Lf][Cf];
	else {
		for (i = 0; i < 4; i++) {
			L = Li + move[i].line;
			C = Ci + move[i].column;
			
			if (lab[L][C] == -1) {
				lab[L][C] = lab[Li][Ci] + 1;
				
				passos = labirinto(lab, move, L, C, Lf, Cf);
				
				if (passos > 0)
					return passos;
			}
		}
	}
	
	return 0;
}

int main() {
	int **lab; 
	int lines, columns, Li, Ci, Lf, Cf, answer;
	Move move[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	
	scanf("%d %d", &lines, &columns); /* Dimensoes do labirinto */
	scanf("%d %d", &Li, &Ci); /* Coordenadas da posicao inicial */
	scanf("%d %d", &Lf, &Cf); /* Coordenadas da posicao final (saida) */
	
	lab = alloc_matrix(lines, columns);
	
	obtemLabirinto(lab, lines, columns);
	
	lab[Li - 1][Ci - 1] = 0;
	
	answer = labirinto(lab, move, Li - 1, Ci - 1, Lf - 1, Cf - 1);
	
	if (!answer)
		printf("Nao ha solucao\n");
	else
		imprimeLabirinto(lab, lines, columns);
	
	free_matrix(lines, lab);
	
	return 0;
}
