#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* o objetivo final eh maximizar a satisfaçao dos professores? se sim, isso se da alocando cada professor
/ para a disciplina que ele deu maior prioridade? isso pode acabar ajudando uns e outros nao, eu acho*/ 

#define PROFESSORES 4
#define DISCIPLINAS 5
#define ALPHA 0.3    // controla a aleatoriedade

// matriz de adjacencia representando o grafo (esse grafo é o modelo do problema)
// G[p][d] = 0 --> o professor p NAO pode ministrar a disciplina d
// G[p][d] > 0 --> o professor p PODE ministrar a disciplina d. e esse valor representa a prioridade
typedef struct
{
    int G[PROFESSORES][DISCIPLINAS];  // grafo que ira armazenar a relacao entre professores e disciplinas
    int *carga_horaria;  // vetor que ira armazenar a carga horaria semanal de cada disciplina

}Disciplinas;

typedef struct{
    int professor, prioridade, carga_horaria_prof;
}Alocacao;

typedef struct
{
    int disciplina, prioridade;
}Candidatos;


void min_max(Candidatos *candidatos, int n_cand, int *max, int *min);

void iniciar_alocacao(Alocacao *alocacao);

// funcao para construir uma solucao inicial (gulosa + aleatoria)
//void fase_construtiva(Alocacao *alocacao);

void imprimir(Alocacao *alocacao);

void cria_RCL(Candidatos *RCL, Candidatos *candidatos, int maximo, int minimo, int n_cand, int *n_RCL);

void atualiza_candidatos(Candidatos *candidatos, int *n_cand, int disciplina); // por enquanto essa atualizacao eh so para tirar a disciplina que foi escolhida

void criando_grafo(Disciplinas *d);

int numero_aleatorio(int n_RCL);

int main(){
    srand(time(NULL));
    Alocacao alocacao[DISCIPLINAS];
    Disciplinas disc;
    Candidatos *candidatos, *RCL;

    int n_cand, n_RCL, maximo, minimo;
    int max_iteracoes, carga_atual, posicao_escolhida;
    //int solucao = -1;  // essa variavel ira armazenar a soma das satisfacoes dos professores

    // alocando o vetor da carga horaria
    disc.carga_horaria = (int *) malloc(sizeof(int) * DISCIPLINAS);

    criando_grafo(&disc);  // armazenando na matriz a relacao entre os professores e as disciplinas, bem como a carga horaria das disciplinas

    /*printf("imprimindo a carga horaria das disciplinas:\n");
    for(int i = 0; i < DISCIPLINAS; i++){
        printf("disciplina %d possui carga horaria de %dhrs semanais\n",i+1,  d.carga_horaria[i]);
    }*/
   
    iniciar_alocacao(alocacao);

    int p = 0; // no começo, eu estou no professor p
    max_iteracoes = 3;
    for(int i = 0; i < max_iteracoes; i++){

        // os candidatos vao ser os as disciplinas que o professor p pode ministrar
        candidatos = (Candidatos *) malloc(sizeof(Candidatos) * DISCIPLINAS);

        // pegando a carga horaria que o professor p deve cumprir
        carga_atual = alocacao[p].carga_horaria_prof;
        //printf("carga horaria do professor 1: %d\n", carga_atual);

        // ==== CRIANDO A LISTA DE CANDIDATOS DO PROFESSOR P
        
        // para entrar na lista duas coisas devem ser atendidas: o professor pode ministrar essa disciplina
        // E ela nao pode ter sido alocado para nenhum outro professor ate ent
        n_cand = 0;
        for(int d = 0; d < DISCIPLINAS; d++){
            // vou fazer por enquanto so a primeira restricao
            if(disc.G[p][d] > 0){
                candidatos[n_cand].prioridade = disc.G[p][d];
                candidatos[n_cand].disciplina = d;   // guardo de fato a disciplina, e nao o interesse que o professor p tem pela disciplina d
                n_cand++;
               // printf("%d ", disc.G[p][d]);
            }
        }
        printf("\ntamanho da lista de candidatos para o professor %d: %d \n", p+1, n_cand);
        printf("todos os candidatos (disciplinas) que podem ser ministradas pelo professor %d:\n", p+1);
        for(int i = 0; i < n_cand; i++){
            printf("Disciplina: %d E prioridade: %d\n", candidatos[i].disciplina, candidatos[i].prioridade);
        }

        
        //enquanto o professor p nao fechou a sua carga horaria E a sua lista de candidatos existe (ou seja, ainda tem disciplinas que ele pode ministrar)
        while(carga_atual > 0 && n_cand >= 1){
            min_max(candidatos, n_cand, &maximo, &minimo);

            printf("\nMAXMIMO %d E MINIMO %d\n", maximo, minimo);

            // criando a RCL
            RCL = (Candidatos *) malloc(sizeof(Candidatos) * n_cand);
            n_RCL = 0;
            cria_RCL(RCL, candidatos, maximo, minimo, n_cand, &n_RCL);
            printf("Tamanho da RCL: %d\nRCL:\n", n_RCL);
            for(int i = 0; i < n_RCL; i++){
                printf("Disciplina: %d E prioridade: %d\n", RCL[i].disciplina, RCL[i].prioridade);
            }

           posicao_escolhida = numero_aleatorio(n_RCL);  // esse numero retornado vai ser a disciplina que vai ser alocada para o professor p
           printf("Numero escolhido pela funcao aleatoria: %d\n", posicao_escolhida);
           alocacao[RCL[posicao_escolhida].disciplina].professor = p;  // colocando na disciplina que foi escolhida o professor p
           alocacao[RCL[posicao_escolhida].disciplina].prioridade = RCL[posicao_escolhida].prioridade;  // colocando na disciplina que foi escolhida a prioridade que o professor escolhido possui nela

            // printando o vetor de alocacao para ver como esta a solucao ate o momento
            printf("disciplina alocada para o professor %d: %d\n", p+1,RCL[posicao_escolhida].disciplina);
            printf("Carga horaria atual do professor %d: %d\n", p+1, carga_atual);
            carga_atual -= disc.carga_horaria[RCL[posicao_escolhida].disciplina];
            printf("Carga horaria atual do professor %d: %d\n", p+1, carga_atual);

            atualiza_candidatos(candidatos, &n_cand, RCL[posicao_escolhida].disciplina);

            free(RCL);

            //imprimir(alocacao);
            printf("\n====== FIM DE UMA ITERACAO!! ========\n");
        } 

        free(candidatos);

        p++;

    }

   imprimir(alocacao);
}

