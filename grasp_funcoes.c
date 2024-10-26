#include "cabecalho.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// fase de construcao da solucao
void contrucao_gulosa_randomizada(celula *itens, celula **solucao, int capacidade_mochila, float alpha){
    // RCL
    celula *RCL = NULL;
    
    // criando a lista de todos os candidatos possiveis (aqueles que cabem na mochila)
    celula *candidatos = NULL;

    printf("lista de todos os itens:\n");
    //imprimir(itens);
    cria_lista_candidatos(itens, &candidatos, capacidade_mochila);
    printf("lista de candidatos\n");
    //imprimir(candidatos);

    int capacidade_atual = capacidade_mochila,  maximo, minimo;
    printf("%d\n", capacidade_atual);
    
    // enquanto a mochila ainda estiver com capacidade E a lista de candidatos NAO estiver vazia
    while(capacidade_atual > 0.0 && candidatos != NULL){
        maximo = max(candidatos);   // pegando o valor maximo da lista de candidatos
        minimo =  min(candidatos);  // pegando o valor minimo da lista de candidatos
        //printf("teste1\n");

        printf("maximo: %d; minimo: %d\n", maximo, minimo);
        
        // criando a RCL
        cria_RCL(&RCL, &candidatos, maximo, minimo, alpha);

        //imprimir(RCL);

       // printf("teste2\n");

        // selecionando um item aleatorio da RCL
        celula *aux = escolha_aleatoria(RCL);

       // printf("teste3\n");

        // coloco na solucao o item escolhido aleatoriamente na RCL
        insercao(aux->item, aux->peso, aux->valor, *&solucao);  
        printf("CAPACIDADE ATUAL: %d\n", capacidade_atual);
        capacidade_atual -= aux->peso;

        //printf("teste4\n");

        // atualizando a lista de candidatos

        // 1°: removo da lista de candidatos o item que estava na RCL e que foi colocado na solucao
        remocao(&candidatos, aux->item); 

       // printf("teste4\n");

        //2°: removo da lista de candidatos todos os itens que tem peso > que a capacidade atual da mochila
        atualiza_candidatos(&candidatos, capacidade_atual);

        apaga_lista(&RCL);

       // printf("teste5\n");


    }

}

// lista de candidatos deve conter todos os itens que tem peso <= capacidade atual da mochila
void cria_lista_candidatos(celula *itens, celula **candidatos, int capacidade){

    while(itens != NULL){
        if(itens->peso <= capacidade){
            insercao(itens->item, itens->peso, itens->valor, *&candidatos);
        }

        itens = itens->proximo;
    }
}

// RCL deve conter apenas os itens cujo valor é >= minimo + alpha * (maximo - minimo))
void cria_RCL(celula **RCL, celula **candidatos, int maximo, int minimo, float alpha){
    celula *aux = *candidatos;

    while(aux != NULL){

        if(aux->valor >= minimo + alpha * (maximo - minimo)){
            // insiro o valor na lista de candidatos restritos
            insercao(aux->item, aux->peso, aux->valor, *&RCL);

            // remove o item inserido da lista de candidatos
            // acho que eh apenas o item que eu selecionei aleatoriamente dela
            //remocao(&candidatos, (*candidatos)->item);
        }

        aux = aux->proximo;
    }

}

// remove da lista de candidatos todos os itens que tem peso > que a capacidade atual da mochila
void atualiza_candidatos(celula **candidatos, int capacidade_atual){
    celula *aux = *candidatos;

    while(aux != NULL){

        if(aux->peso > capacidade_atual){
            remocao(*&candidatos, aux->item);
        }

        aux = aux->proximo;
    }
}

// escolhe um item aleatorio da RCL e retorna a celula em que ele se encontra
celula* escolha_aleatoria(celula *RCL){
    srand(time(NULL));

    int random = random_number(1, quantidadeItens(RCL));

    //printf("numero random: %d E quantidade de itens: %d\n", random, quantidadeItens(RCL));

    for(int i = 1; i < random; i++){
        RCL = RCL->proximo;
    }

    return RCL;
}

int calcula_solucao(celula *solucao){
    int valor = 0;

    while(solucao != NULL){
        valor += solucao->valor;
        solucao = solucao->proximo;
    }

    return valor;
}

int random_number(int x, int y) {
    return x + rand() % (y - x + 1);
}


int max(celula *lista){
    float maximo = lista->valor;

    while(lista != NULL){
        if(lista->valor > maximo){
            maximo = lista->valor;
        }

        lista = lista->proximo;
    }

    return maximo;
}

int min(celula *lista){
    float minimo = lista->valor;

    while(lista != NULL){
        if(lista->valor < minimo){
            minimo = lista->valor;
        }

        lista = lista->proximo;
    }

    return minimo;
}

// insercao no final
void insercao(int item, int peso, int valor, celula **solucao){

    celula *nova = (celula *) malloc(sizeof(celula));  // criando a nova celula
    celula *aux;
    if(nova ==  NULL){
        printf("Erro ao alocar memoria na funcao insercao!!\n");
        return;
    }

    nova->item = item;
    nova->peso = peso;
    nova->valor = valor;
    nova->proximo = NULL;

    if(*solucao == NULL){
        *solucao = nova;
    }else{
        aux = *solucao;

        while(aux->proximo != NULL){
            aux = aux->proximo;
        }

        aux->proximo = nova;
    }

}


void remocao(celula **candidatos, int item){
    celula *aux;

    if(*candidatos != NULL){
        
        if((*candidatos)->item == item){
            aux = *candidatos;
            *candidatos = (*candidatos)->proximo;
            free(aux);

        }else{
            aux = *candidatos;
            
            while(aux->proximo != NULL && aux->proximo->item != item){
                aux = aux->proximo;
            }

            if(aux->proximo != NULL){
                celula *temp = aux->proximo;
                aux->proximo = temp->proximo;
                free(temp);
            }
        }
    }
}

void apaga_lista(celula **lista){

    while(*lista != NULL){
        remocao(*&lista, (*lista)->item);

        // *&lista = lista
        // o operador & seguido de * (ou o contrario) eh a mesma coisa que nao colocar nada SUS
        //(*lista) = (*lista)->proximo;
    }
}

int quantidadeItens(celula *inicio) {
    int contador = 0;
    celula *atual = inicio;
    
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    
    return contador;
}

void imprimir(celula *lista, int n){
    celula *aux = lista;
    int i = 0;

    if(lista == NULL){
        printf("lista vazia\n");
    }
    while(lista != NULL){
        printf("Item: %d, Valor: %d, Peso: %d\n", lista->item, lista->valor, lista->peso);

        for(int j = 0; j < n - i - 1; j++){
            printf("%d ", aux->bonus_i[j]);

        }
        lista = lista->proximo;
        i++;
        printf("\n");
    }



    printf("fim\n");
}