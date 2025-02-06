// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** structure for each item */
typedef struct
{
   int label;  //  rotulo do item
   int value;  // valor do item
   int weight; // peso do item
} itemType;

// struct para guardar uma solucao
typedef struct
{
   int label, mochila
}solucao;

void min_max(itemType *candidatos, int n, int *max, int *min);

void cria_RCL(itemType *candidatos, itemType *RCL, int minimo, int maximo, int alpha, int n, int *n_RCL);

int numero_aleatorio(int n_cand);

void atualiza_candidatos(itemType *candidatos, int rotulo, int *n_cand, int capacidade_atual);

int verifica_solucao(solucao *itens_solucao, int label, int n);

int main()
{
   srand(time(NULL));
   itemType *candidatos, *RCL;
   itemType *item;
   solucao *itens_solucao;
   int n, m;   // n = quant itens. m = quant mochilas
   int max_iteracoes, maximo, minimo, alpha = 0, n_cand = 0;
   int posicao_item_escolhido, n_RCL = 0, custo = 0;
   int *C;
   int rotulo;
   int n_solucao = 0;

   FILE *arquivo = fopen("C:/Users/jhona/OneDrive/Faculdade/LEXA/IC/Grasp/texte.txt", "r");
   if (!arquivo)
   {
      printf("Erro ao abrir o arquivo\n");
      return 1;
   }

   fscanf(arquivo, "%d %d\n", &n, &m);

   // alocando o vetor das mochilas
   C = (int *)malloc(sizeof(int) * m);

   for (int i = 0; i < m; i++)
   {
      // lendo as capacidades de cada mochila
      fscanf(arquivo, "%d\n", &C[i]);
   }

   // alocando o vetor dos itens
   item = (itemType *)malloc(sizeof(itemType) * n);

   for(int i=0; i<n; i++){
    // lendo o nome, o valor e o peso de cada item
     fscanf(arquivo, "%d %d %d\n", &item[i].label, &item[i].weight, &item[i].value);
   }

   /*printf("CAPACIDADE DAS MOCHILAS:\n");
   for(int i = 0; i < m; i++){
      printf("%d ", C[i]);
   }
   printf("\n");

   printf("ITENS:\n");
   for(int i = 0; i < n; i++){
      printf("%d %d %d\n", item[i].label,item[i].weight ,item[i].value);
   }
   printf("\n");*/
   fclose(arquivo);



   // alocando o vetor de itens que foram colocados na solucao
   itens_solucao = (solucao *) malloc(sizeof(solucao)*n);
   
   max_iteracoes = m;  // quant de iteracoes sera no momento a quantidade de mochilas da instancia
   for (int i = 0; i < max_iteracoes; i++)
   {
      printf("\nMOCHILA %d\n", i+1);
      /*printf("SOLUCAO ATE O MOMENTO:\n");
      for(int i = 0; i < n_solucao; i++){
         printf("%d ", itens_solucao[i]);
      }
      printf("\n");*/
      // alocando o vetor de candidatos
      candidatos = (itemType *)malloc(sizeof(itemType) * n);

      for (int j = 0; j < n; j++){
         // colocando no vetor candidatos todos os itens que tem peso <= capacidade da mochila i E que nao foram colocados ainda na solucao
         if (item[j].weight <= C[i] && (verifica_solucao(itens_solucao, item[j].label, n_solucao) == 0))
         {
            candidatos[n_cand].label = item[j].label; // assim?
            candidatos[n_cand].weight = item[j].weight;
            candidatos[n_cand].value = item[j].value;
            n_cand++;
         }
      }
      /*printf("TAMANHO DO VETOR CANDIDATOS: %d\n", n_cand);
      printf("LISTA DE CANDIDATOS:\n");*/
     
      for(int i = 0; i < n_cand; i++){
         printf("%d %d %d\n", candidatos[i].label,candidatos[i].weight ,candidatos[i].value);
      }


      int capacidade_atual = C[i];

      //printf("CAPACIDADE DA MOCHILA %d: %d\n", i+1, capacidade_atual);

      while (capacidade_atual > 0.0 && n_cand >= 1)
      {

         // maximo e o minimo de candidatos[i];
         min_max(candidatos, n_cand, &maximo, &minimo);
         printf("maximo: %d, minimo: %d\n", maximo, minimo);

         printf("LSIAT DE CANDIDATOS ANTES DE EU CRIAR A RCL:\n");
         for(int i = 0; i < n_cand; i++){
            printf("%d %d %d\n", candidatos[i].label,candidatos[i].weight ,candidatos[i].value);
         }
         // cria a RCL
         RCL = (itemType *)malloc(sizeof(itemType) * n);
         n_RCL = 0;  // tamanho da RCL tem que ser 0
         cria_RCL(candidatos, RCL, minimo, maximo, alpha, n_cand, &n_RCL);
        

         printf("RCL: (tamanho = %d)\n", n_RCL);
         for(int i = 0; i < n_RCL; i++){
            printf("%d %d %d\n", RCL[i].label,RCL[i].weight ,RCL[i].value);
         }

         // escolhe um item aleatorio da RCL
         posicao_item_escolhido = numero_aleatorio(n_RCL);
         rotulo = RCL[posicao_item_escolhido].label;  // pegando o rotulo do item escolhido para conseguir remover ele no candidatos

         //printf("ITEM ESCOLHIDO DA RCL: %d\n", RCL[posicao_item_escolhido].label);

         // atualzia o custo e diminui a capacidade atual da mochila
         custo += RCL[posicao_item_escolhido].value;
        // printf("PESO DO ITEM ESCOLHIDO: %d\n", RCL[posicao_item_escolhido].weight);
         capacidade_atual -= RCL[posicao_item_escolhido].weight;
         itens_solucao[n_solucao].label = RCL[posicao_item_escolhido].label;
         itens_solucao[n_solucao].mochila = i+1;
         /*itens_solucao[n_solucao].label = RCL[posicao_item_escolhido].label;
         itens_solucao[n_solucao].weight = RCL[posicao_item_escolhido].weight;
         itens_solucao[n_solucao].value = RCL[posicao_item_escolhido].value;*/
         n_solucao++;
         printf("MOCHILA %d\n", i+1);

         // atualizar a lista de candidatos
        // printf("CAPACIDADE ATUAL DA MOCHILA %d: %d\n", i+1, capacidade_atual);
         atualiza_candidatos(candidatos, rotulo, &n_cand, capacidade_atual);

         // apagando a RCL
         free(RCL);
   

        // printf("custo: %d\n", custo);
      }

      free(candidatos);
   }

   printf("SOLUCAO FINAL:\n");
   for(int i = 0; i < n_solucao; i++){
         printf("ITEM: %d; MOCHILA: %d\n", itens_solucao[i].label, itens_solucao[i].mochila);
      }

   printf("\ncusto: %d\n", custo);
   return 0;
}