void iniciar_alocacao(Alocacao *alocacao){
    // alocando com base na quantidade de disciplinas
    // ou seja, a posicao d do vetor alocacao contem o professor que foi alocado para a disciplina d, e a sua prioridade
    for(int d = 0; d < DISCIPLINAS; d++){
        alocacao[d].professor = -1;
        alocacao[d].prioridade = -1;
        alocacao[d].carga_horaria_prof = 20;  // um prof deve cumprir pelo menos 20 horas semanais
        // depois eu posso tentar colocar uma carga horaria maxima, pra servir de limitante superior

    }
}

/*void fase_construtiva(Alocacao *alocacao){

    // eu crio uma lista de candidatos para cada professor p: e ela vai conter todas as disciplinas que o professor p pode ministrar
    // dai eu vou ter uma RCL para cada professor, de modo que na RCL vai ter apenas as disciplinas que atendem aquela expressao de min + alpha (max - min)
    // dai vc escolhe uma discipla da RCL e aloca ela para o professor p e diminui do professor p a carga horaria que essa disciplina tem
    // ai o laço pode ser enquanto (carga_horaria > 0 E candidados != null)
    //
    // eu nao posso alocar a mesma disciplina/turma para dois professores diferentes, ent eu tenho que verificar no momento em que for criar a lista de candidatos
    // se aquela disciplina que ele pode ministrar ja nao foi alocada

    // do jeito que esta me parece ter grandes chances de pelo menos um professor ficar sem uma disciplina (o que nao pode). isso porconta da aleatoriedade e tals
    // ent, pra tentar corrigir esse possivel problema, ao final da solucao que o grasp gerou eu irei verificar se todos os professores possuem pelo menos uma disciplina
    // se nao, eu tento alocar para aqueles que ficaram sem (olho se tem alguma disciplina que ele pode ministrar que ainda esta livre)
    // se mesmo assim alguns ficarem sem, eu aborto ela solucao e começo tudo denovo
}*/

