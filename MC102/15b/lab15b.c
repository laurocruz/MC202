/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Email: laurocruzsouza@gmail.com
 * Laboratorio 10b - DON'T PANIC - Part II */

#include <stdio.h>

/* Numero maximo de panquecas */
#define MAX_PAN 13

/* Funcao que copia um vetor de inteiros no outro */
void copy_vet(int vet1[], int vet2[], int tam);
/* Funcao que encontra a permutacao com o menor peso */
void pancake_sort_min(int pancakes[], int Wsup, int Wint, int *weight,int npan);
/* Funcao que encontra o limitante inferior */
int search_inferior(int pancakes[], int npan);
/* Funcao que encontra o limitante inferior (funcao do lab10b) */
int pancake_sort_superior(int pancakes[], int *i, int *j, int *weight,int npan);
/* Funcao que encontra os valores de i e j para a funcao acima */
int find_i_j(int pancakes[], int *i, int *j, int *weight, int npan);
/* Funcao que faz a permutacao de prefixos */
void permute(int pancakes[], int i , int j);

int main() {
	int pancakes[MAX_PAN+2], supPancakes[MAX_PAN+2];
	int npan, minWeight = 0;
	int Winf, Wsup = 0;
	int i, j, l;
	
	/* Le o numero de panquecas */
	scanf("%d", &npan); 
	
	/* Atribuindo as posicoes iniciais e finais dos vetores de panquecas */
	supPancakes[0] = 0;
	pancakes[0] = 0;
	supPancakes[npan+1] = npan + 1;
	pancakes[npan+1] = npan + 1;
	
	/* Lendo a ordenacao das panquecas */
	for (l = 1; l <= npan; l++) {        
		scanf("%d", &pancakes[l]);
		supPancakes[l] = pancakes[l];
	}
	
	/* Encontra o limitante inferior */
	Winf = search_inferior(pancakes, npan);
	
	/* Se o limitante inferior for diferente de zero, procura-se a permutacao 
	 * de menor peso */
	if (Winf) {
	
		/* Enquanto a funcao retornar um valor diferente de 1, ou seja, enquanto 
		 * a ordenacao ainda nao estiver completamente feita, o loop se 
		 * repetira */
		while (pancake_sort_superior(supPancakes, &i, &j, &Wsup, npan));

		/* O maior peso aceitavel e o peso do limitante superior */
		minWeight = Wsup;
		/* Encontra a permutacao de menor peso */
		pancake_sort_min(pancakes, Wsup, 0, &minWeight, npan);
		
	/* Se o limitante inferior for igual a zero, as panquecas ja estao 
	 * ordenadas, assim o limitante superior e o peso minimo são iguais a zero*/
	} else {
		Wsup = 0;
		minWeight = 0;
	}
	
	printf("Limitante inferior: %d\n", Winf);
	printf("Peso: %d\n", minWeight);
	printf("Limitante superior: %d\n", Wsup);
	
	return 0;
}

/* Copia um vetor no outro */
void copy_vet(int vet1[], int vet2[], int tam) {
	int i;
	
	for (i = 0; i < tam; i++) {
		vet2[i] = vet1[i];
	}
}

/* Encontra a permutacao de menor peso */
void pancake_sort_min(int pancakes[], int Wsup, int Wint, int *weight,int npan){
	int i, j, aux[MAX_PAN + 2];
	
	/* Se a funcao retornar zero, significa que as panquecas estao ordenadas */
	if (search_inferior(pancakes, npan) == 0) {
		/* Se o peso levado para ordenar essas panquecas for menor que o menor 
		 * peso achado ate o momento, ele e atualizado */
		if (Wint < (*weight));
			(*weight) = Wint;
	/* Se as panquecas ainda nao estiverem organizadas é feito uma iteracao que 
	 * percorrera todas as permutacoes possiveis de serem feitas no vetor de 
	 * panquecas */
	} else {
		for (i = 2; i <= npan; i++) {
			for (j = i + 1; j <= npan+1; j++) {
				/* Caso o peso para fazer a permutacao ate esse momento seja 
				 * menor que o menor peso achado ate o momento, pode-se 
				 * continuar com aquela permutacao, se nao e abortada
				 * (backtracking) */
				if (Wint + j - 1 < (*weight)) {
					/* Vetor aux sendo tornado uma copia do vetor pancakes, ja
					 * que cada permutacao tem que ser feita no mesmo vetor */
					copy_vet(pancakes, aux, MAX_PAN + 2);
					/* Permutacao */
					permute(aux, i, j);
					/* Funcao recursiva e chamada para promover todas as outras
					 * permutacoes possiveis para essa nova ordem de panquecas*/
					pancake_sort_min(aux, Wsup, Wint+j-1, weight, npan);
					
				}
			}
		}
	}
}

