/***************************************************************** 
 * Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laboratório 06 - Análise sintática e Árvores - analisador.c   *
 * Last modified: 19-10-14                                       *
 *****************************************************************/

/* 
 * analisador.c: Módulo de transformação de expressões em Árvores
 * binárias e seus percursos.
 */

#include "analisador.h"
#include <stdlib.h>
#include <ctype.h>
#include "balloc.h"

/* Variáveis globais a este módulo */

char ant; /* Armazena o caractere da entrada anterior ao que in está apontando */

char *in;  /* Cadeia e índice para expressão infixa (entrada). */
int indIn;

char *Gpos, *Gpre; /* Variáveis para armazenar a posição dos vetores pos e pre */

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

void pulaEspacoIn(); /* Pula os espaçoos em branco da infixa */
int eLetra(); /* Verifica se in[indIn] é uma letra */
int car_inv(); /* Verifica se o caractere é inválido */


/* Protótipos das funções mutuamente recursivas. */
/* O resultado é devolvido através da variável 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);

/* Função auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);


/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a notação infixa em Árvore binária.  Em caso de erro,
   devolve o código e a posição na cadeia de entrada onde o erro foi
   encontrado.  */
	Erro final;

	ant = ' '; /* Como não há anterior, inicia-se valendo ' ' */
	
	in = infixa;
	indIn = 0;
	
	if (in[0] == ' ') pulaEspacoIn();
	
	/* Não encontrando nenhum caractere na entrada, é uma cadeia de bracos */
	if (in[indIn] == '\0')
		return montaErro(CADEIA_DE_BRANCOS, 0);
	
	*arv = MALLOC(sizeof(NoArvBin));

	final = Expressao(arv);
	
	/* Se o vetor não estiver no final, faltou um operador */
	if ((in[indIn] != '\0') && (final.codigoErro == EXPR_VALIDA))
		return montaErro(OPERADOR_ESPERADO, indIn);
 
	return final; 

}

/*************************************************************/
/*           Funções de implementação do analisador          */
/*************************************************************/

void pulaEspacoIn() {
	/* Pula espaços em branco */
	if (in[indIn] != ' ') {
		ant = in[indIn];
		indIn++;
	}
	
	while (in[indIn] == ' ')
		indIn++;
}

int eLetra() {
	/* Verifica e o caractere é uma letra */
	return ((toupper(in[indIn]) >= 'A') && (toupper(in[indIn]) <= 'Z'));
}

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com código de erro e posição */
	Erro res;
	
	res.posicao = posicao;
	res.codigoErro = codigo;
  
	return res;

} /* montaErro */

int car_inv() {
	/* Verifica se o caractere é inválido */
	char c = in[indIn];
	
	return (c != '+' && c != '-' && c != '*' && c != '/' && 
			c != '^' && c != '\0'&& c != '(' && c != ')' && !eLetra());
}

Erro Expressao(ArvBin *arv) {
/* Processa uma expressão da cadeia de entrada.  */
	int count = 0;
	ArvBin exclude, aux;
	Erro erroE;

	(*arv)->esq = MALLOC(sizeof(NoArvBin));
	
	/* Inicia-se chamando o filho da esquerda do no apontado por *arv */
	erroE = Termo(&((*arv)->esq));

	if (erroE.codigoErro != EXPR_VALIDA)
		return erroE;

	if (in[indIn] == '+' || in[indIn] == '-') {
		while (in[indIn] == '+' || in[indIn] == '-') {
			/* Se a repetição ocorrer por mais de uma vez, será criado um nó superior, e o atual 
			 * nó apontado por *arv será seu filho esquerdo, e *arv apontará para o novo pai */
			if (count > 0) {
				aux = MALLOC(sizeof(NoArvBin));
				aux->esq = *arv;
				*arv = aux;
			}
			(*arv)->info = in[indIn];

			pulaEspacoIn();

			/* Agora chama-se o filho direito */
			(*arv)->dir = MALLOC(sizeof(NoArvBin));
			erroE = Termo(&((*arv)->dir));

			if (erroE.codigoErro != EXPR_VALIDA)
				return erroE;
			
			count++;
		}
	/* Se não houver operador + ou -, o nó é excluido */
	} else {
		exclude = *arv;
		*arv = (*arv)->esq;
		FREE(exclude);
	}
	
	return resCorreto;

} /* Expressao */


Erro Termo(ArvBin *arv) {
/* Processa um termo da cadeia de entrada.  */
	int count = 0;
	ArvBin exclude, aux;
	Erro erroT;
	
	(*arv)->esq = MALLOC(sizeof(NoArvBin));
	/* Inicia-se chamando o filho da esquerda do no apontado por *arv */
	erroT = Fator(&((*arv)->esq));
	
	if (erroT.codigoErro != EXPR_VALIDA)
		return erroT;
	
	if (in[indIn] == '*' || in[indIn] == '/') {
		while (in[indIn] == '*' || in[indIn] == '/') {
			/* Se a repetição ocorrer por mais de uma vez, será criado um nó superior, e o atual 
			 * nó apontado por *arv será seu filho esquerdo, e *arv apontará para o novo pai */
			if (count > 0) {
				aux = MALLOC(sizeof(NoArvBin));
				aux->esq = *arv;
				*arv = aux;
			}
			(*arv)->info = in[indIn];

			pulaEspacoIn();

			/* Agora chama-se o filho direito */
			(*arv)->dir = MALLOC(sizeof(NoArvBin));
			erroT = Fator(&((*arv)->dir));

			if (erroT.codigoErro != EXPR_VALIDA)
				return erroT;
			count++;
		}
	/* Se não houver operador * ou /, o nó é excluido */
	} else {
		exclude = *arv;
		*arv = (*arv)->esq;
		FREE(exclude);
	}
	
	return resCorreto;

} /* Termo */


