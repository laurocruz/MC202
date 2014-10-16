/* Nome: Lauro Cruz e Souza 
 * RA: 156175
 * Laboratorio 10a - LSCrypto */

#include <stdio.h>
#include <stdlib.h>

/* Quantidade maxima de letras em cada linha */
#define MAX_LETTERS 501
/* Quantidade de letras no alfabeto */
#define N_LETTERS 26

/* Definiciao do tipo do registro 'letters' */
typedef struct letters letters;

/* Declaracao que do registro que armazenara as letras e quantas vezes elas
 * aparecem no texto */
struct letters {
    char let;
    int count;
};

char ** char_matrix_alloc(int lines, int columns);
void char_free_matrix(char **matrix, int lines);
void strings_read_matrix(char **matrix, int lines, int columns);
void counting_letters(char **text, letters alphabet[], int lines);
void sort_alphabet(letters alphabet[]);
char return_letters(letters alphabet[], char letter);
void encrypt(letters alphabet[], char **text, int lines);
void print_matrix_strings(char **matrix, char lines);

int main() {
    int lines, i;
    char **text;
    /* Vetor de registros que armazenarao as letras do alfabeto */
    letters alphabet[N_LETTERS];
    
    /* Atribuindo inicialmente todos os contadores como zero e colocando o 
     * vetor do alfabeto em ordem alfabetica (todas letras maisculas) */
    for (i = 0; i < N_LETTERS; i++) {
        alphabet[i].let = i + 65;
        alphabet[i].count = 0;
    }
    
    /* Lendo quantidade de linhas */
    scanf("%d\n", &lines);
    
    /* Alocacao da matriz do texto */
    text = char_matrix_alloc(lines, MAX_LETTERS);
    
    /* Leitura da texto */
    strings_read_matrix(text, lines, MAX_LETTERS);
    
    /* Contagem das letras no texto */
    counting_letters(text, alphabet, lines);
    
    /* Ordenando as letras em ordem descrescente pela quantidade de vezes que 
     * aparecem no texto */
    sort_alphabet(alphabet);
    
    /* Criptografando o texto */
    encrypt(alphabet, text, lines);
    
    /* Imprimindo o texto criptografado */
    print_matrix_strings(text, lines);
    
    /* Desalocando a memoria alocada para a matriz do texto */
    char_free_matrix(text, lines);
    
    return 0;
}

/* Alocacao dinamica da matriz */
char ** char_matrix_alloc(int lines, int columns) {
    char **matrix;
    int i;
    
    matrix = malloc(lines * sizeof(char *));
    
    for (i = 0; i < lines; i++) {
        matrix[i] = malloc(columns * sizeof(char));
    }
    
    return matrix;
}

/* Desalocacao da memoria alocada dinamicamente para a matriz */
void char_free_matrix(char **matrix, int lines) {
    int i;
    
    for (i = 0; i < lines; i++) {
        free(matrix[i]);
    }
    
    free(matrix);
}

/* Leitura da mariz que armazenara o texto */
void strings_read_matrix(char **matrix, int lines, int columns) {
    int i;
    
    for (i = 0; i < lines; i++) {
        fgets(matrix[i], columns, stdin);
    }
}

/* Contagem da quantidade de cada letra no texto */
void counting_letters(char **text, letters alphabet[], int lines) {
    int i, j = 0;
    
    for (i = 0; i < lines; i++) {
        j = 0;
        while ((text[i][j] != '\0') && (text[i][j] != '\n')) {
            /* Se a letra for masculina */
            if ((text[i][j] >= 'A') && (text[i][j] <= 'Z')) {
                (alphabet[text[i][j]-65].count)++;
            /* Se a letra for minuscula */
            } else if ((text[i][j] >= 'a') && (text[i][j] <= 'z')) {
                (alphabet[text[i][j]-97].count)++;
            }
            j++;
        }
    }
}

/* Ordenacao das letras de acordo com a quantidade de vezes que aparecem no 
 * texto */
void sort_alphabet(letters alphabet[]) {
    int i, j, max;
    letters aux;
    
    /* SELECTION SORT */
    for (i = 0; i < N_LETTERS-1; i++) {
        max = i;
        for (j = i+1; j < N_LETTERS; j++) {
            if (alphabet[j].count > alphabet[max].count) {
                max = j;
            }
        }
        /* Ao encontrar o maximo, faz a troca de todo o registro, assim 
         * ordenando as letras juntamente com a quantidade com que aparecem no 
         * texto */
        aux = alphabet[max];
        alphabet[max] = alphabet[i];
        alphabet[i] = aux;
    }
}

/* Funcao para retornar a letra pela qual sera substituida alguma letra no 
 * texto durante a criptografacao */
char return_letters(letters alphabet[], char letter) {
    int i, flag = 1;
    char l;
    
    for (i = 0; (i < N_LETTERS) && (flag == 1); i++) {
        /* Caso a letra do texto seja igual a do registro (letra do texto e 
         * maiscula) */
        if (alphabet[i].let == letter) {
            flag = 0;
            /* Se a letra do registro estiver em posicao par, a letra do texto 
             * sera substituida pela letra seguinte no vetor do alfabeto */
            if (i % 2 == 0) {
                l = alphabet[i+1].let;
            /* Caso esteja em posicao impar, sera substituida pela anterior */
            } else {
                l = alphabet[i-1].let;
            }
        /* Pela tabela ASCII, ao adicionar-se 32 ao valor da letra maiscula, 
         * obtem-se a letra minuscula, assim nesse caso esta fazendo a busca 
         * da letra no vetor alfabeto quando a letra do texto e minuscula */
        } else if ((char)(alphabet[i].let + 32) == letter) {
            flag = 0;
            if (i % 2 == 0) {
                l = (char)(alphabet[i+1].let + 32);
            } else {
                l = (char)(alphabet[i-1].let + 32);
            }
        }
        
    }
    return l;
}

/* Criptografa o texto */
void encrypt(letters alphabet[], char **text, int lines) {
    int i, j;
    
    for (i = 0; i < lines; i++) {
        j = 0;
        while ((text[i][j] != '\0') && (text[i][j] != '\n')) {
            /* Caso o caractere sera uma letra ... */
            if (((text[i][j] >= 'A') && (text[i][j] <= 'Z')) || 
                ((text[i][j] >= 'a') && (text[i][j] <= 'z'))) {
                /* Sera atribuida a essa posicao do texto a letra 
                 * correspondente a criptografia */
                text[i][j] = return_letters(alphabet, text[i][j]);
                }
                j++;
        }
    }
}

/* Imprime o texto criptografado */
void print_matrix_strings(char **matrix, char lines) {
    int i;
    
    for (i = 0; i < lines; i ++) {
        printf("%s", matrix[i]);
    }
}