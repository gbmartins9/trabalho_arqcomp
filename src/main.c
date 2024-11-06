#include <stdio.h>
#include <stdlib.h>
// #include "../include/commons.h"

// #define MAXIMO_PROCESSOS 5
// #define QUANTUM 5

typedef struct t {
    int tipo;
    int funcao;
} No;


int main() {
    
    // Pode tirar tudo depois
    No *n = (No *) malloc(sizeof(No) * 3);
    n[0].tipo = 0; n[0].funcao = 1;
    n[1].tipo = 0; n[1].funcao = 1;
    n[2].tipo = 0; n[2].funcao = 1;

    int *arr = (int *) malloc(sizeof(int) * 3);
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;

    //int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    printf("[%d]", size);

    // Função para término de IO (enfileiras na fila correta de acordo com o tipo de io)

    // Função
    return 0;
}