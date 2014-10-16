/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratório 02a - INSS e IRPF */

#include <stdio.h>

int main() {
   
    /* Declaracao das variaves salario, dependentes, INSS, base e IRPF */
	int d;
	double inss, base, irpf, s;
    
	/* Entrada pelo usuario do salario e dependentes */
	scanf("%lf %d", &s, &d);

	/* Calculos do INSS, base e IRPF em função do salario e numero de 
	 * dependentes */
	if (s <= 1317.07) {
		inss = s * 0.08;
		base = s - inss - (179.71 * d);
		irpf = 0.0;

	} else if ((s >= 1317.08) && (s <= 2195.12)) {
		inss = s * 0.09;
		base = s - inss - (179.71 * d);
		if ((base >= 1787.78) && (base <= 2679.29))
			irpf = (base - 1787.78) * 0.075;
		else irpf = 0;
		
	} else if ((s >= 2195.13) && (s <= 4390.24)) {
		inss = s * 0.11;
		base = s - inss - (179.71 * d);
		if ((base >= 1787.78) && (base <= 2679.29))
			irpf = (base - 1787.78) * 0.075;
		else if ((base >= 2679.30) && (base <= 3572.43))
			irpf = ((base - 2679.30) * 0.15) + ((2679.29 - 1787.78) * 0.075);
		else if ((base >= 3572.44) && (base <= 4463.81))
			irpf = ((base - 3572.44) * 0.225) + ((3572.43 - 2679.30) * 0.15) + 
					((2679.29 - 1787.78) * 0.075);

	} else if (s >= 4390.24) {
		inss = 482.93;
		base = s - inss - (179.71 * d);
		if ((base >= 1787.78) && (base <= 2679.29))
			irpf = (base - 1787.78) * 0.075;
		else if ((base >= 2679.30) && (base <= 3572.43))
			irpf = ((base - 2679.30) * 0.15) + ((2679.29 - 1787.78) * 0.075);
		else if ((base >= 3572.44) && (base <= 4463.81)) 
			irpf = ((base - 3572.44) * 0.225) + ((3572.43 - 2679.30) * 0.15) + 
					((2679.29 - 1787.78) * 0.075);
		else if (base > 4463.81)
			irpf = ((base - 4463.82) * 0.275) + ((4463.81 - 3572.44) * 0.225) + 
					((3572.43 - 2679.30) * 0.15) + ((2679.29 - 1787.78) * 0.075);
	}
    
	/* Imprimindo valores do INSS, base e IRPF */
	printf("INSS: R$ %.2f\n", inss);
	printf("Base: R$ %.2f\n", base);
	printf("IRPF: R$ %.2f\n", irpf);
    
	return 0;
}