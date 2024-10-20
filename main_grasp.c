#include <stdio.h>
#include "grasp_funcoes.c"


int main(){
    celula *itens = NULL;
    celula *solucao;  // lista que vai conter todos os itens que fazem parte da solucao 
    FILE *pt_arq = fopen("input.txt", "r");
    int max_iteracoes = 10;
    int capacidade, item, valor, peso;

    fscanf(pt_arq, "%d", &capacidade);
    fscanf(pt_arq, "%d", &item);

    printf("%d\n", capacidade);
    for(int i = 0; i < item; i++){

        // faço a contrucao da solucao gulosa randomizada
        //    funcaox(itens, &solucao)
        fscanf(pt_arq, "%d %d", &valor, &peso);

       // printf("item %d valor: %d peso: %d\n", i+1, valor, peso);

        insercao(i+1, peso, valor, &itens);
    }

    for(int i = 0; i < max_iteracoes; i++){
        contrucao_gulosa_randomizada(itens, &solucao, capacidade, 0.5);
    }

    imprimir(itens);
    //imprimir(solucao);

    fclose(pt_arq);

    return 0;
}
