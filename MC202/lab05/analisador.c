/***************************************************************** 
 * Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laborat�rio 05 - An�lise sint�tica - analisador.c             *
 * Last modified: 12-10-2013                                     *
 *****************************************************************/

/* 
 * analisador.c: M�dulo de transforma��o de express�es na nota��o
 * infixa para p�s-fixa.
 */

#include "analisador.h"
#include <ctype.h>

/* Vari�veis globais a este m�dulo */

char ant; /* Armazena o caractere da entrada anterior ao que in est� apontando */

char *in;  /* Cadeia e �ndice para express�o infixa (entrada). */
int indIn;

char *pos; /* Cadeia e �ndice para express�o p�sfixa (sa�da). */
int indPos;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

void pulaEspacoIn(); /* Pula os espa�os em branco da infixa */
int eLetra(); /* Verifica se *in � uma letra */
int car_inv(); /* Verifica se o caractere � inv�lido */

/* Prot�tipos das fun��es mutuamente recursivas  */
Erro Expressao();
Erro Termo();
Erro Fator();
Erro Primario();

/* Fun��o auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Fun��o   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma express�o da nota��o infixa para a p�s-fixa. Em caso
   de erro, devolve o c�digo e a posi��o na cadeia de entrada onde o
   erro foi encontrado.  */
	Erro final;

	ant = ' '; /* Como n�o h� anterior, inicia-se valendo ' ' */
	
	/* Armazenando os vetores de caracteres passados como par�metro */
	in = infixa;
	indIn = 0;
	
	pos = posfixa;
	indPos = 0;
	
	if (*in == ' ') pulaEspacoIn();
	
	/* N�o encontrando nenhum caractere na entrada, ?e uma cadeia de bracos */
	if (*in == '\0')
		return montaErro(CADEIA_DE_BRANCOS, 0);

	final = Expressao();
	
	/* Caso retorne para essa fun��o considerando a express�o correta e sem chegar ao fim do vetor
	 * significa que est� faltando um operando na express�o */
	if ((*in != '\0') && (final.codigoErro == EXPR_VALIDA))
		return montaErro(OPERADOR_ESPERADO, indIn);
	
	*pos = '\0';
 
	return final;
  
}

/*************************************************************/
/*           Fun��es de implementa��o do analisador          */
/*************************************************************/

void pulaEspacoIn() {
	/* Pula os espa�os em branco */
	if (*in != ' ') 
		ant = *in; /* Armazena o valor do caractere anterior */
	
	in++;
	indIn++;
	
	while (*in == ' ') {
		in++;
		indIn++;
	}
}

int eLetra() {
	/* Verifica se o caractere � uma letra */
	return ((toupper(*in) >= 'A') && (toupper(*in) <= 'Z'));
}

Erro montaErro(int codigo, int posicao) {
/* Devolve estrutura com c�digo de erro e posi��o */
	Erro res;
	
	res.posicao = posicao;
	res.codigoErro = codigo;
  
	return res;

} /* montaErro */

int car_inv() {
	/* Verifica se o caractere � inv�lido */
	return (*in != '+' && *in != '-' && 
			*in != '*' && *in != '/' && 
			*in != '^' && *in != '\0'&&
			*in != '(' && *in != ')' && !eLetra());

}

Erro Expressao() {
/* Processa uma express�o da cadeia de entrada.  */
	char op;
	Erro erroE = Termo(); 
	/* A express�o � um termo ou um conjunto de termos separados por + e/ou - */
	
	if (erroE.codigoErro != EXPR_VALIDA)
		return erroE;
	
	
	while (*in == '+' || *in == '-') {
		/* Armazenando o operador para poder deslocar no vetor */
		op = *in;

		pulaEspacoIn();
		
		/* Verifica o pr�ximo termo */
		erroE = Termo();
		
		if (erroE.codigoErro != EXPR_VALIDA)
			return erroE;

		/* Armazena o operador no vetor pos e pula uma posi��o */
		*pos = op;
		pos++;
		indPos++;
	}
	
	return resCorreto;

} /* Expressao */


