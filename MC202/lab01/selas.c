/* Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laborat�rio 01 - Pontos de sela                               */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20 /* Numero m�ximo da ordem da matriz */

void exclude_com();
void invalid_input();
void read_mat(int matrix[MAX_N][MAX_N], int n, int col_max[MAX_N]);
void check_selas(int matrix[MAX_N][MAX_N], int col_max[MAX_N], int n);

int main() {
	int n, verify;
	int matrix[MAX_N][MAX_N];
	int col_max[MAX_N];
	
	verify = scanf("%d", &n);
	
	if ((verify != 1) || (n > 20) || (n < 1))
		invalid_input();
	
	exclude_com();
	
	read_mat(matrix, n, col_max);
	
	printf("Os pontos de sela da matriz s�o:\n\n");
	
	check_selas(matrix, col_max, n);
	
	return 0;
}

/* Func�o que ignora os coment�rios das linhas */
void exclude_com() {
	char c;
	
	do { c = getchar(); }
	while ((c != '\n') && (c != EOF));
}

/* Fun��o que interrompe o programa caso a entrada seja inv�lida */
void invalid_input() {
	
	printf("Dados inv�lidos\n");
	
	exit(0);
}

/* Fun��o que realiza a leitura da matriz, determina os valores m�ximos de cada
 * coluna e determina se os dados passados pelo usu�rio s�o v�lidos */
void read_mat(int matrix[MAX_N][MAX_N], int n, int col_max[MAX_N]) {
	int i, j, verify;
	
	for (j = 0; j < n; j++) {
		verify = scanf("%d", &matrix[0][j]);
			
		if (verify != 1)
			invalid_input();
		
		/* Contabiliza os valores da primeira linha para compara��o */
		col_max[j] = matrix[0][j];
	}
	
	exclude_com();
	
	for (i = 1; i < n; i++) {
		for (j = 0; j < n; j++) {
			verify = scanf("%d", &matrix[i][j]);
			
			if (verify != 1)
				invalid_input();
			
			/* Faz as compara��es para encontrar o valor m�ximo de cada coluna*/
			if (matrix[i][j] > col_max[j])
				col_max[j] = matrix[i][j];
			
		}
		exclude_com();
	}
	
}

/* Fun��o que encontra os valores m�nimos em cada linha e determina se eles
 * formam pontos de sela */
void check_selas(int matrix[MAX_N][MAX_N], int col_max[MAX_N], int n) {
	int value, count, min[MAX_N], i, j, ok = 0;
	
	for (i = 0; i < n; i++) {
		value = matrix[i][0];
		min[0] = 0;
		count = 1; /* Contador de minimos na linha */
		for (j = 1; j < n; j++) {
			if (value > matrix[i][j]) {
				value = matrix[i][j];
				min[0] = j;
				count = 1;
			} else if (value == matrix[i][j]) {
				min[count] = j;
				count++;
			}
		}
		
		for (j = 0; j < count; j++) {
			if (value == col_max[min[j]]) {
				printf("%4d%4d%4d\n", i, min[j], value);
				ok = 1;
			}
		}
	}
	
	if (!ok)
		printf("    nenhum\n");
}
