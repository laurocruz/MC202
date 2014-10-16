/***************************************************************** 
 * Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laborat�rio 06 - An�lise sint�tica e �rvores - analisador.c   *
 * Last modified: *
 *****************************************************************/

/* 
 * analisador.c: M�dulo de transforma��o de express�es em �rvores
 * bin�rias e seus percursos.
 */

#include <stdio.h>
#include "analisador.h"
#include <stdlib.h>
#include <ctype.h>
#include "balloc.h"

/* Vari�veis globais a este m�dulo */

char ant; /* Armazena o caractere da entrada anterior ao que in est� apontando */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

void pulaEspacoIn(); /* Pula os espa�oos em branco da infixa */
int eLetra(); /* Verifica se in[indIn] � uma letra */
int car_inv(); /* Verifica se o caractere � inv�lido */


/* Prot�tipos das fun��es mutuamente recursivas. */
/* O resultado � devolvido atrav�s da vari�vel 'arv'. */
Erro Expressao(ArvBin *arv);
Erro Termo(ArvBin *arv);
Erro Fator(ArvBin *arv);
Erro Primario(ArvBin *arv);

/* Fun��o auxiliar -- declarada mais adiante */
Erro montaErro(int codigo, int pos);


/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InArv(char *infixa, ArvBin *arv) {
/* Transforma a nota��o infixa em �rvore bin�ria.  Em caso de erro,
   devolve o c�digo e a posi��o na cadeia de entrada onde o erro foi
   encontrado.  */
	Erro final;

	ant = ' '; /* COmo n�o h� anterior, inicia-se valendo ' ' */
	
	in = infixa;
	indIn = 0;
	
	if (in[0] == ' ') pulaEspacoIn();
	
	/* N�o encontrando nenhum caractere na entrada, � uma cadeia de bracos */
	if (in[indIn] == '\0')
		return montaErro(CADEIA_DE_BRANCOS, 0);

	final = Expressao(arv);
	
	if ((in[indIn] != '\0') && (final.codigoErro == EXPR_VALIDA))
		return montaErro(OPERADOR_ESPERADO, indIn);
 
	return final; 

}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

void pulaEspacoIn() {
	if (in[indIn] != ' ') {
		ant = in[indIn];
		indIn++;
	}
	
	while (in[indIn] == ' ')
		indIn++;
}

int eLetra() {
	return ((toupper(in[indIn]) >= 'A') && (toupper(in[indIn]) <= 'Z'));
}

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com c�digo de erro e posi��o */
	Erro res;
	
	res.posicao = posicao;
	res.codigoErro = codigo;
  
	return res;

} /* montaErro */

int car_inv() {
	char c = in[indIn];
	
	return (c != '+' && c != '-' && c != '*' && c != '/' && 
			c != '^' && c != '\0'&& c != '(' && c != ')' && !eLetra());
}

Erro Expressao(ArvBin *arv) {
/* Processa uma express�o da cadeia de entrada.  */
	ArvBin exclude;
	Erro erroE;

	printf("EXPRESS�O\n\n");
	(*arv)->esq = MALLOC(sizeof(NoArvBin));
	printf("ALOCOU (ACHO)\n\n");
	erroE = Termo(&((*arv)->esq));

	if (erroE.codigoErro != EXPR_VALIDA)
		return erroE;

	if (in[indIn] == '+' || in[indIn] == '-') {
		while (in[indIn] == '+' || in[indIn] == '-') {
			(*arv)->info = in[indIn];

			pulaEspacoIn();

			(*arv)->dir = MALLOC(sizeof(NoArvBin));
			erroE = Termo(&((*arv)->dir));

			if (erroE.codigoErro != EXPR_VALIDA)
				return erroE;
		}
	} else {
		exclude = *arv;
		arv = &((*arv)->esq);
		FREE(exclude);
	}
	
	return resCorreto;

} /* Expressao */


Erro Termo(ArvBin *arv) {
/* Processa um termo da cadeia de entrada.  */
	ArvBin exclude;
	Erro erroT;
	
	printf("TERMO\n\n");
	(*arv)->esq = MALLOC(sizeof(NoArvBin));
	
	erroT = Fator(&((*arv)->esq));
	
	if (erroT.codigoErro != EXPR_VALIDA)
		return erroT;
	
	if (in[indIn] == '*' || in[indIn] == '/') {
		while (in[indIn] == '*' || in[indIn] == '/') {
			(*arv)->info = in[indIn];

			pulaEspacoIn();

			(*arv)->dir = MALLOC(sizeof(NoArvBin));
			erroT = Fator(&((*arv)->dir));

			if (erroT.codigoErro != EXPR_VALIDA)
				return erroT;
				
		}
	} else {
		exclude = *arv;
		arv = &((*arv)->esq);
		FREE(exclude);
	}
	
	return resCorreto;

} /* Termo */


