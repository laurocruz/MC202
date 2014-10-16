/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 07a - The Voice - Blind Auditions */

#include <stdio.h>

/* Declaracao das variaveis globais que marcarao a posicao a ser atribuida o valor do
 * participante em cada um dos 4 times */
int k1 = 0, k2 = 0, k3 = 0, k4 = 0;

/* Prototipo da funcao que dara a posicao a ser atribuida o valor dos participantes em
 * cada um dos 4 times e que organizara esses posicoes */
int atribuicoes(int time, int teste);

int main() {
    /* Declaracao da matriz que armazenara os jurados que viraram para cada participante e
     * as preferencias de time de cada um */
    int blind[100][9];
    /* Declaracao da matriz que armazenara os candidatos em seus times */
    int times[4][100];
    /* Declaracao das variaveis da quantidade de participantes e a preferencia de time do
     * participante, dependendo da ordem sendo analisada */
    int participantes, tim;
    /* Dois marcadores de iteracao */
    int i, j; 

    /* Leitura da quantidade de participantes */
    scanf("%d", &participantes);

    /* Leitura da matriz blind */
    for (i = 0; i < participantes; i++) {
        for (j = 0; j < 8; j++) {
            scanf("%d", &blind[i][j]);
        }
    }

    /* Alocacao dos candidatos a seus times com base nos jurados que se viraram para eles
     * e suas preferencias */
    for (i = 0; i < participantes; i++) {
        /* Caso o jurado de sua primeira opcao o tenha escolhido */
        if (blind[i][blind[i][4]-1] != 0) {
            tim = blind[i][4];
            times[blind[i][4]-1][atribuicoes(tim, 1)] = i+1;
        /* Caso o jurado de sua segunda opcao o tenha escolhido e o da primeira nao */
        } else if (blind[i][blind[i][5]-1] != 0) {
            tim = blind[i][5];
            times[blind[i][5]-1][atribuicoes(tim, 1)] = i+1;
        /* Caso o jurados de sua terceira opcao o tenha escolhido e os das duas primeiras
         * nao */
        } else if (blind[i][blind[i][6]-1] != 0) {
            tim = blind[i][6];
            times[blind[i][6]-1][atribuicoes(tim, 1)] = i+1;
        /* Caso o jurado de sua ultima opcao o tenha escolhido e os das outras nao */
        } else if (blind[i][blind[i][7]-1] != 0) {
            tim = blind[i][7];
            times[blind[i][7]-1][atribuicoes(tim, 1)] = i+1;
        }
    }

    /* Impressao da situacao final dos quatro times */
    for (i = 0; i < 4; i++) {
        tim = i+1;
        /* Caso o time tenha um participante ou mais */
        if (times[i][0] != 0) {
            printf("Time %d:", tim);
            /* Impressao dos numeros dos participante do time em questao em ordem
             * crescente */
            for (j = 0; j < atribuicoes(tim, 0); j++) {
                printf(" %d", times[i][j]);
            }
        /* Caso o time fique sem nenhum participante */
        } else {
            printf("Time %d: Nenhum participante", tim);
        }
        printf("\n");
    }

    return 0;
}

int atribuicoes(int time, int teste) {
    int k;
    /* Dependendo do time em questao, a funcao incrementara um valor a posicao em questao
     * do time para que um participante possa ser alocado nela */
    if (time == 1) {
        k = k1;
        if (teste == 1) {
            k1++;
        }
    } else if (time == 2) {
        k = k2;
        if (teste == 1) {
            k2++;
        }
    } else if (time == 3) {
        k = k3;
        if (teste == 1) {
            k3++;
        }
    } else if (time == 4) {
        k = k4;
        if (teste == 1) {
            k4++;
        }
    }
    return k;
}