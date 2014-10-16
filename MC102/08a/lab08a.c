#include <stdio.h>
#include <stdlib.h>

int ** aloca_matriz(int usuarios);
void free_matriz(int **matriz, int usuarios);

int main() {
    int usuarios, user, **relac, *amigos, *suggest, k = 0, h = 0, i, j;
    int popular = 1, seg = 1, teste = 0, row = 0;
    
    scanf("%d %d", &usuarios, &user);
    
    relac = aloca_matriz(usuarios);
    amigos = malloc((usuarios-1) * sizeof(int));
    
    for (i = 0; i < usuarios; i++) {
        for (j = 0; j < usuarios; j++) {
            scanf("%d", &relac[i][j]);
        }
    }
    
    for (i = 0; i < usuarios; i++) {
        if ((relac[user][i] == 1) && (user != i)) {
            amigos[k++] = i;
        }
    }
    suggest = malloc((usuarios - 1 - k) * sizeof(int));
    
    if ((k != usuarios - 1) && (k != 0)) {
        popular = 0;
        for (i = 0; i < usuarios; i++) {
            if (i != user) {
                row = 0;
                seg = 1;
                for (j = 0; (j < k) && (seg != 0); j++) {
                    if (i == amigos[j]) {
                        seg = 0;
                    }
                }
                if (seg != 0) {
                    for (j = 0; j < k; j++) {
                        if (relac[i][amigos[j]] == 1) {
                            row = 1;
                        }
                    }
                }
                if (row != 0) {
                    teste = 1;
                    suggest[h++] = i;
                }
            }
        }
    }
    
    if (popular == 0) {
        if (teste != 0) {
            printf("Sugestao de amigos:");
            for (i = 0; i < h; i++) {
                printf(" %d", suggest[i]);
            }
        } else {
            printf("Sem sugestao de novos amigos");
        }
    } else {
        printf("Sem sugestao de novos amigos");
    }
    
    printf("\n");
    
    free_matriz(relac, usuarios);
    free(suggest);
    free(amigos);
    
    return 0;
}

int ** aloca_matriz(int usuarios) {
    int i, **matriz;
    
    matriz = malloc(usuarios * sizeof(int *));
    
    for (i = 0; i < usuarios; i++) {
        matriz[i] = malloc(usuarios * sizeof(int));
    }
    return matriz;
}

void free_matriz(int **matriz, int usuarios) {
    int i;
    
    for (i = 0; i < usuarios; i++) {
        free(matriz[i]);
    }
    
    free(matriz);
}