void criando_grafo(Disciplinas *d){
    int valores[PROFESSORES][DISCIPLINAS] = {
        {10, 5, 0, 7, 4},
        {2, 9, 8, 0, 7},
        {0, 6, 10, 8, 5},
        {4, 0, 5, 9, 10}
    };

    // copiando os valores para a matriz dentro da struct
    for(int i = 0; i < PROFESSORES; i++){
        for(int j = 0; j < DISCIPLINAS; j++){
            d->G[i][j] = valores[i][j];
        }
    }

    // salvando as informacoes da carga horaria das disciplinas
    for(int i = 0; i < DISCIPLINAS; i++){
        d->carga_horaria[i] = 10;   // 10 horas cada disciplina ira exigir
    }
}

int numero_aleatorio(int n_RCL){
    //srand(time(NULL));
    return rand() % n_RCL;
}

void min_max(Candidatos *candidatos, int n_cand, int *max, int *min) {
    if (n_cand == 1) {
        *max = candidatos[0].prioridade;
        *min = candidatos[0].prioridade;
        return;
    }

    if (candidatos[0].prioridade < candidatos[1].prioridade) {
        *min = candidatos[0].prioridade;
        *max = candidatos[1].prioridade;
    } else {
        *min = candidatos[1].prioridade;
        *max = candidatos[0].prioridade;
    }

    for (int i = 2; i < n_cand - 1; i += 2) {
        if (candidatos[i].prioridade < candidatos[i + 1].prioridade) {
            if (candidatos[i].prioridade < *min) {
                *min = candidatos[i].prioridade;
            }
            if (candidatos[i + 1].prioridade > *max) {
                *max = candidatos[i + 1].prioridade;
            }
        } else {
            if (candidatos[i].prioridade > *max) {
                *max = candidatos[i].prioridade;
            }
            if (candidatos[i + 1].prioridade < *min) {
                *min = candidatos[i + 1].prioridade;
            }
        }
    }
    if (n_cand % 2 != 0) {
        if (candidatos[n_cand - 1].prioridade > *max) {
            *max = candidatos[n_cand - 1].prioridade;
        }
        if (candidatos[n_cand - 1].prioridade < *min) {
            *min = candidatos[n_cand - 1].prioridade;
        }
    }
}

void cria_RCL(Candidatos *RCL, Candidatos *candidatos, int maximo, int minimo, int n_cand, int *n_RCL){
    for(int i = 0; i < n_cand; i++){
        if(candidatos[i].prioridade >= minimo + ALPHA * (maximo - minimo)){
            RCL[*n_RCL].disciplina = candidatos[i].disciplina;
            RCL[*n_RCL].prioridade = candidatos[i].prioridade;
            (*n_RCL) += 1;
        }
    }
}

void atualiza_candidatos(Candidatos *candidatos, int *n_cand, int disciplina){
    printf("lista de candidatos (disciplinas) do professor atual:\n");
    for(int i = 0; i < *n_cand; i++){
        printf("%d ", candidatos[i].disciplina);
    }

    for(int i = 0; i < *n_cand; i++){
        if(candidatos[i].disciplina == disciplina){
            candidatos[i].disciplina = candidatos[(*n_cand)-1].disciplina;
            candidatos[i].prioridade = candidatos[(*n_cand)-1].prioridade;
            break;
        }
    }
    //candidatos[escolhido].disciplina = candidatos[*n_cand].disciplina;  // colocando a ultima disciplina no local da disciplina que foi escolhida
    //candidatos[escolhido].prioridade = candidatos[*n_cand].prioridade;

    (*n_cand) -= 1;

    printf("\nlista de candidatos (disciplinas) do professor atual DEPOIS DA ATUALIZACAO:\n");
    for(int i = 0; i < *n_cand; i++){
        printf("%d ", candidatos[i].disciplina);
    }
}

void imprimir(Alocacao *alocacao) {
    printf("alocacao das disciplinas:\n");
    for (int d = 0; d < DISCIPLINAS; d++) {
        printf("disciplina %d -> professor %d (prioridade %d)\n", d, alocacao[d].professor+1, alocacao[d].prioridade);
    }
}