/* Procura o limitante inferior */
int search_inferior(int pancakes[], int npan) {
	int i, inf = 0;
	
	for (i = 1; i <= npan; i++) {
		if ((pancakes[i] != i) && (pancakes[i] > inf))
			inf = pancakes[i];
	}
	
	return inf;
}

/* Funcao que realiza o pancake sort do laboratorio 10b, o qual sera usado para
 * determinar o limitante superior do peso da ordenacao das panquecas */
int pancake_sort_superior(int pancakes[], int *i, int *j, int *weight,int npan){
	int flag;
	/* Procura o i e j da permutacao e retorna 0 se estiver ordenado */
	flag = find_i_j(pancakes, i, j, weight, npan);
	/* Se as panquecas ja estiverem ordenadas, retorna 0 */
	if (flag == 0)
		return 0;
	
	/* Faz a permutacao tendo os valor de i e j */
	permute(pancakes, *i, *j);
	
	return 1;
}

/* Acha i e j da funcao de determinacao do limitante superior */
int find_i_j(int pancakes[], int *i, int *j, int *weight, int npan) {
	int it;
	
	/* Procura o i fazendo uma procura de strip no inicio */
	(*i) = 2;
	while ((pancakes[*i-1] == pancakes[*i]-1) && (*i != npan+1)) {
		(*i)++;
	}
	
	/* Retorna 0 se a strip for o vetor inteiro (panquecas ordenadas) */
	if (*i == npan+1)
		return 0;
	
	/* Procura o j para o qual havera a destruicao de um breakpoint ao se fazer 
	 * permutacao com o prefixo determinado pelo i anterior */
	(*j) = (*i) + 1;
	while ((pancakes[1] - pancakes[(*j)-1] != 1) && 
		(pancakes[(*j)] - pancakes[(*i)-1] != 1)) {
		(*j)++;
		}
		
		/* Sabendo o J (e consequentemente o peso), procura por uma strip na 
		 * qual a permutacao destruira dois breakpoints */
		if (pancakes[1] - pancakes[(*j)-1] == 1) {
			for (it = 2; it < (*j); it++) {
				if (pancakes[(*j)] - pancakes[it-1] == 1) {
					/* Se achar, altera o valor de i */
					(*i) = it;
					/* Atribui o valor do peso */
					(*weight) += (*j) - 1;
					/* E retorn 1, saindo da funcao */
					return 1;
				}
			}
		}
		/* Caso não ache o i referido acima, atribui o valor do peso e sai da
		 * funcao normalmente */
		(*weight) += (*j) - 1;
		
		return 1;
}

/* Funcao responsavel por permutar os dois prefixos determinados pelos indices
 * i e j */
void permute(int pancakes[], int i , int j) {
	int auxi[MAX_PAN-1], auxj[MAX_PAN-1];
	int k, m, n, p = 0, l;
	
	for (m = 1; m < i; m++) {
		auxi[m-1] = pancakes[m];
	}
	for (n = i; n < j; n++) {
		auxj[n-i] = pancakes[n];
	}
	
	for (k = 0; k < n-i; k++) {
		pancakes[k+1] = auxj[k];
	}
	
	for (l = k+1; l < j; l++) {
		pancakes[l] = auxi[p++];
	}
}
