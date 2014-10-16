/************************************
 * Nome: Lauro Cruz e Souza         *
 * RA: 156175                       *
 * Email: laurocruzsouza@gmail.com  *
 * Laboratorio 13a - Jmob           *
 ***********************************/

#include <stdio.h>

int peso(int *v);

int main() {	
	int Peso;
	/* Flag que determina se o mobile esta ou nao em equilibrio */
	int equilibrio = 1;
	
	/* Calcula o peso do mobile */
	Peso = peso(&equilibrio);
	
	if (equilibrio)
		printf("Mobile equilibrado\n");
	else
		printf("Mobile desequilibrado\n");
	
	printf("Peso total: %d\n", Peso);
	
	return 0;
}

/* Funcao que obtem o peso do mobile e determina se esta ou nao equilibrado */
int peso(int *v) {
	int De, Dd, Pe, Pd;
	
	scanf("%d %d %d %d", &Pe, &De, &Pd, &Dd);
	
	/* Calcula o peso do lado esquerdo caso haja barra */ 
	if (Pe == 0)
		Pe = peso(v);
	
	/* Calcula o peso do lado direito caso haja barra */
	if (Pd == 0)
		Pd = peso(v);
	
	/* Verifica se o mobile esta equilibrado */
	if ((Pe * De) != (Pd * Dd))
		*v = 0;
	
	/* Retorna o peso total do mobile */
	return Pe + Pd;
}