/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 03b: Fringe */

#include <stdio.h>

int main () {
    
    /* Declaracao das variaveis mols/s, fator S, x e y que receberao os numeros
     * 0 e 1 das fases da onda, quantidade de mols que podem ser passadas pelo
     * portal, quantidade de fases de mesmo tamanho em sequencia, segundos de
     * casa fase e uma variavel auxiliar para gravar os segundos */
    int M, S, x, y, no_mols, qtde_fase = 0, segundos = 0, aux;

    /* Leitura das variaveis mols/s e fator S */
    scanf("%d %d", &M, &S);

    /*Leitura dos dois primeiros valores */
    scanf(" %d", &x);
    scanf(" %d", &y);

    /* Repeticao que "pulara" a primeira fase de numeros, ja que a
     * primeira fase nao pode ser considerada */
    if (x == y) {
        while (x == y) {
            scanf(" %d", &y);
        }
    }
    /* Leitura da segunda fase da sequencia */
    segundos++;
    x = y;
    scanf(" %d", &y);
   
    while (x == y) {
        segundos++;
        scanf(" %d", &y);
    }
    
    /* Leitura das fases consequentes, somando o contador "qtde_fase" caso o
     * numero de segundos da fase e igual ao da fase anterior e reiniciando a
     * contagem caso sejam diferentes. O loop e "quebrado" quando y == -1 */
    while (y != -1) {
        qtde_fase = 1;
        if (aux != 0) {
            segundos = aux;
        }

        do {
            aux = 1;
            x = y;
            scanf(" %d", &y);
            while (x == y) {
                aux++;
                scanf(" %d", &y);
            }
            if ((aux == segundos) && (y != -1)) {
                qtde_fase++;
            }
        } while ((aux == segundos) && (y != -1));
    }

    /* Condicionais imprimem se o portal abre (quando o numero de fases
     * de mesma duracao contabilizadas sao maiores ou iguais ao fator S),
     * imprimindo tambem quantos mols podem passar pelo portal em uma fase, ou
     * se o portal nao abre, sendo assim a quantidade de fases menor que o
     * fator S */
    if (qtde_fase == S) {
        no_mols = M * segundos;
        printf("%d mols\n", no_mols);
    }
    if (qtde_fase > S) {
        no_mols = M * segundos;
        printf("%d mols\n", no_mols);
    }
    if (qtde_fase < S) {
        printf("Portal nao abriu\n");
    }

    return 0;
}
