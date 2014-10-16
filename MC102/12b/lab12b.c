/***********************************
 * Nome: Lauro Cruz e Souza        *
 * RA: 156175                      *
 * Email: laurocruzsouza@gmail.com *
 * Laboratorio 12b - Whiteworse    *
 ***********************************/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Tamanho maximo do nome do titular */
#define MAXNOME 21
/* Tamanho maximo do nome dos arquivos de entrada/saida */
#define MAXNOMEARQ 101
/* Valor da taxa de deposito em conta com saldo negativo */
#define TAXA 5.00

/* Conta
 * ag = numero da agencia
 * cc = numero da conta corrente
 * titular = Nome do titular da conta
 * saldo = Saldo da conta
 */
struct Conta {
	int ag;
	int cc;
	char titular[MAXNOME];
	double saldo;
};

typedef struct Conta Conta;


/* Transacao
 * tipo - 'D' para Depositos e 'S' para Saques
 * ag - Numero da agencia
 * cc - Numero da conta corrente
 * valor - Valor da operacao
 */
struct Transacao {
    char tipo;
    int ag;
    int cc;
    double valor;
};

typedef struct Transacao Transacao;

void making_transactions(int ntrans, int exis_accounts, Conta *accounts,
						 Transacao *transactions);

int main(int argc, char **argv) {
    /* Nome do arquivo binario com as contas */
    char nomeArqConta[MAXNOMEARQ];
    /* Nome do arquivo binario com as transacoes */
    char nomeArqTrans[MAXNOMEARQ];
    /* Nome do arquivo binario de saida */
    char nomeArqSaida[MAXNOMEARQ];
    
	FILE *contas, *trans, *out;
	int exis_accounts, ntrans;
	Conta *accounts;
	Transacao *transactions;
	
    /* Obtendo o nome dos arquivos */
    strcpy(nomeArqConta, argv[1]);
    strcpy(nomeArqTrans, argv[2]);
    strcpy(nomeArqSaida, argv[3]);
	
	/* Abrindo os arqivos das contas, transacoes e o arquivo de saida das 
	 * contas atualizadas */
	contas = fopen(nomeArqConta, "rb");
	trans = fopen(nomeArqTrans, "rb");
	out = fopen(nomeArqSaida, "wb");
	
	if ((contas == NULL) || (trans == NULL) || (out == NULL))
		return 0;

		/**** Contas ****/
		
	/* Le quantidade de contas */
	fread(&exis_accounts, sizeof(int), 1, contas);
	
	/* Aloca um vetor de contas */
	accounts = malloc(exis_accounts * sizeof(Conta));
	
	/* Armazena as informacoes das contas presentes no arquivo binario no vetor
	 * de registros de conta */
	fread(accounts, sizeof(Conta), exis_accounts, contas);
	
		/**** Transacoes ****/
		
	/* Le a quantidade de transacoes */
	fread(&ntrans, sizeof(int), 1, trans);
	
	/* Aloca um vetor de transacoes */
	transactions = malloc(ntrans * sizeof(Transacao));
	
	/* Armazena as informacoes das transacoes presentes no arquivo binario no 
	 * vetor de registros de transacao */
	fread(transactions, sizeof(Transacao), ntrans, trans);
	
	
		/**** Fazendo as transacoes ****/
	making_transactions(ntrans, exis_accounts, accounts, transactions);
	
		/**** Escrevendo as contas atualizada no arquivo de saida ****/
	fwrite(&exis_accounts, sizeof(int), 1, out);
	
	fwrite(accounts, sizeof(Conta), exis_accounts, out);
	
	/* Fechando os arquivos abertos */
	if (contas)
		fclose(contas);
	if (trans)
		fclose(trans);
	if (out)
		fclose(out);
	
	/* Liberando a memoria alocada */
	free(accounts);
	free(transactions);
	
	
    return 0;
}

/* Funcao que faz altera os saldos dos clientes de acordo com as transacoes e
 * imprime as transacoes validas */
void making_transactions(int ntrans, int exis_accounts, Conta *accounts,
						Transacao *transactions) {
	int i, j, valido;

	for (i = 0; i < ntrans; i++) {
		valido = 0;
		for (j = 0; (j < exis_accounts) && (valido == 0); j++) {
			/* Caso o numero da agencias seja igual ...*/
			if ((transactions[i].ag == accounts[j].ag) && 
				(transactions[i].cc == accounts[j].cc)) {
				/* Se for um deposito o dinheiro e adicionado ao saldo */
				if (transactions[i].tipo == 'D') {
					accounts[j].saldo += transactions[i].valor;
					valido = 1; /* Transacao valida */
					/* Se for um saque...*/
				} else if (transactions[i].tipo == 'S') {
					/* Caso o saldo seja positivo e o saldo menos o valor 
					 do saque seja maior ou igual a -100.00, a transacao e 
					 * realizada */
					if ((accounts[j].saldo > 0) &&
						(accounts[j].saldo - transactions[i].valor >= -100)) {
						accounts[j].saldo -= transactions[i].valor;
						if (accounts[j].saldo < 0) {
							accounts[j].saldo -= TAXA;
						}
						valido = 1; /* Transacao valida */
					}
				}
			}
		}
		/* Imprime as transacoes validas */
		if (valido) {
			printf("T%d: %c %d %d %.2f\n", i, transactions[i].tipo,
				transactions[i].ag, transactions[i].cc,
			transactions[i].valor);
		}
	}
}
