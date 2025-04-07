#include <stdio.h>

typedef struct {
    int *codigo_turma;
    int *peso_atribuido;
    int tamanho;  // Adicionamos um campo para o tamanho dos vetores
} Auxiliar;

void ordenar(Auxiliar *dados) {
    for (int i = 0; i < dados->tamanho - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < dados->tamanho; j++) {
            if (dados->peso_atribuido[j] > dados->peso_atribuido[max_idx]) {
                max_idx = j;
            }
        }
        // Troca peso_atribuido
        int temp_peso = dados->peso_atribuido[i];
        dados->peso_atribuido[i] = dados->peso_atribuido[max_idx];
        dados->peso_atribuido[max_idx] = temp_peso;

        // Troca codigo_turma para manter alinhamento
        int temp_codigo = dados->codigo_turma[i];
        dados->codigo_turma[i] = dados->codigo_turma[max_idx];
        dados->codigo_turma[max_idx] = temp_codigo;
    }
}

void imprimir(Auxiliar *dados) {
    printf("codigo_turma; peso_atribuido;\n");
    for (int i = 0; i < dados->tamanho; i++) {
        printf("%d;%d;\n", dados->codigo_turma[i], dados->peso_atribuido[i]);
    }
}

int main() {
    int codigos[] = {209, 161, 49, 157, 19, 182, 142, 147, 51, 22};
    int pesos[] = {9, 10, 10, 4, 10, 9, 4, 4, 10, 10};
    int tamanho = 10;

    Auxiliar dados;
    dados.codigo_turma = codigos;
    dados.peso_atribuido = pesos;
    dados.tamanho = tamanho;

    printf("ANTES DA ORDENACAO:\n");
    imprimir(&dados);

    ordenar(&dados);

    printf("\nDEPOIS DA ORDENACAO:\n");
    imprimir(&dados);

    return 0;
}
