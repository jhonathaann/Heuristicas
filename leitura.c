#include <stdio.h>
#include <stdlib.h>

int main() {
    
    char instance_ref[20];
    int n;  // quantidade de itens
    int *c; // valores dos itens
    int **c_ij; // bonus do par ij
    int tipo_restricao; // tipo de restrição (0 para <=)
    int capacidade; // capacidade da mochila
    int *peso; // pesos (a_i)

    FILE *valores_itens = fopen("valores_itens.txt", "r");
    FILE *peso_itens = fopen("peso_itens.txt", "r");

    if(valores_itens == NULL || peso_itens == NULL){
        printf("Erro ao abrir os aquivos de peso e/ou valor dos itens!\n");
        return 1;
    }
    
    FILE *file = fopen("r_100_25_1.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // lendo o nome do arquivo
    fscanf(file, "%s", instance_ref);
    printf("intancia: %s\n", instance_ref);

    // lendo a quantidade de itens e a capacidade da mochila
    fscanf(file, "%d", &n);
    printf("quantidade de itens: %d\n", n);
    fscanf(file, "%d", &capacidade);
    printf("capacidade da mochila: %d\n", capacidade);

    // alocando memoria para o vetor dos valores do itens e dos peso dos itens
    c = (int *)malloc(n * sizeof(int));
    peso = (int *)malloc(n * sizeof(int));

    // lendo os valores dos itens
    printf("coeficientes lineares: ");
    for (int i = 0; i < n; i++) {
        fscanf(valores_itens, "%d", &c[i]);
        printf("%d ", c[i]);
    }
    printf("\n");

    // alocando a matriz de bonus (matriz triangular)
    c_ij = (int **)malloc((n-1) * sizeof(int *));
    for (int i = 0; i < n-1; i++) {
        c_ij[i] = (int *)malloc((n - i - 1) * sizeof(int)); 
    }

    // lendo os bonus
    printf("coeficientes quadraticos (bonus_ij):\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            fscanf(file, "%d", &c_ij[i][j - i - 1]);
            printf("%d ", c_ij[i][j - i - 1]);
            
        }
        printf("teste1\n");
    }

    // lendo o tipo de restricao
    fscanf(file, "%d", &tipo_restricao);
    printf("tipo de restricao: %d (<=)\n", tipo_restricao);



    // lendo os pesos dos itens
    printf("pesos dos itens: ");
    for (int i = 0; i < n; i++) {
        fscanf(peso_itens, "%d", &peso[i]);
        printf("%d ", peso[i]);
    }
    printf("\n");

    fclose(file);

    free(c);
    free(peso);
    for (int i = 0; i < n-1; i++) {
        printf("liberando memoria!\n");
        free(c_ij[i]);
    }
    printf("teste1");
    free(c_ij);
    printf("teste2");

    return 0;
}
