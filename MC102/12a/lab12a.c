/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 12a - CUT++ */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Tamanho maximo do nome dos arquivos de entrada e saida */
#define MAX_NOMEARQ 101
/* Tamanho maximo de cada um dos campos do registro */
#define MAX_CAMP 501

/* Prototipo das funcoes utilizadas pela main */
void gera_csv_reduzido(char fnamein[], char fnameout[]);
char** alloc_matrix(int lines, int columns);
void free_matrix(char **matrix, int lines);
int columns_file(FILE *in);
int lines_file(FILE *in);
void read_lines(FILE *in, int columns, char **values);

int main(int argc, char *argv[]) {
    char fnamein[MAX_NOMEARQ], fnameout[MAX_NOMEARQ];

    strcpy(fnamein, argv[1]);
    strcpy(fnameout, argv[2]);

    gera_csv_reduzido(fnamein, fnameout);

    return 0;
}

/* Funcao para alocar a matriz dinamicamente */
char** alloc_matrix(int lines, int columns) {
	char **matrix;
	int i;
	
	matrix = malloc(lines * sizeof(char *));
	
	for (i = 0; i < lines; i++) {
		matrix[i] = malloc(columns * sizeof(char));
	}
	
	return matrix;
}

/* Funcao para liberar a memoria alocada dinamicamente para a matriz */
void free_matrix(char **matrix, int lines) {
	int i;
	
	for (i = 0; i < lines; i++) {
		free(matrix[i]);
	}
	
	free(matrix);
}

/* Conta a quantidade de colunas (campos) no arquivo de entrada */
int columns_file(FILE *in) {
	int columns = 1;
	char aux;
	
	do {
		fscanf(in, "%c", &aux);
		if (aux == ',')
			columns++;
	} while (aux != '\n');
	
	rewind(in);
	
	return columns;
}

/* Conta a quatidade de linhas no arquivo de entrada */
int lines_file(FILE *in) {
	int lines = 0;
	char x;
	
	while (fscanf(in, "%c", &x) != EOF) {
		if (x == '\n')
			lines++;
	}
	
	rewind(in);
	
	return lines;
}

/* Le os campos em cada linha e atribui a uma matriz values */
void read_lines(FILE *in, int columns, char **values) {
	int i = 0, k;
	char x;
	
	while (i < columns) {
		k = 0;
		fscanf(in, "%c", &x);
		while ((x != ',') && (x != '\n')) {
			values[i][k++] = x;
			fscanf(in, "%c", &x);
		}
		values[i][k] = '\0';
		i++;
	}
}

/* Gera o arquivo de saida */
void gera_csv_reduzido(char fnamein[], char fnameout[]) {
	FILE *in, *out;
	int n, *campos;
	int columns, lines;
	int i, j;
	char **values;
	
	/* Abrindo os arquivos de entrada e saida */
	in = fopen(fnamein, "r");
	out = fopen(fnameout, "w");
	
	/* Se nao conseguir abrir, retorna */
	if ((in == NULL) || (out == NULL)) {
		return;
	}
	
	/* Quantidade de colunas */
	columns = columns_file(in);
	
	/* Quantidade de linhas */
	lines = lines_file(in);
	
	/* Alocacao da matriz que armazenara os campos em cada linha */
	values = alloc_matrix(columns, MAX_CAMP);
	
	/* Quantidade de colunas que serao impressas no arquivo de saida */
	scanf("%d", &n);
	
	/* Alocacao do vetor que armazenara quais colunas serao impressas */
	campos = malloc(n * sizeof(int));
	
	/* Leitura dos numeros das colunas a serem impressas */
	for (i = 0; i < n; i++)
		scanf("%d", &campos[i]);
	
	/* Leitura das linhas do arquivo de entrada */
	for (i = 0; i < lines; i++) {
		read_lines(in, columns, values);
		
		/* Impressao dessas linhas no arquivo de saida */
		for (j = 0; j < n; j++) {
			fprintf(out, "%s", values[campos[j]-1]);
			if (j != n-1)
				fprintf(out, ",");
		}
		fprintf(out, "\n");
	}
	
	/* Fechando os arquivos abertos pelo programa */
	if (in)
		fclose(in);
	if (out)
		fclose(out);
	
	/* Liberando a memoria alocada pela matriz */
	free_matrix(values, columns);
}
