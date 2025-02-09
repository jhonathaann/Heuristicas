#include <stdio.h>

void min_max(int arr[], int n, int *min_val, int *max_val) {
    // caso base: se o vetor tiver apenas um elemento
    if (n == 1) {
        *min_val = arr[0];
        *max_val = arr[0];
        return;
    }
    
    // inicializando o maximo e o minimo
    if (arr[0] < arr[1]) {
        *min_val = arr[0];
        *max_val = arr[1];
    } else {
        *min_val = arr[1];
        *max_val = arr[0];
    }
    
    // percorrendo os elementos em pares
    for (int i = 2; i < n - 1; i += 2) {
        if (arr[i] < arr[i + 1]) {
            if (arr[i] < *min_val) *min_val = arr[i];
            if (arr[i + 1] > *max_val) *max_val = arr[i + 1];
        } else {
            if (arr[i + 1] < *min_val) *min_val = arr[i + 1];
            if (arr[i] > *max_val) *max_val = arr[i];
        }
    }
    
    // se tiver p elementos, verifica o ultimo elemento
    if (n % 2 != 0) {
        if (arr[n - 1] < *min_val) *min_val = arr[n - 1];
        if (arr[n - 1] > *max_val) *max_val = arr[n - 1];
    }
}

int main() {
    int arr[] = {3, 1, 5, 2, 4, 8, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int min_val, max_val;
    printf("\n%d\n", n);
    min_max(arr, n, &min_val, &max_val);
    printf("Min: %d, Max: %d\n", min_val, max_val);
    
    return 0;
}
