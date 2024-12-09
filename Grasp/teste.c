#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura que representa cada linha da matriz triangular
typedef struct {
    int *coeficientes; // Vetor dinâmico para armazenar os coeficientes de cada linha
    int tamanho;       // Tamanho do vetor de coeficientes (quantidade de elementos)
} LinhaCoeficientes;

int main() {
    char instance_ref[20];
    int n; // número de variáveis
    int *c; // coeficientes lineares (c_i)
    LinhaCoeficientes *linhas; // vetor de structs para armazenar as linhas da matriz triangular
    int constraint_type; // tipo de restrição (0 para <=)
    int capacity; // capacidade da mochila
    int *weights; // pesos (a_i)

    FILE *valores_itens = fopen("valores_itens.txt", "r");
    FILE *peso_itens = fopen("peso_itens.txt", "r");

    if(valores_itens == NULL || peso_itens == NULL){
        printf("Erro ao abrir os aquivos de peso e/ou valor dos itens!\n");
        return 1;
    }
    
    // Abrir o arquivo de entrada
    FILE *file = fopen("r_100_25_1.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler referência da instância
    fscanf(file, "%s", instance_ref);
    printf("instancia: %s\n", instance_ref);

    // Ler o número de variáveis
    fscanf(file, "%d", &n);
    printf("quantidade de itens : %d\n", n);
    // Ler a capacidade da mochila
    fscanf(file, "%d", &capacity);
    printf("capacidade da mochila: %d\n", capacity);

    // Alocar memória para coeficientes lineares e pesos
    c = (int *)malloc(n * sizeof(int));
    weights = (int *)malloc(n * sizeof(int));

    // Ler coeficientes lineares (c_i)
    printf("coeficientes lineares: ");
    for (int i = 0; i < n; i++) {
        fscanf(valores_itens, "%d", &c[i]);
        printf("%d ", c[i]);
    }
    printf("\n");

    // Alocar memória para o vetor de structs (linhas da matriz)
    linhas = (LinhaCoeficientes *)malloc((n - 1) * sizeof(LinhaCoeficientes));

    // Ler coeficientes quadráticos (c_ij) e armazená-los em cada struct
    printf("coeficientes quadraticos:\n");
    for (int i = 0; i < n - 1; i++) {
        // Definir o tamanho do vetor de coeficientes para a linha i
        linhas[i].tamanho = n - i - 1;
        // Alocar o vetor de coeficientes para a linha i
        linhas[i].coeficientes = (int *)malloc(linhas[i].tamanho * sizeof(int));

        // Ler e armazenar os coeficientes para a linha i
        for (int j = 0; j < linhas[i].tamanho; j++) {
            fscanf(file, "%d", &linhas[i].coeficientes[j]);
            printf("%d ", linhas[i].coeficientes[j]);
        }
        printf("\n");
    }

    // Ler tipo de restrição
    fscanf(file, "%d", &constraint_type);
    printf("tipo de restricao: %d (<=)\n", constraint_type);



    // Ler os pesos dos itens
    printf("pesos dos itens: ");
    for (int i = 0; i < n; i++) {
        fscanf(peso_itens, "%d", &weights[i]);
        printf("%d ", weights[i]);
    }
    printf("\n");

    // Fechar o arquivo
    fclose(file);

    // Liberar memória
    free(c);
    free(weights);
    for (int i = 0; i < n - 1; i++) {
        free(linhas[i].coeficientes);
    }
    free(linhas);

    return 0;
}
