#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/commons.h"
#include "../include/fila.h"

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

/*
O QUE TEMOS:
    0. Alguma coisa contendo os processos que serão utilizados
    1. Fila de alta prioridade 
    2. Fila de baixa prioridade 
    3. Fila com processos em IO 
*/

/*
O QUE FAZER A CADA TEMPO:

    1. Checar se temos algum processo novo que chegou (inserir na fila de alta prioridade)
        -> Verificar se o instante de ativação do processo é igual ao tempo corrente (Depois o Gabriel Explica)

    2. Verificar se o tempo de retorno de algum I/O é igual ao tempo corrente
            -> Checar se o processo tem algum IO na fila (removerFilaIO)
            -> Se o processo tem, checar se o tempo de ativação do próximo I/O já chegou 
            -> Se o tempo de ativação do próximo I/O já chegou, mover processo para fila de I/O
            -> Calcular tempo de retorno do I/O daquele processo.
            
    3. Checar se o processo atual continuará executando ou sofrerá preempção/IO
        
        3.2 Comparar o tempo em que o processo já esteve executando com o Quantum máximo
            -> Checar variável "count" para ver se é igual ao Quantum. 
            -> Se for, "count" = 0 e o processo volta para fila de alta/baixa
            -> Então, seleciona o próximo da fila de alta prioridade
*/

// Algoritmo Round Robin com enum Estado
void roundRobin(Fila *alta, int quantum) {

    Fila *alta = inicializaFila();
    Fila *baixa = inicializarFila();
    Fila *IO = inicializarFila();
    
    int tempo = 0; // tempo global
    int processos_concluidos = 0;
    int count = 0; // para comparar com o timeslice
    int f; // indicador de fila

    // Ordenando os processos
    ordenarPorInstanteAtivacao(alta, MAX_PROCESSES);

    while (processos_concluidos != MAX_PROCESSES) { 

        // Adiciona processos prontos à fila de execução
        adicionarProcessosProntos(alta, prontos, tempo);
        
        if (prontos->inicio != NULL) {
            No *atual = prontos->inicio;
            atual->processo.estado = EXECUTANDO; // Atualiza para EXECUTANDO

            atual->processo.tempo_restante--;
            count++;

            // se o processo acabou
            if (atual->processo.tempo_restante == 0){
                count = 0;
            }

            // decrementando o tempo_retorno do io
            for (i=0;i<atual->processo.quantidade_io;i++) {
                atual->processo.io[i].tempo_retorno--;
            }

            
            f=0; // Indicador de fila alta
        } else if() {

        }

        if ()

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
