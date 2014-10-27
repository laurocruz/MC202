/***************************************************************** 
 * Lauro Cruz e Souza - RA: 156175                               *
 * MC202 - Turma F                                               *
 * laurocruzsouza@gmail.com / lauro.souza@students.ic.unicamp.br *
 * Laboratório 05 - Análise sintática - analisador.c             *
 * Last modified: 12-10-2013                                     *
 *****************************************************************/

/* 
 * analisador.c: Módulo de transformação de expressões na notação
 * infixa para pós-fixa.
 */

#include "analisador.h"
#include <ctype.h>

/* Variáveis globais a este módulo */

char ant; /* Armazena o caractere da entrada anterior ao que in está apontando */

char *in;  /* Cadeia e índice para expressão infixa (entrada). */
int indIn;

char *pos; /* Cadeia e índice para expressão pósfixa (saída). */
int indPos;

Erro resCorreto = {EXPR_VALIDA,0}; /* resultado correto */

void pulaEspacoIn(); /* Pula os espaços em branco da infixa */
int eLetra(); /* Verifica se *in é uma letra */
int car_inv(); /* Verifica se o caractere é inválido */

/* Protótipos das funções mutuamente recursivas  */
Erro Expressao();
Erro Termo();
Erro Fator();
Erro Primario();

/* Função auxiliar */
Erro montaErro(int codigo, int pos);

/*************************************************************/
/*                 Função   principal                        */
/*************************************************************/

Erro InPos(char *infixa, char *posfixa) {
/* Transforma uma expressão da notação infixa para a pós-fixa. Em caso
   de erro, devolve o código e a posição na cadeia de entrada onde o
   erro foi encontrado.  */
	Erro final;

	ant = ' '; /* Como não há anterior, inicia-se valendo ' ' */
	
	/* Armazenando os vetores de caracteres passados como parâmetro */
	in = infixa;
	indIn = 0;
	
	pos = posfixa;
	indPos = 0;
	
	if (*in == ' ') pulaEspacoIn();
	
	/* Não encontrando nenhum caractere na entrada, ?e uma cadeia de bracos */
	if (*in == '\0')
		return montaErro(CADEIA_DE_BRANCOS, 0);

	final = Expressao();
	
	/* Caso retorne para essa função considerando a expressão correta e sem chegar ao fim do vetor
	 * significa que está faltando um operando na expressão */
	if ((*in != '\0') && (final.codigoErro == EXPR_VALIDA))
		return montaErro(OPERADOR_ESPERADO, indIn);
	
	*pos = '\0';
 
	return final;
  
}

/*************************************************************/
/*           Funções de implementação do analisador          */
/*************************************************************/

void pulaEspacoIn() {
	/* Pula os espaços em branco */
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
	/* Verifica se o caractere é uma letra */
	return ((toupper(*in) >= 'A') && (toupper(*in) <= 'Z'));
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
	return (*in != '+' && *in != '-' && 
			*in != '*' && *in != '/' && 
			*in != '^' && *in != '\0'&&
			*in != '(' && *in != ')' && !eLetra());

}

