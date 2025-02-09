#include <stdio.h>

#define PROFESSORES 4
#define DISCIPLINAS 5

typedef struct {
    int G[PROFESSORES][DISCIPLINAS];  // Apenas a declaração
    int *carga_horaria;
} disciplinas;

void inicializarDisciplinas(disciplinas *d) {
    int valores[PROFESSORES][DISCIPLINAS] = {
        {10, 5, 0, 7, 4},
        {2, 9, 8, 0, 7},
        {0, 6, 10, 8, 5},
        {7, 0, 5, 9, 10}
    };

    // Copiar os valores para a matriz dentro da struct
    for (int i = 0; i < PROFESSORES; i++) {
        for (int j = 0; j < DISCIPLINAS; j++) {
            d->G[i][j] = valores[i][j];
        }
    }
}

int main() {
    disciplinas d;
    inicializarDisciplinas(&d);

    // Teste: imprimir a matriz G
    for (int i = 0; i < PROFESSORES; i++) {
        for (int j = 0; j < DISCIPLINAS; j++) {
            printf("%d ", d.G[i][j]);
        }
        printf("\n");
    }

    return 0;
}
