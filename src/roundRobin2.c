#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/commons.h"
#include "../include/fila.h"


// Função para adicionar processos prontos à fila de execução
void adicionarProcessosProntos(Fila *pendentes, Fila *execucao, int tempo) {
    No *atual = pendentes->inicio;
    while (atual != NULL) {
        if (atual->processo.instante_ativacao <= tempo && atual->processo.estado == NOVO) {
            atual->processo.estado = PRONTO; // Atualiza o estado para PRONTO
            Processo p = atual->processo;
            inserirFila(execucao, p); // Insere na fila de execução
            removerFila(pendentes, &atual->processo); // Remove da lista de pendentes
            atual = pendentes->inicio; // Reinicia a verificação
        } else {
            atual = atual->proximo_processo;
        }
    }
}

// Algoritmo Round Robin com enum Estado
void roundRobin(Fila *pendentes, int quantum) {
    Fila *execucao = inicializaFila(); // Fila de processos prontos
    int tempo = 0;

    while (pendentes->inicio != NULL || execucao->inicio != NULL) {
        // Adiciona processos prontos à fila de execução
        adicionarProcessosProntos(pendentes, execucao, tempo);

        if (execucao->inicio != NULL) {
            No *atual = execucao->inicio;
            atual->processo.estado = EXECUTANDO; // Atualiza para EXECUTANDO

            int execucao_tempo = (atual->processo.tempo_restante > quantum) ? quantum : atual->processo.tempo_restante;
            printf("Tempo %d: Executando Processo %d por %d unidades de tempo\n", tempo, atual->processo.id, execucao_tempo);
            
            tempo += execucao_tempo;
            atual->processo.tempo_restante -= execucao_tempo;

            // Verifica novamente se há novos processos prontos após a execução do quantum
            adicionarProcessosProntos(pendentes, execucao, tempo);

            if (atual->processo.tempo_restante <= 0) {
                atual->processo.estado = FINALIZADO; // Atualiza para FINALIZADO
                printf("Tempo %d: Processo %d concluído\n", tempo, atual->processo.id);
                removerFila(execucao, &atual->processo);  // Remove da fila de execução
            } else {
                // Move o processo para o final da fila
                atual->processo.estado = PRONTO; // Volta para PRONTO
                Processo p = atual->processo;
                removerFila(execucao, &atual->processo);
                inserirFila(execucao, p);
            }
        } else {
            // Avança o tempo se não há processos prontos
            tempo++;
        }

        mostrarFila(execucao); // Mostra o estado da fila de execução
    }

    printf("Tempo total de execução: %d\n", tempo);
    free(execucao); // Libera memória da fila de execução
}

int main() {
    Fila *pendentes = inicializaFila();
    if (pendentes == NULL) {
        printf("Erro ao inicializar a fila de pendentes.\n");
        return -1;
    }

    // Adiciona processos com diferentes instantes de ativação
    inserirFila(pendentes, novoProcesso(1, 13, 0, 1, 0, NULL));
    inserirFila(pendentes, novoProcesso(2, 11, 4, 1, 0, NULL));
    inserirFila(pendentes, novoProcesso(3, 7, 5, 1, 0, NULL));
    inserirFila(pendentes, novoProcesso(4, 8, 7, 1, 0, NULL));
    inserirFila(pendentes, novoProcesso(5, 16, 10, 1, 0, NULL));

    int quantum = 2;
    roundRobin(pendentes, quantum);

    free(pendentes); // Libera memória da fila de pendentes
    return 0;
}
