/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Email: laurocruzsouza@gmail.com
 * Laboratorio 14a - Gerenciador de mamoria */

#include <stdio.h>

void memory_manager(int *partitions);

int main() {
	/* Quantidade de partcoes de memoria */
	int partitions = 1;

	/* Gerenciador de memoria */
	memory_manager(&partitions);
	
	/* Todas as particoes foram usadas */
	if (partitions == 0) {
		printf("Alocacao total\n");
	/* Sobraram partcoes sem serem usadas */
	} else if (partitions > 0) {
		printf("Alocacao parcial\n");
	/* Foram usadas mais particoes do que foram criadas */
	} else {
		printf("Alocacao invalida\n");
	}
		
	return 0;
}

void memory_manager(int *partitions) {
	char c;
	
	scanf("%c", &c);
	
	/* Se # chega ao fim e sai da funcao */
	if (c == '#')
		return;
	
	/* Quando I, uma particao passa a ser utilizada, sem a criacao de outra */
	if (c == 'I')
		(*partitions)--;
	
	/* Quando D, criam-se tres particoes e uma e usada, assim aumenta em 1 o 
	 * numero de particoes existentes */
	if (c == 'D')
		(*partitions)++;
	
	memory_manager(partitions);
}
