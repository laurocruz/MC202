/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 04a - Deep Web */
#include <stdio.h>

int main() {

    /* Declaracao dos contadores do loops, o vetor senha e a soma das 
     * multiplicacoes feitas nos digitos anteriores para calcular o proximo 
digito */
    int senha[15], n, i, j, soma = 0, l;
    
    /*Leitura da quatidade inicial de digitos */
    scanf("%d", &n);
    
    /*Leitura dos n primeiros digitos da senha */
    for (i = 0; i < n; i++) {
        scanf(" %d", &senha[i]);
        soma += senha[i] * n * (i + 1);
    }
    
    /*Calculo dos digitos subsequentes */
    do {
        if (soma % 11 == 10) {
            senha[i] = 0;
        } else {
            senha[i] = soma % 11;
        }
        soma = 0;
        for (l = 0; l <= i; l++) {
            soma += senha[l] * (i + 1) * (l + 1);
        }
        i++;
    } while (i < 15);
    
    /* Imprimindo a senha gerada */
    for (j = 0; j < 15; j++) {
        printf("%d", senha[j]);
    }
        
    printf("\n");
    
    return 0;
}