void min_max(itemType *candidatos, int n, int *max, int *min)
{
   *max = candidatos[0].value;
   *min = candidatos[0].value;
   //printf("TESTE MAXIMO E MINIMO: %d, %d\n", *max, *min);

   for (int i = 1; i < n; i++)
   {
      if (candidatos[i].value >= *max)
      {
         *max = candidatos[i].value;
      }

      if (candidatos[i].value <= *min)
      {
         
         *min = candidatos[i].value;
      }
   }
   //printf("TESTECU MAXIMO E MINIMO: %d, %d\n", *max, *min);
}

void cria_RCL(itemType *candidatos, itemType *RCL, int minimo, int maximo, int alpha, int n, int *n_RCL)
{

   for (int i = 0; i < n; i++)
   {
      //printf("teste1\n");
      if (candidatos[i].value >= minimo + alpha * (maximo - minimo))
      {
        //printf("teste 2 RCL. %d\n", *n_RCL);
         RCL[*n_RCL].label = candidatos[i].label;
         RCL[*n_RCL].weight = candidatos[i].weight;
         RCL[*n_RCL].value = candidatos[i].value;
         (*n_RCL) += 1;
         //printf("teste 3 RCL. %d\n", *n_RCL);
      }
   }
}

int numero_aleatorio(int n_cand)
{
   return rand() % n_cand;
}

void atualiza_candidatos(itemType *candidatos, int rotulo, int *n_cand, int capacidade_atual)
{
   /*printf("LISTA DE CANDIDATOS ANTES DA ATUALIZACAO:\n");
   for(int i = 0; i < *n_cand; i++){
      printf("%d %d %d\n", candidatos[i].label,candidatos[i].weight ,candidatos[i].value);
   }*/

   // 1° "remover" o item que foi escolhido
   for(int i = 0; i < *n_cand; i++){
      if(candidatos[i].label == rotulo){
         candidatos[i] = candidatos[--(*n_cand)];
      }
   }
   /* 1° "remover" o item que foi escolhido
   candidatos[posicao_item_escolhido] = candidatos[--(*n_cand)]; // coloco o ultimo na posicao do item escolhido e diminuo a quant de itens*/

   /*printf("LISTA DEPOIS DA PRIMEIRA ATUALIZACAO:\n");
   if(*n_cand == 0){
      printf("LISTA DE CANDIDATOS VAZIA\n");
   }
   for(int i = 0; i < *n_cand; i++){
      printf("%d %d %d\n", candidatos[i].label,candidatos[i].weight ,candidatos[i].value);
   }*/


   // removendo da lista todos os itens que possuem peso > capacidade atual da mochila
   for (int i = 0; i < *n_cand; i++)
   {

      // se isso acontecer, eu preciso remover esse item
      if (candidatos[i].weight > capacidade_atual)
      {

         while (candidatos[(*n_cand) - 1].weight > capacidade_atual && *n_cand > i)
         {
            (*n_cand) -= 1;
         }

         if (*n_cand > i)
         {
            candidatos[i] = candidatos[--(*n_cand)];
         }
      }
   }

   /*printf("LISTA DEPOIS DA ULTIMA ATUALIZACAO:\n");
   if(*n_cand == 0){
      printf("LISTA DE CANDIDATOS VAZIA\n");
   }
   for(int i = 0; i < *n_cand; i++){
      printf("%d %d %d\n", candidatos[i].label,candidatos[i].weight ,candidatos[i].value);
   }*/
}

int verifica_solucao(solucao *itens_solucao, int label, int n){

   // solucao ainda esta vazia
   if(n == 0){
      return 0;
   }else{
      for(int i = 0; i < n; i++){
         if(itens_solucao[i].label == label){
            // esse item ja esta na solucao
            return 1;
         }
      }
   }

   return 0;  // esse item nao foi colacado em nenhuma outra mochila

}