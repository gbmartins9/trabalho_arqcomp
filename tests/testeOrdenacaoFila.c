#include <stdio.h>

typedef enum {PRONTO, EXECUTANDO, BLOQUEADO, TERMINADO} Estado;

typedef struct {
    int id;
    int tempo_servico;
    int tempo_restante;
    int instante_ativacao;
    int prioridade;
    int quantidade_io;
    Estado estado; 
    void *io; // Supondo que IO seja uma estrutura previamente definida
} Processo;

// Função para ordenar a fila pelo instante de ativação
void ordenarPorInstanteAtivacao(Processo *fila, int n) {
    for (int i = 0; i < n - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < n; j++) {
            if (fila[j].instante_ativacao < fila[indiceMenor].instante_ativacao) {
                indiceMenor = j;
            }
        }
        // Troca os elementos
        if (indiceMenor != i) {
            Processo temp = fila[i];
            fila[i] = fila[indiceMenor];
            fila[indiceMenor] = temp;
        }
    }
}

// Função de teste
int main() {
    Processo fila[] = {
        {1, 10, 10, 5, 1, 0, PRONTO, NULL},
        {2, 8, 8, 3, 2, 0, PRONTO, NULL},
        {3, 15, 15, 1, 3, 0, PRONTO, NULL},
        {4, 5, 5, 7, 1, 0, PRONTO, NULL}
    };
    int n = sizeof(fila) / sizeof(fila[0]);

    printf("Antes da ordenação:\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Instante de Ativação: %d\n", fila[i].id, fila[i].instante_ativacao);
    }

    ordenarPorInstanteAtivacao(fila, n);

    printf("\nApós a ordenação:\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Instante de Ativação: %d\n", fila[i].id, fila[i].instante_ativacao);
    }

    return 0;
}
