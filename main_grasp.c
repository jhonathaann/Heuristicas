#include <stdio.h>
#include "grasp_funcoes.c"


int main(){
    celula *itens = NULL;  // lista que ira armazenar todos os itens de entrada
    celula *solucao = NULL;  // lista que vai conter todos os itens que fazem parte da solucao 
    FILE *pt_arq = fopen("r_100_25_1.txt", "r");
    FILE *valores_itens = fopen("valores_itens.txt", "r");
    FILE *peso_itens = fopen("peso_itens.txt", "r");

    if(pt_arq == NULL || valores_itens == NULL || peso_itens == NULL){
        printf("Erro ao abrir um dos (ou mais) arquivos de entrada!\n");
        return 1;
    }

    char referencia_instancia[20];
    int max_iteracoes = 0;
    int capacidade, quant_item, valor, peso;

    // lendo a referencia da instacnia
    fscanf(pt_arq, "%s", referencia_instancia);
    printf("Arquivo: %s\n", referencia_instancia); 
    
    

    // lendo o numero de itens
    fscanf(pt_arq, "%d", &quant_item);
    //fscanf(pt_arq, "%d", &capacidade);
    



    //printf("%d\n", capacidade);
    // leitura dos itens (seu valor e seu peso)
    for(int i = 0; i < quant_item; i++){

        fscanf(valores_itens, "%d", &valor);
        fscanf(peso_itens, "%d", &peso);
        //fscanf(pt_arq, "%d", &aux);
       // printf("%d ", aux);
       // printf("item %d valor: %d peso: %d\n", i+1, valor, peso);

        insercao(i+1, peso, valor, &itens);
    }

    // cada item x pode formar par com no maximo outros n-1 itens (considerando que temos ao todo n itens)
    // ent, para cada item, eh necessario alocar dois vetores, um para guardar todos os itens que forma bonus com o item x
    // e outro vetor que ira guardar
   
    // alocando o vetor
    printf("lista de todos os itens na main:\n");
    imprimir(itens);
    for(int i = 0; i < max_iteracoes; i++){
        contrucao_gulosa_randomizada(itens, &solucao, capacidade, 1);

        // busca local que 

        // 

        // antes desse laço rodar mais uma vez eu preciso "zerar" a lista "solucao"

        //apaga_lista(&solucao);
    }

    //imprimir(itens);
   //imprimir(solucao);
   //printf("Valor da solucao: %d\n", calcula_solucao(solucao));

    fclose(pt_arq);

    return 0;

    
}
