#include <stdio.h>

// Estrutura para representar um par de itens
typedef struct {
    int item1;
    int item2;
} ParItens;

// Estrutura para representar um par de itens e seu bônus
typedef struct {
    ParItens par;
    int bonus;
} BonusPar;

int main() {
    // Array de pares de itens
    ParItens pares[] = { {1, 2}, {3, 4} };

    // Array de bônus associados aos pares de itens
    BonusPar bonus_pares[] = { {{1, 2}, 10}, {{3, 4}, 150} };

    // Acessar os valores
    printf("Par: (%d, %d), Bonus: %d\n", bonus_pares[0].par.item1, bonus_pares[0].par.item2, bonus_pares[0].bonus);
    printf("Par: (%d, %d), Bonus: %d\n", bonus_pares[1].par.item1, bonus_pares[1].par.item2, bonus_pares[1].bonus);

    return 0;
}
