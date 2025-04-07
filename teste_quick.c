#include <stdio.h>

typedef struct {
    int *codigo_turma;
    int *peso_atribuido;
    int tamanho;
} Auxiliar;

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Auxiliar *dados, int baixo, int alto) {
    int pivo = dados->peso_atribuido[alto];  // Pivô escolhido como o último elemento
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (dados->peso_atribuido[j] >= pivo) {  // Ordenação decrescente
            i++;
            trocar(&dados->peso_atribuido[i], &dados->peso_atribuido[j]);
            trocar(&dados->codigo_turma[i], &dados->codigo_turma[j]);
        }
    }
    
    trocar(&dados->peso_atribuido[i + 1], &dados->peso_atribuido[alto]);
    trocar(&dados->codigo_turma[i + 1], &dados->codigo_turma[alto]);
    
    return i + 1;
}

void quickSort(Auxiliar *dados, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(dados, baixo, alto);

        quickSort(dados, baixo, pi - 1);
        quickSort(dados, pi + 1, alto);
    }
}

void imprimir(Auxiliar *dados) {
    printf("codigo_turma; peso_atribuido;\n");
    for (int i = 0; i < dados->tamanho; i++) {
        printf("%d;%d;\n", dados->codigo_turma[i], dados->peso_atribuido[i]);
    }
}

int main() {
    int codigos[] = {54, 156, 2, 16, 1, 211, 74, 116, 17, 80};
    int pesos[] = {5, 5, 5, 10, 10, 3, 5, 5, 10, 5};
    int tamanho = 10;

    Auxiliar dados;
    dados.codigo_turma = codigos;
    dados.peso_atribuido = pesos;
    dados.tamanho = tamanho;

    printf("ANTES DA ORDENACAO:\n");
    imprimir(&dados);

    quickSort(&dados, 0, tamanho - 1);

    printf("\nDEPOIS DA ORDENACAO:\n");
    imprimir(&dados);

    return 0;
}
