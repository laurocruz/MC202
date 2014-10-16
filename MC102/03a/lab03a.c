/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 03a - Composição de senha */
#include <stdio.h>

int main () {
   
    /* Declaracao das variaveis, uma que recebera a letra, uma que calcula a 
     * soma das notas e uma que conta a quantidade de letras por linha */
    char c;
    double soma;
    int letras;

    /* Conjunto de condicionais que farão a soma e imprimirão os caracteres da 
     * senha com base nos caracteres digitados e finalizarão o programo ao 
     * digitar o caractere '*' */
    do {
        soma = 0;
        letras = 0;
        do {
            scanf("%c", &c);
            if (c == '*') {
                break;
            } else if (c == 'A') {
                soma++;
                letras++;
            } else if (c == 'B') {
                soma = soma + 0.5;
                letras++;
            } else if (c == 'C') {
                soma = soma + 0.25;
                letras++;
            } else if (c == 'D') {
                soma = soma + 0.125;
                letras++;
            } else if (c == 'E') {
                soma = soma + 0.0625;
                letras++;
            } else if (c == 'F') {
                soma = soma + 0.03125;
                letras++;
            } else if (c == 'G') {
                soma = soma + 0.015625;
                letras++;
            } else if (c == 'H') {
                soma = soma + 0.0078125;
                letras++;
            }
     
        } while (c != '\n');
    
        if ((soma != 1) && (soma != 0)) {
            printf("%d", 0);
        } else if (soma == 1) {
            printf("%d", letras);
        }
    
    } while (c != '*');
    
    printf("\n");
    
    return 0;

}
        
        
                                        
        
        