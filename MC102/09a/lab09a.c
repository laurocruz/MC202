/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 09a - Oliver Queen is Alive! */

#include <stdio.h>

/* Tamanho maximo do mapa */
#define MAX_SIZE 30

void read_map(int matrix[][MAX_SIZE], int size);
void case_0(int *line, int *column, char direction, int map[][MAX_SIZE]);
void case_1(int *line, int *column, char *direction, int map[][MAX_SIZE]);
void case_2(int *line, int *column, char *direction, int map[][MAX_SIZE]);

int main() {
    /* Tamanho do mapa, tempo para desativar o TREMOR e contador do tempo */
    int size, time, count_time = 0;
    /* Matriz que fara o papel do mapa */
    int map[MAX_SIZE][MAX_SIZE];
    /* Posicao inicial de Oliver Queen */
    int line = 0, column = 0;
    /* Flags para marcar se Oliver morrer e encontrar TREMOR */
    int dead = 0, found = 0;
    /* Direcao inicial de Oliver: leste(e) */
    char direction = 'e';
    int i, j;

    /* Lendo as dimensoes do mapa e o tempo para desativar tremor */
    scanf("%d %d", &size, &time);
    /* Leitura do mapa */
    read_map(map, size);    

    /* Loop para promover os passos de Oliver até ele morrer, ou desativar 
     * tremor ou acabar o tempo */
    while ((dead == 0) && (found == 0) && (count_time < time)) {
        
        /* Posicao branca */
        if (map[line][column] == 0) {
            case_0(&line, &column, direction, map);
            count_time++;
            
        /* Posicao azul */
        } else if (map[line][column] == 1) {
            case_1(&line, &column, &direction, map);
            count_time++;
            
        /* Posicao verde */
        } else if (map[line][column] == 2) {
            case_2(&line, &column, &direction, map);
            count_time++;
            
        /* Posicao vermelha */
        } else if (map[line][column] == 3) {
            /* Morre ao passar na posicao vermelha */
            dead = 1;
            printf("Oliver morre\n");
            
        /* TREMOR */
        } else if (map[line][column] == 4) {
            /* Desativa TREMOR ao acha-lo */
            found = 1;
            printf("Oliver destroi o dispositivo em %d segundos\n", count_time);
        }
        /* Bate na parede (ultrapassa as bordas) */
        if ((line >= size) || (column >= size) || (line < 0) || (column < 0)) {
            /* Morre ao bater na parede */
            dead = 1;
            printf("Oliver morre\n");
        }
    }
    /* Para quando o tempo acaba e Oliver nao acha TREMOR */
    if ((count_time == time) && (found == 0)) {
        printf("Oliver nao chega ao dispositivo a tempo\n");
    }

    return 0;
}

/* Funcao para leitura das posicoes do mapa */
void read_map(int matrix[][MAX_SIZE], int size) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}
/* Funcao para quando Oliver estiver em posicao branca */
void case_0(int *line, int *column, char direction, int map[][MAX_SIZE]) {
    /* Transforma a posicao branca em azul */
    map[*line][*column] = 1;
    
    /* Define para que direcao deve se mover dependendo do lado para o qual 
     * esta direcionado */
    
    /* Norte */
    if (direction == 'n') {
        (*line)--;
    /* Sul */
    } else if (direction == 's') {
        (*line)++;
    /* Oeste */
    } else if (direction == 'w') {
        (*column)--;
    /* Leste */
    } else if (direction == 'e') {
        (*column)++;
    }
}

/* Funcao para quando Oliver estiver em posicao azul */
void case_1(int *line, int *column, char *direction, int map[][MAX_SIZE]) {
    /* Tranforma a posicao azul em verde */
    map[*line][*column] = 2;
    
    /* Vira Oliver para a esquerda e o movimenta em uma posicao nessa direcao */
    
    /* Norte */
    if (*direction == 'n') {
        /* Vira para oeste */
        *direction = 'w';
        (*column)--;
        
    /* Sul */
    } else if (*direction == 's') {
        /* Vira para leste */
        *direction = 'e';
        (*column)++;
        
    /* Oeste */
    } else if (*direction == 'w') {
        /* Vira para sul */
        *direction = 's';
        (*line)++;
        
    /* Leste */
    } else if (*direction == 'e') {
        /* Vira para norte */
        *direction = 'n';
        (*line)--;
    }
}

/* Funcao para quando Oliver estiver em posicao verde */
void case_2(int *line, int *column, char *direction, int map[][MAX_SIZE]) {
    /* Tranforma a posicao verde em branca */
    map[*line][*column] = 0;

    /* Vira Oliver para a direita e o movimenta em uma posicao nessa direcao */
    
    /* Norte */
    if (*direction == 'n') {
        /* Vira para leste */
        *direction = 'e';
        (*column)++;
        
    /* Sul */
    } else if (*direction == 's') {
        /* Vira para oeste */
        *direction = 'w';
        (*column)--;
        
    /* Oeste */
    } else if (*direction == 'w') {
        /* Vira para norte */
        *direction = 'n';
        (*line)--;
        
    /* Leste */
    } else if (*direction == 'e') {
        /* Vira para sul */
        *direction = 's';
        (*line)++;
    }
}