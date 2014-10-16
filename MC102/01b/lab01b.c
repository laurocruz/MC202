/* Nome: Lauro Cruz e Souza
 * RA: 156175
 * Laboratorio 01b - Notas do Vestibular */

#include <stdio.h>

int main() {
   
   /* Declaração das variaveis (notas absolutas, pesos das materias, notas
    * padronizadas, notas minimas etc) */
    int A, NMO;
    double PCG, PIN, PPO, PMA, PCH, PCN, NCG, MCG, DPCG, NIN, MIN, DPIN, NPO,
MPO, DPPO, NMA, MMA, DPMA, NCH, MCH, DPCH, NCN, MCN, DPCN, NPCG, NPIN, NPPO,
NPMA, NPCH, NPCN, NF;

    /* Leitura do código da area do curso, nota minima das provas associadas a
     * area do curso e dados para calcular a nota padronizada da primeira fase
     */
    scanf("%d %d", &A, &NMO);
    scanf("%lf %lf %lf %lf %lf %lf", &PCG, &PIN, &PPO, &PMA, &PCH, &PCN);
    scanf("%lf %lf %lf", &NCG, &MCG, &DPCG);
    
    /* Calculo da nota padronizada da primeira fase */
    NPCG = ((NCG - MCG) * 100)/DPCG + 500;
    
    /* Condição que determina se o vestibulando passou ou não para a segunda
     * fase */
    if (NPCG >= 550) {
        scanf("%lf %lf %lf", &NIN, &MIN, &DPIN);
        scanf("%lf %lf %lf", &NPO, &MPO, &DPPO);
        scanf("%lf %lf %lf", &NMA, &MMA, &DPMA);
        scanf("%lf %lf %lf", &NCH, &MCH, &DPCH);
        scanf("%lf %lf %lf", &NCN, &MCN, &DPCN);
        
        /* Calculo das notas padronizadas das diferentes areas de conhecimento
         * da prova de segunda fase */
        NPIN = ((NIN - MIN) * 100)/DPIN + 500;
        NPPO = ((NPO - MPO) * 100)/DPPO + 500;
        NPMA = ((NMA - MMA) * 100)/DPMA + 500;
        NPCH = ((NCH - MCH) * 100)/DPCH + 500;
        NPCN = ((NCN - MCN) * 100)/DPCN + 500;
        
        /* Calculo da nota final (nota da segunda fase) */
        NF = ((NPCG * PCG) + (NPIN * PIN) + (NPPO * PPO) + (NPMA * PMA) + (NPCH
* PCH) + (NPCN * PCN))/(PIN + PPO + PMA + PCH + PCN + PCG);
        
        printf("Primeira Fase: %.1f\n", NPCG);
        printf("Segunda Fase: %.1f\n", NF);
        
        /* Condicionais para determinar se o vestibulando foi listado no grupo
         * 1 ou grupo 2 */
        if (A == 1) {
            if ((NPMA >= NMO) && (NPCN >= NMO)) {
                printf("Grupo 1\n");
                
            } else {
                printf("Grupo 2\n");
            } 
        }
        
        if (A == 2) {
            if ((NPPO >= NMO) && (NPCH >= NMO)) {
                printf("Grupo 1\n");
                
            } else {
                printf("Grupo 2\n");
            }
        }
        
        if (A == 3) {
            if (NPCN >= NMO) {
                printf("Grupo 1\n");
                
            } else {
                printf("Grupo 2\n");
            }
        }
        
     } else { 
         printf("Primeira Fase: %.1f\n", NPCG);
     }
    return 0;
}     