Erro Fator(ArvBin *arv) {
/* Processa um fator da cadeia de entrada.  */
	ArvBin exclude;
	Erro erroF;
	
	(*arv)->esq = MALLOC(sizeof(NoArvBin));
	/* Inicia-se chamando o filho da esquerda do no apontado por *arv */
	erroF = Primario(&((*arv)->esq));
	
	if (erroF.codigoErro != EXPR_VALIDA)
		return erroF;
	
	/* Verifica se há caractere inválido que não foi pego em Primario() */
	if (car_inv())
		return montaErro(CARACTERE_INVALIDO, indIn);
		
	if (in[indIn] == '^') {
		(*arv)->info = '^';
		
		pulaEspacoIn();
		
		/* Agora chama-se o filho direito */
		(*arv)->dir = MALLOC(sizeof(NoArvBin));
		erroF = Fator(&((*arv)->dir));
		
		if (erroF.codigoErro != EXPR_VALIDA)
			return erroF;
		
	/* Se não houver operador ^, o nó é excluido */
	} else {
		exclude = *arv;
		*arv = (*arv)->esq;
		FREE(exclude);
	}
  
	return resCorreto;
} /* Fator */


Erro Primario(ArvBin *arv) {
/* Processa um  primário da cadeia de entrada.  */
	Erro erroP;
	char unr, let;
	
	if (in[indIn] == ' ') pulaEspacoIn();

	/* Encontra um operando */
	if (eLetra()) {
		/* Armazena o valor do operando para poder se locomover no vetor */
		let = in[indIn];
		pulaEspacoIn();
		
		/* Verifica se há dois operandos um ao lado do outro */
		if (eLetra())
			return montaErro(OPERADOR_ESPERADO, indIn);
			
		/* Um operando é alocado em uma folha */
		(*arv)->esq = (*arv)->dir = NULL;
		(*arv)->info = let; 
		
	/* Encontra um abre parênteses */
	} else if (in[indIn] == '(') {
		pulaEspacoIn();
		/* Verifica se não há operando ou operador após abrir o parêntese */
		if (in[indIn] == '\0' || in[indIn] == ')') /* Se não houver, falta operando */
			return montaErro(OPERANDO_ESPERADO, indIn);
		
		/* Dentro dos parênteses deve haver uma expressão "separada" do resto, já que ela tem
		 * prioridade */
		erroP = Expressao(arv);

		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
		
		/* Verifica de faltou o fecha parêntese */
		if (in[indIn] != ')')
			return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
		
		pulaEspacoIn();
		
	/* Verifica se é operador unário */
	} else if ((in[indIn] == '+' || in[indIn] == '-') && (ant == ' ' || ant == '(')) {
		if (in[indIn] == '+') unr = '&';
		else unr = '~';
		
		pulaEspacoIn();
		/* Verifica se o operador realmente é unário ou se é binário, mas falta um operando */
		if (!eLetra() && in[indIn] != '(')
			return montaErro(OPERANDO_ESPERADO, indIn);
		
		/* O termo do operador unário é alocado no nó direito */
		(*arv)->esq = NULL;
		(*arv)->info = unr;
		
		(*arv)->dir = MALLOC(sizeof(NoArvBin));
		
		/* Verifica o termo do operador unário */
		erroP = Termo(&((*arv)->dir));
		
		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
	
	/* Se um desses caracteres forem encontrados, a entrada está incorreta pois espera um operando*/
	} else if (in[indIn] == '+' || in[indIn] == '-' || in[indIn] == '*' || 
			   in[indIn] == '/' || in[indIn] == '^' || in[indIn] == ')' || 
			   in[indIn] == '\0') {
		return montaErro(OPERANDO_ESPERADO, indIn);
		
	/* Se não entrar em nenhum dos casos acima, o caractere é inválido */
	} else return montaErro(CARACTERE_INVALIDO, indIn);
	
	return resCorreto;

} /* Primario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representação pré-fixa a partir da Árvore. */
	Gpre = pre;
	
	while (arv != NULL) {
		*Gpre = arv->info; /* Visita a raiz da subárvore */
		Gpre++;
		ArvPre(arv->esq, Gpre); /* Chama a subárvore esquerda */
		arv = arv->dir; /* Chama a subárvore direita */
	}
	*Gpre = '\0';
}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representação pós-fixa a partir da Árvore. */  
	Gpos = pos;

	if (arv != NULL) {
		ArvPos(arv->esq, Gpos); /* Chama a subárvore esquerda */
		ArvPos(arv->dir, Gpos); /* Chama a subárvore direita */
		*Gpos = arv->info; /* Visita a raiz da subárvore */
		Gpos++;
	}
	*Gpos = '\0';
}


void LiberaArv(ArvBin arv) {
/* Libera o espaço ocupado pela Árvore. */
	if (arv != NULL) {
		LiberaArv(arv->esq);
		LiberaArv(arv->dir);
		FREE(arv);
	}
}

