#include <stdio.h>
#include <string.h>

#define MAXNOME 101

struct Conta {
    int ag;
    int cc;
    char titular[MAXNOME];
    double saldo;
};

typedef struct Conta Conta;

int main(int argc, char **argv) {
	FILE *txt, *bin;
	char nometxt[101], nomebin[101];
	Conta x;
	int c;
	
	strcpy(nometxt, argv[1]);

	strcpy(nomebin, argv[2]);

	txt = fopen(nometxt, "w");
	
	if (txt == NULL) {
		printf("Nao foi possivel abrir o arquivo texto\n");
		return 0;
	}
	
	bin = fopen(nomebin, "rb");
	
	if (bin == NULL) {
		printf("Nnao foi possivel abrir o arquivo binario\n");
		return 0;
	}
	
	fread(&c, sizeof(int), 1, bin);
	fprintf(txt, "%d\n", c);
	
	while (fread(&x, sizeof(Conta), 1, bin)) {
		fprintf(txt, "%s ", x.titular);
		fprintf(txt, "%d ", x.ag);
		fprintf(txt, "%d ", x.cc);
		fprintf(txt, "%.2f\n\n", x.saldo);
	}
	
	
	if (txt)
		fclose(txt);
	if (bin)
		fclose(bin);
	
	return 0;
}
