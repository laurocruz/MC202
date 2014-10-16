/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 11b - BibTeX */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Registro que ira armazenar as informacoes da bibliografia */
struct bibliography {
	/* Nome do(a)(s) autor(es)(as) */
    char author[501];
	/* Titulo da referencia */
    char title[501];
	/* Periodico ou livro na qual foi publicada */
    char journal[101];
	/* Paginas do trecho, ano da publicacao, volume do livro e numero */
    char pages[51], year[51], volume[51], number[51];
	/* Ordem numerica na qual a bibliografia foi dada */
	int given;
};

typedef struct bibliography bib;

void cases (char type, bib bibp[], char bibtex[], int j, int l);

void flags_yvnp(bib *bibp, int l);

void reading_bibs(bib *bibp, int articles);

int find_min(int articles, int i, bib *bibp);

void change_bib(bib *a, bib *b);

void sorting_bibs(bib *bibp, int articles);

void print_bibs(bib *bibp, int articles);

int main() {
	int articles;
	char trash;
	bib *bibp;
	
	/* Le o caractere '%' do comentario e o descarta */
	scanf("%c", &trash);
	/* Leitura da quantidade de artigos sendo referenciados */
	scanf("%d\n", &articles);
	/* Alocacao dos registros para as bibliografias dos artigos */
	bibp = malloc(articles * sizeof(bib));
	
	/* Lendo as bibliografias */
	reading_bibs(bibp, articles);
	/* Fazenda a ordenacao as bibliografias por ordem alfabetica dos titulos */
	sorting_bibs(bibp, articles);
	/* Imprimindo as bibliografias no formato padrao */
	print_bibs(bibp, articles);
	/* Liberando a memoria alocada para o vetor de registro bibp */
	free(bibp);
	
	return 0;
}

/* Funcao resonsavel por fazer a leitura das informacoes de cada bibliografia
 * e aloca-la em suas respectivas categorias (ex: autor, titulo, ano, paginas,
 * etc) */
void cases (char type, bib bibp[], char bibtex[], int j, int l) {
	int k = 0;
	
	/* Cada tipo e determinado pela primeira letra de palavra que determina sua
	 * cateoria, o que é possivel ja que todas tem a primeira letra de suas 
	 * palavras diferentes. Ex: a - author, t - title, j - journal... */
	
	/* Em cada um dos casos havera uma alocacao de caracteres ate o caractere 
	 * '}'ser atingido, o que significa que a informacao chegou ao fim, sendo 
	 * atribuido um '\0' ao final para ser criada uma string */
	switch (type) {
		case 'a':
			while (bibtex[j] != '}') {
				bibp[l].author[k] = bibtex[j];
				j++;
				k++;
			}
			bibp[l].author[k] = '\0';
			break;
			
		case 't':
			while (bibtex[j] != '}') {
				bibp[l].title[k] = bibtex[j];
				j++;
				k++;
			}
			bibp[l].title[k] = '\0';
			break;
			
		case 'j':
			while (bibtex[j] != '}') {
				bibp[l].journal[k] = bibtex[j];
				j++;
				k++;
			}
			bibp[l].journal[k] = '\0';
			break;
			
		case 'p':
			while (bibtex[j] != '}') {
				bibp[l].pages[k] = bibtex[j];
				j++;
				k++;
			}
			bibp[l].pages[k] = '\0';
			break;
			
		case 'y':
			while (bibtex[j] != '}') {
				bibp[l].year[k] = bibtex[j];
				j++;
				k++;
			}
			bibp[l].year[k] = '\0';
			break;
			
		case 'v':
			while (bibtex[j] != '}') {
				bibp[l].volume[k] = bibtex[j];
				j++;
				k++;
			}
			bibp[l].volume[k] = '\0';
			break;
			
		case 'n':
			while (bibtex[j] != '}') {
				bibp[l].number[k] = bibtex[j];
				j++;
				k++;
			}
			bibp[l].number[k] = '\0';
			break;
	}
}