Erro Expressao() {
/* Processa uma expressão da cadeia de entrada.  */
	char op;
	Erro erroE = Termo(); 
	/* A expressão é um termo ou um conjunto de termos separados por + e/ou - */
	
	if (erroE.codigoErro != EXPR_VALIDA)
		return erroE;
	
	
	while (*in == '+' || *in == '-') {
		/* Armazenando o operador para poder deslocar no vetor */
		op = *in;

		pulaEspacoIn();
		
		/* Verifica o próximo termo */
		erroE = Termo();
		
		if (erroE.codigoErro != EXPR_VALIDA)
			return erroE;

		/* Armazena o operador no vetor pos e pula uma posição */
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
	/* O termo é um fator ou um conjunto de fatores separados por * e/ou / */
	
	if (erroT.codigoErro != EXPR_VALIDA)
		return erroT;
	
	while ((*in == '*') || (*in == '/')) {
		/* Armazenando o operador para poder se descolar no vetor */
		op = *in;
		
		pulaEspacoIn();
		
		/* Verifica o próximo fator */
		erroT = Fator();
		
		if (erroT.codigoErro != EXPR_VALIDA)
			return erroT;
		
		/* Armazena o operando no vetor da posfixa e pula uma posição */
		*pos = op;
		pos++;
		indPos++;
	}
	
	return resCorreto;

} /* Termo */


Erro Fator() {
/* Processa um fator da cadeia de entrada.  */
	Erro erroF = Primario();
	/* O fator é um primário ou um primario elevado por outro fator */
	
	if (erroF.codigoErro != EXPR_VALIDA)
		return erroF;
	
	/* Verifica se há caractere inválido que não foi pego em Primario() */
	if (car_inv())
		return montaErro(CARACTERE_INVALIDO, indIn);
		
	if (*in == '^') {
		pulaEspacoIn();
		
		/* Verifica o próximo fator */
		erroF = Fator();
		
		if (erroF.codigoErro != EXPR_VALIDA)
			return erroF;
		
		/* Armazena o operando na posfixa e pula uma posição */
		*pos = '^';
		
		pos++;
		indPos++;

	}
  
	return resCorreto;

} /* Fator */


Erro Primario() {
/* Processa um fator primário da cadeia de entrada.  */
	Erro erroP;
	char unr, let;
	
	/* Pula os espaçõs em branco caso existam */
	if (*in == ' ')
		pulaEspacoIn();

	/* Encontra um operando */
	if (eLetra()) {
		/* Armazena o operando pra poder se deslocar no vetor */
		let = *in;
		pulaEspacoIn();
		
		/* Verifica se há dois operandos um ao lado do outro */
		if (eLetra())
			return montaErro(OPERADOR_ESPERADO, indIn);
		
		/* Armazena o operando na posfixa e pula uma posição */
		*pos = let;
		pos++;
		indPos++;
			
	/* Encontra um abre parênteses */
	} else if (*in == '(') {
		pulaEspacoIn();
		/* Verifica se não há operando ou operador após abrir o parêntese */
		if (*in == '\0' || *in == ')') /* Se não houver, falta operando */
			return montaErro(OPERANDO_ESPERADO, indIn);
		
		/* Dentro de parenteses deve existir uma expressão "separada" do resto */
		erroP = Expressao();
		
		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
		
		/* Verifica de faltou o fecha parêntese */
		if (*in != ')')
			return montaErro(FECHA_PARENTESE_ESPERADO, indIn);
		
		pulaEspacoIn();
		
	/* Verifica se é operador unário */
	} else if ((*in == '+' || *in == '-') && (ant == ' ' || ant == '(')) {
		if (*in == '+') unr = '&';
		else unr = '~';
		
		pulaEspacoIn();
		/* Verifica se o operador realmente é unário ou se é binário, mas falta um operando */
		if (!eLetra() && *in != '(')
			return montaErro(OPERANDO_ESPERADO, indIn);
		/* Verifica o termo do operador unário */
		erroP = Termo();
		
		if (erroP.codigoErro != EXPR_VALIDA)
			return erroP;
		
		/* Armazena o operador e pula uma posição */
		*pos = unr;
		pos++;
		indPos++;
	
	/* Caso for encontrado um operador nesse momento ou se estiver no fim da expressão, fatou um
	 * operando */
	} else if (*in == '+' || *in == '-' || *in == '*' || 
			   *in == '/' || *in == '^' || *in == ')' || *in == '\0') {
		return montaErro(OPERANDO_ESPERADO, indIn);
		
	/* Caso não entrar em nenhum dos casos anteriores, o caractere é inválido */
	} else return montaErro(CARACTERE_INVALIDO, indIn);
	
	return resCorreto;

} /* Primario */
