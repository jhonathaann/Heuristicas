#include <stdio.h>
#include "grasp_funcoes.c"


int main(){

    celula *itens = NULL;  // lista que ira armazenar todos os itens de entrada 
    celula *solucao = NULL;  // lista que vai conter todos os itens que fazem parte da solucao 
    FILE *pt_arq = fopen("r_100_25_1.txt", "r");
    FILE *valores_itens = fopen("valores_itens.txt", "r");
    FILE *peso_itens = fopen("peso_itens.txt", "r");

    char referencia_instancia[20];
    int max_iteracoes = 1;
    int capacidade, quant_item, valor, peso;
    srand(0);  // inicializando a semente

    if(pt_arq == NULL || valores_itens == NULL || peso_itens == NULL){
        printf("Erro ao abrir um dos (ou mais) arquivos de entrada!\n");
        return 1;
    }

    // lendo a referencia da instacnia
    fscanf(pt_arq, "%s", referencia_instancia);
    printf("Arquivo: %s\n", referencia_instancia); 
    
    
    // lendo o numero de itens e a capacidade da mochila
    fscanf(pt_arq, "%d", &quant_item);
    fscanf(pt_arq, "%d", &capacidade);
    printf("quantidade de itens: %d ; capacidade da mochila: %d\n", quant_item,capacidade);



    //printf("%d\n", capacidade);
    // leitura dos itens (seu valor e seu peso)
    for(int i = 0; i < quant_item; i++){

        fscanf(valores_itens, "%d", &valor);
        fscanf(peso_itens, "%d", &peso);

       // printf("Inserindo o item %d\n", i+1);
        insercao(i+1, peso, valor, &itens);
    }

    // cada item x pode formar par com no maximo outros n-1 itens (considerando que temos ao todo n itens)
    // o campo da struct **bonus_ij (matriz alocada dinamicamente) ira conter o bonus do item i com o item j
   
    // alocando o vetor que ira guardar os bonus que existem com o item i
    // todos os item tem que ter esse vetor alocado. mas o tamanho desse vetor para cada item nao sera o mesmo

    // itens NAO Eh umvetor e sim uma lista encadeada. por isso nao faz sentido usar itens[i]
    celula *aux = itens;
    for(int i = 0; i < quant_item; i++){
        aux->bonus_i = (int *) malloc((quant_item - i - 1) * sizeof(int));
        //itens[i].bonus_i = (int *) malloc((quant_item - i - 1) * sizeof(int));

        //printf("Item: %d\n", aux->item);
        for(int j = 0; j < quant_item - i - 1; j++){
            fscanf(pt_arq, "%d", &aux->bonus_i[j]);
            //printf("%d ", aux->bonus_i[j]);
            //fscanf(pt_arq, "%d", &itens[i].bonus_i[j]);
            //printf("%d ", itens[i].bonus_i[j]);
        }
        aux = aux->proximo;
        //printf("\n");
    }

    //printf("lista de todos os itens na main:\n");
    //imprimir_itens(itens, quant_item);



    for(int i = 0; i < max_iteracoes; i++){
        apaga_lista(&solucao);
        contrucao_gulosa_randomizada(itens, &solucao, capacidade, 1);

        // busca local

        // antes desse laço rodar mais uma vez eu preciso "zerar" a lista "solucao"

        
    }

    printf("Itens:\n");
    imprimir_itens(itens, quant_item);
    printf("===========================================================================\n");
    printf("Solucao:\n");
    imprimir_solucao(solucao);
    int aux1 = calcula_bonus(itens, solucao, quant_item);
    int aux2 = calcula_solucao(solucao);
    printf("Valor dos bonus presente na solucao: %d\n",aux1);
    printf("Valor da solucao (SEM BONUS): %d\n", aux2);
    printf("Valor FINAL da solucao: %d\n", aux1 + aux2);


    fclose(pt_arq);
    fclose(valores_itens);
    fclose(peso_itens);

    return 0;

    
}
