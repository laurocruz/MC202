/* Nome: Lauro Cruz e Souza 
 * RA: 156175
 * Laboratorio 05b - Killing the messenger */

#include <stdio.h>

int main() {
    /* Declaracao dos vetores RNA mensageiro e do oligonucleotideo */
    char mRNA[101], olig[26];
    /* Declaracao da quantidade de bases nitrogenadas no mRNA e oligonucleotideo, dois
     * marcadores de iteracao, um flag para determinar se o gene e silenciado, um
     * contador do oligonucleotideo, uma variavel temporaria para 'i' e uma variavel para
     * determinar a partir que que posicao o mRNA foi silenciado */
    int R, O, i = 0, j = 0, flag = 1, vez, temp, sil;
    /* Leitura da quantidade de bases nitrogenadas do mRNA e do oligonucleotideo */
    scanf("%d %d", &R, &O);
    /* Leitura da cadeia de bases nitrogenadas do mRNA */
    scanf("%s", mRNA);
    /* Leitura da cadeia de bases nitrogenadas do oligonucleotideo */
    scanf("%s", olig);
    /* Loop para percorrer as bases do mRNA */
    while ((mRNA[i] != '\0') && (flag != 0)) {
        vez = 0;
        j = O - 1;
        temp = i;
        /* Loop para comparar as bases do oligonucleotideo com o mRNA */
        while ((j < O) && (j >= 0) && (flag != 0)) {
            /* Condicional que determina se há ligação entre a base do mRNA e do
             * oligonucleotideo */
            if (((mRNA[temp] == 'U') && (olig[j] == 'A')) || ((mRNA[temp] == 'A') &&
(olig[j] == 'U')) || ((mRNA[temp] == 'C') && (olig[j] == 'G')) || ((mRNA[temp]
== 'G') && (olig[j] == 'C'))) {
                /* Conta a posição do oligonucleotideo */
                vez++;
                /* Se for o primeiro, então a posicao atual do mRNA e de onde se inicia
                 * do silenciamento, caso ele seja concretizado */
                if (vez == 1) {
                    sil = i + 1;
                }
                temp++;
                /* Se essa condicao for verdadeira, houve o silenciamento */
                if ((j == 0) && (vez == O)) {
                    flag = 0;
                }
            }
            j--;
        }
        i++;
    }

    /* Imprime o resultado */
    if (flag != 0) {
        printf("Nao silenciado\n");
    } else {
        printf("Silenciado em %d\n", sil);
    }
        
    return 0;
}