Erro Termo() {
/* Processa um termo da cadeia de entrada.  */
	char op;
	Erro erroT = Fator();
	/* O termo � um fator ou um conjunto de fatores separados por * e/ou / */
	
	if (erroT.codigoErro != EXPR_VALIDA)
		return erroT;
	
	while ((*in == '*') || (*in == '/')) {
		/* Armazenando o operador para poder se descolar no vetor */
		op = *in;
		
		pulaEspacoIn();
		
		/* Verifica o pr�ximo fator */
		erroT = Fator();
		
		if (erroT.codigoErro != EXPR_VALIDA)
			return erroT;
		
		/* Armazena o operando no vetor da posfixa e pula uma posi��o */
		*pos = op;
		pos++;
		indPos++;
	}
	
	return resCorreto;

} /* Termo */


Erro Fator() {
/* Processa um fator da cadeia de entrada.  */
	Erro erroF = Primario();
	/* O fator � um prim�rio ou um primario elevado por outro fator */
	
	if (erroF.codigoErro != EXPR_VALIDA)
		return erroF;
	
	/* Verifica se h� caractere inv�lido que n�o foi pego em Primario() */
	if (car_inv())
		return montaErro(CARACTERE_INVALIDO, indIn);
		
	if (*in == '^') {
		pulaEspacoIn();
		
		/* Verifica o pr�ximo fator */
		erroF = Fator();
		
		if (erroF.codigoErro != EXPR_VALIDA)
			return erroF;
		
		/* Armazena o operando na posfixa e pula uma posi��o */
		*pos = '^';
		
		pos++;
		indPos++;

	}
  
	return resCorreto;

} /* Fator */


Erro Primario() {
/* Processa um fator prim�rio da cadeia de entrada.  */
	Erro erroP;
	char unr, let;
	
	/* Pula os espa��s em branco caso existam */
	if (*in == ' ')
		pulaEspacoIn();

	/* Encontra um operando */
	if (eLetra()) {
		/* Armazena o operando pra poder se deslocar no vetor */
		let = *in;
		pulaEspacoIn();
		
		/* Verifica se h� dois operandos um ao lado do outro */
		if (eLetra())
			return montaErro(OPERADOR_ESPERADO, indIn);
		
		/* Armazena o operando na posfixa e pula uma posi��o */
		*pos = let;
		pos++;
		indPos++;
			
	/* Encontra um abre par�nteses */
	} else if (*in == '(') {
		pulaEspacoIn();
		/* Verifica se n�o h� operando ou operador ap�s abrir o par�ntese */
		if (*in == '\0' || *in == ')') /* Se n�o houver, falta operando */
			return montaErro(OPERANDO_ESPERADO, indIn);
		
		/* Dentro de parenteses deve existir uma express�o "separada" do resto */
		erroP = Expressao();
		
		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
		
		/* Verifica de faltou o fecha par�ntese */
		if (*in != ')')
			return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
		
		pulaEspacoIn();
		
	/* Verifica se � operador un�rio */
	} else if ((*in == '+' || *in == '-') && (ant == ' ' || ant == '(')) {
		if (*in == '+') unr = '&';
		else unr = '~';
		
		pulaEspacoIn();
		/* Verifica se o operador realmente � un�rio ou se � bin�rio, mas falta um operando */
		if (!eLetra() && *in != '(')
			return montaErro(OPERANDO_ESPERADO, indIn);
		/* Verifica o termo do operador un�rio */
		erroP = Termo();
		
		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
		
		/* Armazena o operador e pula uma posi��o */
		*pos = unr;
		pos++;
		indPos++;
	
	/* Caso for encontrado um operador nesse momento ou se estiver no fim da express�o, fatou um
	 * operando */
	} else if (*in == '+' || *in == '-' || *in == '*' || 
			   *in == '/' || *in == '^' || *in == ')' || *in == '\0') {
		return montaErro(OPERANDO_ESPERADO, indIn);
		
	/* Caso n�o entrar em nenhum dos casos anteriores, o caractere � inv�lido */
	} else return montaErro(CARACTERE_INVALIDO, indIn);
	
	return resCorreto;

} /* Primario */