Erro Fator(ArvBin *arv) {
/* Processa um fator da cadeia de entrada.  */
	ArvBin exclude;
	Erro erroF;
	
	printf("FATOR\n\n");
	(*arv)->esq = MALLOC(sizeof(NoArvBin));
	
	erroF = Primario(&((*arv)->esq));
	
	if (erroF.codigoErro != EXPR_VALIDA)
		return erroF;
	
	/* Verifica se h� caractere inv�lido que n�o foi pego em Primario() */
	if (car_inv())
		return montaErro(CARACTERE_INVALIDO, indIn);
		
	if (in[indIn] == '^') {
		(*arv)->info = '^';
		
		pulaEspacoIn();
		
		(*arv)->dir = MALLOC(sizeof(NoArvBin));
		erroF = Fator(&((*arv)->dir));
		
		if (erroF.codigoErro != EXPR_VALIDA)
			return erroF;
		
	} else {
		exclude = *arv;
		arv = &((*arv)->esq);
		FREE(exclude);
	}
  
	return resCorreto;
} /* Fator */


Erro Primario(ArvBin *arv) {
/* Processa um  prim�rio da cadeia de entrada.  */
	Erro erroP;
	char unr, let;
	
	if (in[indIn] == ' ') pulaEspacoIn();

	printf("PRIMARIO: ");
	if (eLetra()) {
		printf("LETRA\n\n");
		let = in[indIn];
		pulaEspacoIn();
		
		/* Verifica se h� dois operandos um ao lado do outro */
		if (eLetra())
			return montaErro(OPERADOR_ESPERADO, indIn);
			
		(*arv)->esq = (*arv)->dir = NULL;
		(*arv)->info = let; 
		
	} else if (in[indIn] == '(') {
		printf("PAR�NTESE\n\n");
		pulaEspacoIn();
		/* Verifica se n�o h� operando ou operador ap�s abrir o par�ntese */
		if (in[indIn] == '\0' || in[indIn] == ')')
			return montaErro(OPERANDO_ESPERADO, indIn);
		
		erroP = Expressao(arv);

		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
		
		/* Verifica de faltou o fecha par�ntese */
		if (in[indIn] != ')')
			return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
		
		pulaEspacoIn();
		
	/* Verifica se � operador un�rio */
	} else if ((in[indIn] == '+' || in[indIn] == '-') && (ant == ' ' || ant == '(')) {
		printf("UN�RIO\n\n");
		if (in[indIn] == '+') unr = '&';
		else unr = '~';
		
		pulaEspacoIn();
		/* Verifica se o operador realmente � un�rio ou se � bin�rio, mas falta um operando */
		if (!eLetra() && in[indIn] != '(')
			return montaErro(OPERANDO_ESPERADO, indIn);
		
		(*arv)->esq = NULL;
		(*arv)->info = unr;
		
		(*arv)->dir = MALLOC(sizeof(NoArvBin));
		
		erroP = Termo(&((*arv)->dir));
		
		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
		
	} else if (in[indIn] == '+' || in[indIn] == '-' || in[indIn] == '*' || 
			   in[indIn] == '/' || in[indIn] == '^' || in[indIn] == ')' || 
			   in[indIn] == '\0') {
		return montaErro(OPERANDO_ESPERADO, indIn);
		
	} else return montaErro(CARACTERE_INVALIDO, indIn);
	
	return resCorreto;

} /* Primario */

/* Percursos */

void ArvPre(ArvBin arv, char *pre) {
 /* Produz a representa��o pr�-fixa a partir da �rvore. */
	while (arv != NULL) {
		*pre = arv->info;
		pre++;
		ArvPre(arv->esq, pre);
		arv = arv->dir;
	}
	
	*pre = '\0';
}

void ArvPos(ArvBin arv, char *pos) {
/* Produz a representa��o p�s-fixa a partir da �rvore. */  
	if (arv != NULL) {
		ArvPos(arv->esq, pos);
		ArvPos(arv->dir, pos);
		*pos = arv->info;
		pos++;
	}
	
	*pos = '\0';
}


void LiberaArv(ArvBin arv) {
/* Libera o espa�o ocupado pela �rvore. */
	if (arv != NULL) {
		LiberaArv(arv->esq);
		LiberaArv(arv->dir);
		FREE(arv);
	}
}

