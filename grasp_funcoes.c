#include "cabecalho.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// fase de construcao da solucao
void contrucao_gulosa_randomizada(celula *itens, celula **solucao, float capacidade_mochila, float alpha){
    // RCL
    celula *RCL;
    
    // criando a lista de todos os candidatos possiveis (aqueles que cabem na mochila)
    celula *candidatos = NULL;
    cria_lista_candidatos(itens, &candidatos, capacidade_mochila);

    float capacidade_atual = capacidade_mochila;
    float maximo, minimo;
    

    while(capacidade_atual > 0.0){
        maximo = max(candidatos);   // pegando o valor maximo da lista de candidatos
        minimo =  min(candidatos);  // pegando o valor minimo da lista de candidatos
        
        // criando a RCL
        cria_RCL(&RCL, candidatos, maximo, minimo, alpha);

        // selecionando um item aleatorio da RCL
        celula *aux = escolha_aleatoria(RCL);

        // coloco na solucao o item escolhido aleatoriamente na RCL
        insercao(aux->item, aux->peso, aux->valor, &solucao);  
        capacidade_atual -= aux->peso;

        // atualizando a lista de candidatos

        // 1°: removo da lista de candidatos o item que estava na RCL e que foi colocado na solucao
        remocao(&candidatos, aux->item); 

        //2°: removo da lista de candidatos todos os itens que tem peso > que a capacidade atual da mochila
        atualiza_candidatos(&candidatos, capacidade_atual);


    }

}

// lista de candidatos deve conter todos os itens que tem peso <= capacidade atual da mochila
void cria_lista_candidatos(celula *itens, celula **candidatos,  float capacidade){

    while(itens != NULL){
        if(itens->peso <= capacidade){
            insercao(itens->item, itens->peso, itens->valor, &candidatos);
        }

        itens = itens->proximo;
    }
}

// RCL deve conter apenas os itens cujo valor é >= minimo + alpha * (maximo - minimo))
void cria_RCL(celula **RCL, celula **candidatos, float maximo, float minimo, float alpha){
    celula *aux = *candidatos;

    while(aux != NULL){

        if(aux->valor >= minimo + alpha * (maximo - minimo)){
            // insiro o valor na lista de candidatos restritos
            insercao(aux->item, aux->peso, aux->valor, &RCL);

            // remove o item inserido da lista de candidatos
            // acho que eh apenas o item que eu selecionei aleatoriamente dela
            //remocao(&candidatos, (*candidatos)->item);
        }

        aux = aux->proximo;
    }

}

// remove da lista de candidatos todos os itens que tem peso > que a capacidade atual da mochila
void atualiza_candidatos(celula **candidatos, float capacidade_atual){
    celula *aux = *candidatos;

    while(aux != NULL){

        if(aux->peso > capacidade_atual){
            remocao(&candidatos, aux->item);
        }

        aux = aux->proximo;
    }
}

// escolhe um item aleatorio da RCL e retorna a celula em que ele se encontra
celula* escolha_aleatoria(celula *RCL){
    srand(time(NULL));

    int random = random_number(1, quantidadeItens(RCL));

    for(int i = 1; i < random; i++){
        RCL = RCL->proximo;
    }

    return RCL;
}

float valor_solucao(celula *solucao){
    float valor = 0.0;

    while(solucao != NULL){
        valor += solucao->valor;
        solucao = solucao->proximo;
    }

    return valor;
}

int random_number(int x, int y) {
    return x + rand() % (y - x + 1);
}


float max(celula *lista){
    float maximo = lista->valor;

    while(lista != NULL){
        if(lista->valor > maximo){
            maximo = lista->valor;
        }

        lista = lista->proximo;
    }

    return maximo;
}

float min(celula *lista){
    float minimo = lista->valor;

    while(lista != NULL){
        if(lista->valor < minimo){
            minimo = lista->valor;
        }

        lista = lista->proximo;
    }

    return minimo;
}


void insercao(int item, float peso, float valor, celula **solucao){

    celula *nova = (celula *) malloc(sizeof(celula));  // criando a nova celula

    if(nova ==  NULL){
        printf("Erro ao alocar memoria na funcao insercao!!\n");
        return;
    }

    nova->item = item;
    nova->peso = peso;
    nova->valor = valor;

    // faz a nova celula apontar para o topo da lista anterior
    nova->proximo = *solucao;

    *solucao = nova;  // atualiza o topo da lista anterior

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

int quantidadeItens(celula *inicio) {
    int contador = 0;
    celula *atual = inicio;
    
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    
    return contador;
}