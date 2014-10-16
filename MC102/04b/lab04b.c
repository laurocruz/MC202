/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 04b - Semanada */

#include <stdio.h>

int main() {
    /* Declaracao dos vetores que armazenarao o numero enviado pelo pai e o maior
     * numero resultante da retirada da quantidade de numeros determinada pelo
     * pai */
    int numero[100], maior[100];
    /* Declaracao das variaveis que representarao a quantidade de numeros
     * enviados pelo pai, quantos numeros devem ser tirados e quantos foram
     * retirados (contador) */
    int qtde, tirar, retirados = 0;
    /* Declarao de variaveis contadoras de iteracoes, temporarias e condicionais
     */
    int tentativa, temp, i, j, k;

    /* Zerando os dois vetores (nao é necessário, apenas gosto pessoal) */
    for (i = 0; i < 100; i++) {
        numero[i] = 0;
        maior[i] = 0;
    }
    
    /* Lendo a quantidade de numeros enviados pelo pai e quantos devem ser
     * retirados */
    scanf("%d %d", &qtde, &tirar);

    /* Lendo os numeros enviados pelo pai */
    for (i = 0; i < qtde; i++) {
        scanf(" %d", &numero[i]);
    }
    
    /* Zerando as contadoras de iteracoes */
    k = 0;
    i = 0;
    j = i + 1;
    
    /* Repetição até serem retirados a quantidade de algarismos necessária */
    while ((retirados < tirar) && (j < qtde)) {
        temp = i;
        tentativa = 1;
        /* Comparacao de um numero na posicao i do vertor numero com o da
         * posicao j no mesmo vetor, adicionando ao vetor maior quem for o maior
         * da sequencia analisada, sendo essa igual a posicao i do primeiro a ser
         * analisado mais a quantidade de numeros a serem retirados menos a
         * quantidade ja retirada */
        while ((j <= i + tirar - retirados) && (j < qtde)) {
            if (numero[j] > numero[temp]) {
                maior[k] = numero[j];
                temp = j;
                j++;
                tentativa = 0;
            } else if ((j == i + tirar - retirados) && (tentativa != 0)) {
                maior[k] = numero[i];
                j++;
            } else {
                j++;
            }
        }
        retirados = temp - k;
        i = temp + 1;
        j = i + 1;
        k++;
    }
    
    /* Imprimindo os últimos algarismos do numero que não chegaram a ser lidos
     * devido a retirada da quantidade de números necessária antes de serem
     * atingidos */
    while (k < qtde - tirar) {
        maior[k] = numero[i];
        k++;
        i++;
    }

    printf("Maior valor: ");

    /* Imprimindo os valores do vetor maior um por um */
    for (k = 0; k < (qtde - tirar); k++) {
        printf("%d", maior[k]);
    }

    printf("\n");

    return 0;
}
