#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 1024
#define TAM_AREA 33  // 32 bits + '\0'
#define MAX_AREAS 100

int area_ja_existe(char areas[][TAM_AREA], int total, char *nova_area) {
    for (int i = 0; i < total; i++) {
        if (strcmp(areas[i], nova_area) == 0) {
            return 1; // ja existe
        }
    }
    return 0;
}

int main() {
    FILE *arquivo = fopen("C:/Users/jhona/OneDrive/Faculdade/LEXA/IC/entrada.csv", "r");
    
    if (arquivo == NULL) {
        perror("erro ao abrir o arquivo");
        return 1;
    }

    char linha[MAX_LINHA];
    char areas[MAX_AREAS][TAM_AREA];
    int total_areas = 0;

    // ignorando as duas primeiras linhas
    fgets(linha, MAX_LINHA, arquivo); // 224;61;14;
    fgets(linha, MAX_LINHA, arquivo); // cabecalho

    while (fgets(linha, MAX_LINHA, arquivo)) {
        // pega a ultima coluna de cada linha (area)
        char *area = strrchr(linha, ';');
        if (area != NULL) {
            area++; // avança para depois do ';'

            // remove quebra de linha
            area[strcspn(area, "\r\n")] = '\0';

            // verifica se ja existe
            if (!area_ja_existe(areas, total_areas, area)) {
                strncpy(areas[total_areas], area, TAM_AREA);
                total_areas++;
            }
        }
    }

    fclose(arquivo);

    printf("Total de areas distintas: %d\n", total_areas);
    return 0;
}
