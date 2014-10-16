/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 05a - Caça ao tesouro */

#include <stdio.h>

int main() {
    /* Declaracao do vetor trilha, flag para determinar se há ou não tesouro e 
     * marcador de iteracao e contador */
    int trilha[100], n, flag = 1, i = 0, contador = 0;
    
    /* Leitura do numero de passos da trilha */
    scanf("%d", &n);

    /* Leitura das dicas presentes em cada parte da trilha */
    for (i = 0; i < n; i++) {
        scanf(" %d", &trilha[i]);
    }
   
    i = 0;
    
    /* Loop que lera as pistas */
    while ((flag != 0) && (contador <= n)) {
        /* Condicional que se determiar que pista aponta para o local onde 
         * esta, o tesouro foi encontrado */
        if (trilha[i] == i + 1) {
            flag = 0;
            printf("Tesouro existe em %d\n", i+1);
        } else {
            i = trilha[i]-1;
            contador++;
        }
    }
    
    /* Condicional que ira determinar, a partir do contador, se nao ha tesouro*/
    if (contador > n) {
        printf("Nao existe tesouro\n");
    }
    return 0;
}