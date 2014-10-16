/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Email: laurocruzsouza@gmail.com
 * Laboratorio 15a - Transferência de Bitcoins */

#include <stdio.h>
#include <math.h>

/* Quantidade de numeros do codigo de verificacao */
#define MAX_NUM 9
/* O maximo de operacoes que poder ser realizadas entre os numeros do codigo */
#define MAX_OP 8

/* Le o codigo de verificacao */
void read_numbers(int vet[]);
/* Funcao para realizar as operacoes nos numeros */
void operations(int op[], int numbers[], int key, int *out);
/* Funcao para fazer o arranjo de operacoes possiveis e calcular cada uma */
void arrange(int op[], int numbers[], int size, int key, int *out);

int main() {
	int key, out = 0;
	int numbers[MAX_NUM], op[MAX_OP];
	
	/* Lendo o codigo de verificacao */
	read_numbers(numbers);
	
	/* Lendo o numero de seguranca */
	scanf("%d", &key);
	
	/* Fazendo a verificacao */
	arrange(op, numbers, 0, key, &out);
	
	if (out)
		printf("Transferencia aceita\n");
	else
		printf("Transferencia abortada\n");
	
	return 0;
}

/* Funcao que le cada numero algarismo do codigo separadamente e os atribui a 
 um vetor de inteiros */
void read_numbers(int vet[]) {
	int i;
	char c;
	
	for (i = 0; i < MAX_NUM; i++) {
		scanf("%c", &c);
		
		vet[i] = c - '0';
	}
}

/* Funcao que realiza a operacoes nos numeros e verifica se a soma é 
 * equivalente ao numero de seguranca */
void operations(int op[], int numbers[], int key, int *out) {
	int aux, countZ = 0, j, sum = 0;
	
	/* A variavel aux sera utilizada para formar os numeros que serao 
	 * somados ou subtraidos a variavel sum, que armazenara o valor final
	 * das operacoes */
	
	/* Inicialmente aux comeca com o valor do ultimo algarismo, ja que as
	 * operacoes sera contabilizadas de tras para frente */
	aux = numbers[MAX_NUM-1];
	for (j = MAX_OP - 1; j >= 0; j--) {
		/* Se op[j] for 1 ou -1 significa que ocorre uma subtracao ou 
		 * adicao, de modo que a variavel sum e atualizada, adicionando ou
		 * subtraindo o valor de aux */
		
		/* Aux e nesse momento atualizada com o valor do proximo algarismo, 
		 * iniciando-se o processo novamente */
		if ((op[j] == -1) || (op[j] == 1)){
			sum += op[j] * aux;
			countZ = 0;
			aux = numbers[j];
			
			/* Caso encontre-se um 0, entao os dois numeros dever se juntar */
		} else {
			/* essa variavel conta a quantidade de 0's consecutivos no 
			 * vetor op de tras pra frente, para poder fazer a juncao dos
			 * algarismos, multiplicando-os por multiplos de 10^countZ, que
			 * determina assim sua casa decimal */
			countZ++;
			aux += numbers[j] * pow(10.0, countZ);
		}
	}
	
	/* O primeiro numero sempre vai ser positivo */
	sum += aux;
	
	/* Verificacao se a soma dos numeros e igual ao numero de seguranca */
	if (sum == key)
		(*out) = 1;
	/* Se a soma em algum momento for igual ao num de seguranca, isso 
	 * sifnifica que a operacao pode ser realizada */
}

void arrange(int op[], int numbers[], int size, int key, int *out) { 
	int i;
	
	/* Caso base: O vetor de operacoes ja foi todo completado */
	if (size == MAX_OP) {
		operations(op, numbers, key, out);
		
	} else {
		/* 1 representa soma
		 * -1 representa subtracao
		 * 0 significa que nao ha operacao, ou seja, juncao de dois algarismos*/
		
		for (i = 1; (i >= -1) && ((*out) == 0); i--) {
			op[size] = i;
			arrange(op, numbers, size + 1, key, out);
		}
	}
}