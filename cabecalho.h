#ifndef CABECALHO_H
#define CABECALHO_H

// fase de contrucao da solucao
void contrucao_gulosa_randomizada(celula *itens, celula **solucao, float capacidade_mochila, float alpha);

// cria lista de candidatos (aqules que cabem na mochila)
void cria_lista_candidatos(celula *itens, celula **candidatos, float capacidade);

// cria a lista de candidatos restritos (RCL)
void cria_RCL(celula **RCL, celula **candidatos, float maximo, float minimo, float alpha);

// atualiza a lista de candidatos
void atualiza_candidatos(celula **candidatos, float capacidade_atual);

// escolhe aleatoriamente um item da RCL
celula* escolha_aleatoria(celula *RCL);

// gera um numero aleatorio entre x e y
int random_number(int x, int y);

// achar o maior valor da lista
float max(celula *lista);

// acha o menor valor da lista
float min(celula *lista);

// conta quantos itens tem na lista
int quantidadeItens(celula *inicio);

// inserir um item na lista
void insercao(int item, float peso, float valor, celula **solucao);

// remove um item da lista
void remocao(celula **candidatos, int item);

#endif