/* Funcao que permitira determinar se deve-se imprimir o numero, ano, volume e
 * paginas, que nem sempre são dadas */
void flags_yvnp(bib *bibp, int l) {
	/* Atribui tambem a ordem na qual as bibliografias foram dadas */
	bibp[l].given = l+1;
	
	bibp[l].year[0] = 'x';
	bibp[l].volume[0] = 'x';
	bibp[l].number[0] = 'x';
	bibp[l].pages[0] = 'x';
}

/* Funcao que le as bibliografias e atribui suas informacoes as registros de
 * informacao de cada uma */
void reading_bibs(bib *bibp, int articles) {
	int l, in, i, j;
	char type, trashv[3];
	char bibtex[516];

	for (l = 0; l < articles; l++) {
		in = 1;
		/* Lendo as linhas em branco (apenas com quebra de linha \n) */
		fgets(trashv, 3, stdin);
		/* Atribuindo as flags no registro */
		flags_yvnp(bibp, l);
		
		for (i = 0; (i 	< 9) && (in); i++) {
			/* Le cada linha do bibtex */
			fgets(bibtex, 516, stdin);
			/* Se o primeiro caracere lido for '}', siginifica que esse bloco de
			 * bibliografia chegou ao fim e ira passar-se para o proximo */
			if (bibtex[0] == '}') {
				in = 0;
			}
			
			
			if ((i > 0) && (in)) {
				/* Obtendo a categoria a qual a informacao sera atribuida */
				type = bibtex[1];
				/*Menor posicao possivel da qual a informacao pode se iniciar */
				j = 8; 
				/* Chegando-se a posicao a partir da qual esta a informacao */
				while (bibtex[j] != '{')
					j++;
				j++;
				/* Fazendo a atribuicao das informacoes */
				cases(type, bibp, bibtex, j, l);
			}
		}
	}
}

/* Funcao que acha a bibliografia com o menor titulo lexicograficamente */
int find_min(int articles, int i, bib *bibp) {
	int j, min = i;
	
	for (j = i+1; j < articles; j++) {
		/* Se bibp[j].title for menor que bibp[min].title */
		if (strcmp(bibp[j].title, bibp[min].title) < 0) {
			min = j;
		/* Caso os titulos sejam iguais... */
		} else if (strcmp(bibp[j].title, bibp[min].title) == 0) {
			/* Sera escolhido o que foi dado primeiro */
			if (bibp[j].given < bibp[min].given) {
				min = j;
			}
		}
	}
	
	return min;
}

/* Troca dois registros */
void change_bib(bib *a, bib *b) {
	bib aux;
	
	aux = *a;
	*a = *b;
	*b = aux;
}

/* SELECTION SORT das bibliografias com base na ordem alfabetica dos titulos de
 * cada um */
void sorting_bibs(bib *bibp, int articles) {
	int i, min;
	
	for (i = 0; i < articles-1; i++) {
		min = find_min(articles, i, bibp);
		change_bib(&bibp[i], &bibp[min]);
	}
}

/* Funcao que imprime as bibliografias no formato definido */
void print_bibs(bib *bibp, int articles) {
	int i;
	
	for (i = 0; i < articles; i++) {
		printf("%s", bibp[i].title);
		printf(", %s", bibp[i].author);
		printf(", %s", bibp[i].journal);
		
		/* Caso um desses nao tenham a primeira posicao igual a 'x', significa 
		 * que um valor foi atribuido a eles, ou seja, deve ser imprimido */
		if (bibp[i].volume[0] != 'x')
			printf(", %s", bibp[i].volume);
		if (bibp[i].number[0] != 'x')
			printf(", %s", bibp[i].number);
		if (bibp[i].pages[0] != 'x')
			printf(", %s", bibp[i].pages);
		if (bibp[i].year[0] != 'x')
			printf(", %s", bibp[i].year);
		
		printf(".\n\n");
	}
}