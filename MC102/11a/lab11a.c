/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 11a - Copa do Mundo */

#include <stdio.h>
#include <string.h>

/* Registro das informacoes de cada time e seus jogos */
struct team {
    /* Nome do time */
    char name[16];
    /* Pontos obtidos apos os jogos */
    int points;
    /* Quantidade de gols marcados */
    int goalsMade;
    /* Quantidade de gols sofridos */
    int goalsSuff;
    /* Saldo de gols final */
    int goalsDiff;
};

/* Definicao de um tipo struct team chmado team */
typedef struct team team;

void reading_games (team teams[][4]);
void change_team(team *a, team *b);
void placing_teams(team teams[][4]);
void print_classification(team teams[][4]);
void quarter_final(team teams[][4]);

int main() {
    int i, j;
    /* Matriz de registros dos times, sena cada linha um dos grupos */
    team teams[8][4];
    
    /* Zerando os contadores dentro da matriz */
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            teams[i][j].points = 0;
            teams[i][j].goalsDiff = 0;
            teams[i][j].goalsMade = 0;
            teams[i][j].goalsSuff = 0;
        }
    }
    
    
    reading_games(teams);
    placing_teams(teams);
    print_classification(teams);
    quarter_final(teams);
    
    return 0;
}

/* Funcao para ler os valores de cada jogo e fazer a contagem de gols e pontos 
 * de cada time */
void reading_games (team teams[][4]) {
    char name_team1[15], name_team2[15];
    int goals_team1, goals_team2, i, j, k;
    
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 6; j++) {
            scanf("%s %d x %d %s", name_team1, &goals_team1, &goals_team2, 
                  name_team2);
            
            /* Fazendo a atribuicao dos nomes das selecoes aos registros */
            if (j == 0) {
                strcpy (teams[i][0].name, name_team1);
                strcpy (teams[i][1].name, name_team2);
            } else if (j == 1) {
                strcpy (teams[i][2].name, name_team1);
                strcpy (teams[i][3].name, name_team2);
            }
            
            
            for (k = 0; k < 4; k++) {
                /* Quando achar a selecao 1 da qual foi lida o placar */
                if (strcmp(name_team1, teams[i][k].name) == 0) {
                    /* Armazena seus gols feitos */
                    teams[i][k].goalsMade += goals_team1;
                    /* Armazena seus gols sofridos */
                    teams[i][k].goalsSuff += goals_team2;
                    
                    /* Contabiliza os pontos ganhos com a partida */
                    if (goals_team1 > goals_team2) {
                        teams[i][k].points += 3;
                    } else if (goals_team1 == goals_team2) {
                        teams[i][k].points++;
                    }
                    
                }
                
                /* Quando achar a selecao 2 da qual foi lida o placar */
                if (strcmp(name_team2, teams[i][k].name) == 0) {
                    /* Armazena seus gols feitos */
                    teams[i][k].goalsMade += goals_team2;
                    /* Armazena seus gols sofridos */
                    teams[i][k].goalsSuff += goals_team1;
                    
                    /* Contabiliza os pontos ganhos com a partida */
                    if (goals_team1 < goals_team2) {
                        teams[i][k].points += 3;
                    } else if (goals_team1 == goals_team2) {
                        teams[i][k].points++;
                    }
                    
                }
            }
        }
        /* Faz o calculo do saldo de gols com base nos gols feitos e tomados de 
         * cada selecacao */
        for (k = 0; k < 4; k++) {
            teams[i][k].goalsDiff = teams[i][k].goalsMade - 
            teams[i][k].goalsSuff;
        }
    }
}

/* Funcao para fazer a troca de dois registros */
void change_team(team *a, team *b) {
    team aux;
    
    aux = *a;
    *a = *b;
    *b = aux;
}

/* Funcao para achar a palavra que vem primeiro na ordem alfabetica */
int alphabetical(char vet1[], char vet2[], int k, int first) {
    int flag = 1, l = 0, fir;
    
    while (flag)  {
        if (vet1[l] < vet2[l]) {
            fir = k;
            flag = 0;
        } else if (vet1[l] > vet2[l]) {
            fir = first;
            flag = 0;
        }
        l++;
    }
    /* Retorna o indice do registro que tem o nome da selecao de menor tamanho 
     * alfabeticamente */
    return fir;
}

/* Fazendo a ordenacao dos times */
void placing_teams(team teams[][4]) {
    int i, j, k, first;
    
    /* Analisa cada grupo um por um */
    for (i = 0; i < 8; i++) {
        /* SELECTION SORT */
        for (j = 0; j < 3; j++) {
            first = j;
            
            for (k = j+1; k < 4; k++) {
                /*Primeiramente a ordenacao e feita usando os pontos dos times*/
                if (teams[i][k].points > teams[i][first].points) {
                    first = k;
                /* Quando tem pontos iguais... */
                } else if (teams[i][k].points == teams[i][first].points) {
                    /* Utiliza-se o saldo de gols */
                    if (teams[i][k].goalsDiff > teams[i][first].goalsDiff) {
                        first = k;    
                    /* Quando os saldos são iguais... */    
                    } else if (teams[i][k].goalsDiff == 
                               teams[i][first].goalsDiff) {
                        /* Utiliza-se quem fez mais gols */
                        if (teams[i][k].goalsMade > teams[i][first].goalsMade) {
                            first = k;    
                        /* Quando as quantidade de gols e igaul... */
                        } else if (teams[i][k].goalsMade == 
                                   teams[i][first].goalsMade) {
                            /* Utiliza-se a ordem alfabetica */
                            first = alphabetical(teams[i][k].name,
                                    teams[i][first].name, k, first);
                        }
                    }
                }
            }
            /* Troca de posicao dos registros */
            change_team(&teams[i][j], &teams[i][first]);
        }
    }
}

/* Imprimindo os times de cada grupo na ordem de classificacao e seus pontos,
 * saldos de gols, gols marcados e gols sofridos */
void print_classification(team teams[][4]) {
    int i, j;
    
    for (i = 0; i < 8; i++) {
        printf("Grupo %c:\n", i+65);
        for (j = 0; j < 4; j++) {
            printf("%-15s %3d %3d %3d %3d\n",teams[i][j].name, 
                   teams[i][j].points, teams[i][j].goalsMade, 
                   teams[i][j].goalsSuff, 
                   teams[i][j].goalsDiff);
        }
        printf("\n");
    }
}

/* Imprime quais serao os jogos das oitavas de final */
void quarter_final(team teams[][4]) {
    int i, j = 1, k = 0;
    
    printf("Oitavas de final:\n");
    for (i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            printf("%15s x %s\n", teams[i][0].name, teams[j][1].name);
            j += 2;
        } else {
            printf("%15s x %s\n", teams[i][0].name, teams[k][1].name);
            k += 2;
        }
    }
}
    
    
        