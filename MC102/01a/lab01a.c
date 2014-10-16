/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 01a - Calculo de media das notas de avaliacoes */

#include <stdio.h>
#include <math.h>

int main() {

    /* Declaracao de variaveis*/
    double P1, P2, P3, L, P;
   
    /* Entrada das notas */
    scanf("%lf %lf %lf %lf", &P1, &P2, &P3, &L);

    /* Media ponderada de P1, P2 e P3 */
    P = (3 * P1 + 3 * P2 + 4 * P3)/10;

    /* Saida de resultados */
    printf("Media aritmetica: %.1f\n", (P + L)/2);
    printf("Media harmonica: %.1f\n", (2 * P * L)/(P + L));
    printf("Media geometrica: %.1f\n", sqrt(P * L));

    return 0;
}
    