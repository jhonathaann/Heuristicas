#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROFESSORES 4
#define DISCIPLINAS 5
#define ALPHA 0.3    // controla a aleatoriedade

// matriz de adjacencia representando o grafo (esse grafo é o modelo do problema)
// G[p][d] = 0 --> o professor p NAO pode ministrar a disciplina d
// G[p][d] > 0 --> o professor p PODE ministrar a disciplina d. e esse valor representa a prioridade
int G[PROFESSORES][DISCIPLINAS] = {
    {10, 5, 0, 7, 4},
    {2, 9, 8, 0, 7},
    {0, 6, 10, 8, 5},
    {7, 0, 5, 9, 10}
    //{3, 4, 7, 0}
};

typedef struct{
    int professor, prioridade;
}Alocacao;

void iniciar_alocacao(Alocacao *instancia);

// funcao para construir uma solucao inicial (gulosa + aleatoria)
void fase_construtiva(Alocacao *instancia);

void imprimir(Alocacao *instancia);

int main(){
    srand(time(NULL));

    Alocacao instancia[DISCIPLINAS];

    iniciar_alocacao(instancia);

    fase_construtiva(instancia);

    imprimir(instancia);
}

void iniciar_alocacao(Alocacao *instancia){
    // alocando com base na quantidade de disciplinas
    // ou seja, a posicao d do vetor instancia contem o professor que foi alocado para a disciplina d, e a sua prioridade
    for(int d = 0; d < DISCIPLINAS; d++){
        instancia[d].professor = -1;
        instancia[d].prioridade = -1;
    }
}

void fase_construtiva(Alocacao *instancia){

    for(int d = 0; d < DISCIPLINAS; d++){

        int max_prioridade = -1, min_prioridade = 11;

        for(int p = 0; p < PROFESSORES; p++){
            // vefificando se o professor p pode ministrar a disciplina d
            if(G[p][d] > 0){
                // verificando agora as prioridades
                if(G[p][d] > max_prioridade){
                    max_prioridade = G[p][d];
                }

                if(G[p][d] < min_prioridade){
                    min_prioridade = G[p][d];
                }
            }

        }

        int limite = min_prioridade + ALPHA * (max_prioridade - min_prioridade);
        int candidatos[PROFESSORES]; // lista de candidatos
        int aux = 0;

        // criando de fato a lista de candidatos
        for(int p = 0; p < PROFESSORES; p++){
            if(G[p][d] >= limite){
                candidatos[aux] = p;
                aux++;
            }
        }

        if(aux > 0){
            // escolhendo um aleatorio da lista de candidatos
            int escolhido = candidatos[rand() % aux];
            instancia[d].professor = escolhido;
            instancia[d].prioridade = G[escolhido][d];
        }
    }
}

void imprimir(Alocacao *instancia) {
    printf("alocacao das disciplinas:\n");
    for (int d = 0; d < DISCIPLINAS; d++) {
        printf("disciplina %d -> professor %d (prioridade %d)\n", d+1, instancia[d].professor+1, instancia[d].prioridade);
    }
}