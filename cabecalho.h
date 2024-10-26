#ifndef CABECALHO_H
#define CABECALHO_H

// struct para representar um item
typedef struct cel{
    int item, peso, valor;
    int *bonus_i;    // esse vetor ira conter todos os bonus que existem com o item i
    struct cel *proximo;
}celula;

// sobre o vetor *bonus_i: se eu estiver no item i, o vetor em questao vai ter tamanho n-i-1
// e com quem sera o bonus sera da seguinte forma: bonus_i[x] sera o bonus do item i com o item j
// j = x+i+1. nos laços, tenho que inicializar o i=1


// fase de contrucao da solucao
void contrucao_gulosa_randomizada(celula *itens, celula **solucao, int capacidade_mochila, float alpha);

// cria lista de candidatos (aqules que cabem na mochila)
void cria_lista_candidatos(celula *itens, celula **candidatos, int capacidade);

// cria a lista de candidatos restritos (RCL)
void cria_RCL(celula **RCL, celula **candidatos,  int maximo, int minimo, float alpha);

// atualiza a lista de candidatos
void atualiza_candidatos(celula **candidatos, int capacidade_atual);

// calcula o valor da solucao (sem considerar os bonus)
int calcula_solucao(celula *solucao);

// escolhe aleatoriamente um item da RCL
celula* escolha_aleatoria(celula *RCL);

// calcula o valor da solucao
float valor_solucao(celula *solucao);

// gera um numero aleatorio entre x e y
int random_number(int x, int y);

// achar o maior valor da lista
int max(celula *lista);

// acha o menor valor da lista
int min(celula *lista);

// conta quantos itens tem na lista
int quantidadeItens(celula *inicio);

// inserir um item na lista
void insercao(int item, int peso, int valor, celula **solucao);

// remove um item da lista
void remocao(celula **candidatos, int item);

// remove todos os itens da lista
void apaga_lista(celula **lista);

void imprimir(celula *lista, int n);

#endif