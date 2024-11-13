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
void roundRobin(Fila *alta, int quantum) {

    Fila *alta = inicializaFila();
    Fila *IO = inicializarFila();
    Fila *prontos = inicializarFila();
    Fila *baixa = inicializarFila();
    int tempo = 0;

    // Adiciona processos prontos à fila de execução
    adicionarProcessosProntos(alta, prontos, tempo);

    while (alta->inicio != NULL || prontos->inicio != NULL) { // REVER A CONDICAO DE PARADA
        
        if (prontos->inicio != NULL) {
            No *atual = prontos->inicio;
            atual->processo.estado = EXECUTANDO; // Atualiza para EXECUTANDO

            int execucao_tempo = (atual->processo.tempo_restante > quantum) ? quantum : atual->processo.tempo_restante;
            printf("Tempo %d: Executando Processo %d por %d unidades de tempo\n", tempo, atual->processo.id, execucao_tempo);
            
            // Aqui vamos calcular o quantum que o processo vai usar (isto é, verificar se ele será interrompido por I/O.
            for (int i=0;i<atual->processo.quantidade_io;i++){
                // Assumindo que nossa lista de IOs esta ordenada.
                if (atual->processo.io[i].tempo_ativacao >= tempo && atual->processo.io[i].tempo_ativacao >= tempo + quantum) {
                    execucao_tempo = atual->processo.io[i].tempo_ativacao; // REVER PARA MAIS DE IO
                    atual->processo.tempo_ativacao = tempo + atual->processo.io[i].tempo_execucao + atual->processo.io[i].tempo_ativacao;
                    removerFila(prontos, &atual->processo);
                    inserirFilaIO(IO);
                    break; // VERIFICAR
                }
            }

            // Vamos encontrar os processos com menor instante de ativação dentro do quantum. Se houver empate, usamos os critérios Novos - I/O - Preempção.
            for (int i=tempo; i<=execucao_tempo;i++) {
                // Tem alguem com instante de ativacao == i na fila de Novos? Entao insere
                // Tem alguem com instante de ativacao == i na fila de IO? Entao insere
                // Tem alguem com instante de ativacao == i na fila de Preempcao? Entao insere
            }
         
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

    IO io1 = novoIO(0, 7, 2);
    IO io2 = novoIO(1, 8, 5);
    IO io3 = novoIO(2, 4, 1);
    IO io4 = novoIO(1, 8, 10);
    IO empty[] = {};
    IO lista_io1[] = {io1};
    IO lista_io2[] = {io2};
    IO lista_io3[] = {io3};
    IO lista_io4[] = {io4};


    // Adiciona processos com diferentes instantes de ativação
    inserirFila(pendentes, novoProcesso(1, 13, 0, 1, 1, lista_io1));
    inserirFila(pendentes, novoProcesso(2, 11, 4, 1, 1, lista_io2));
    inserirFila(pendentes, novoProcesso(3, 7, 5, 1, 1, lista_io3));
    inserirFila(pendentes, novoProcesso(4, 8, 7, 1, 1, lista_io4));
    inserirFila(pendentes, novoProcesso(5, 16, 10, 1, 1, lista_io4));

    int quantum = 2;
    roundRobin(pendentes, quantum);

    free(pendentes); // Libera memória da fila de pendentes
    return 0;
}
