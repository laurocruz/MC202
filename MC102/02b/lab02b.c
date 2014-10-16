/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 02b - Pedra, papel, tesoura, lagarto, Spock */
#include <stdio.h>

int main() {
    
    /* Declaracao das variaveis que representam a jogada de Sheldon e Leonard, os pontos de ambos, o numero de partidas
     * e o indice para o loop */
    int s, l, pl = 0, ps = 0, i, n;
    
    /* Leitura do numero de partidas */
    scanf("%d", &n);

    /* Repeticao que determinara o vencedor de cara rodada e o acumulo de seus pontos */
    for (i = 1; i <= n; i++) {
        scanf("%d %d", &s, &l);
        if ((s == 3) && (l == 2)) {
            ps++;
            printf("Sheldon: Tesoura corta Papel\n");
        }else if ((s == 2) && (l == 1)) {
            ps++;
            printf("Sheldon: Papel embrulha Pedra\n");
        }else if ((s == 1) && (l == 4)) {
            ps++;
            printf("Sheldon: Pedra amassa Lagarto\n");
        }else if ((s == 4) && (l == 5)) {
            ps++;
            printf("Sheldon: Lagarto envenena Spock\n");
        }else if ((s == 5) && (l == 3)) {
            ps++;
            printf("Sheldon: Spock quebra Tesoura\n");
        }else if ((s == 3) && (l == 4)) {
            ps++;
            printf("Sheldon: Tesoura decepa Lagarto\n");
        }else if ((s == 4) && (l == 2)) {
            ps++;
            printf("Sheldon: Lagarto come Papel\n");
        }else if ((s == 2) && (l == 5)) {
            ps++;
            printf("Sheldon: Papel refuta Spock\n");
        }else if ((s == 5) && (l == 1)) {
            ps++;
            printf("Sheldon: Spock vaporiza Pedra\n");
        }else if ((s == 1) && (l == 3)) {
            ps++;
            printf("Sheldon: Pedra quebra Tesoura\n");
        }else if ((s == 2) && (l == 3)) {
            pl++;
            printf("Leonard: Tesoura corta Papel\n");
        }else if ((s == 1) && (l == 2)) {
            pl++;
            printf("Leonard: Papel embrulha Pedra\n");
        }else if ((s == 4) && (l == 1)) {
            pl++;
            printf("Leonard: Pedra amassa Lagarto\n");
        }else if ((s == 5) && (l == 4)) {
            pl++;
            printf("Leonard: Lagarto envenena Spock\n");
        }else if ((s == 3) && (l == 5)) {
            pl++;
            printf("Leonard: Spock quebra Tesoura\n");
        }else if ((s == 4) && (l == 3)) {
            pl++;
            printf("Leonard: Tesoura decepa Lagarto\n");
        }else if ((s == 2) && (l == 4)) {
            pl++;
            printf("Leonard: Lagarto come Papel\n");
        }else if ((s == 5) && (l == 2)) {
            pl++;
            printf("Leonard: Papel refuta Spock\n");
        }else if ((s == 1) && (l == 5)) {
            pl++;
            printf("Leonard: Spock vaporiza Pedra\n");
        }else if ((s == 3) && (l == 1)) {
            pl++;
            printf("Leonard: Pedra quebra Tesoura\n");
        }else{
            printf("Empate\n");
        }
    }
    
    /* Placar final */
    printf("Sheldon %d x %d Leonard\n", ps, pl);
    
    return 0;
}
