#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição de constantes e estruturas
#define MAX_PROCESSES 3
#define QUANTUM 3

typedef struct {
    int tempo_ativacao; // Tempo de ativação do IO
    int tempo_retorno;  // Tempo de retorno do IO
} IO;

typedef struct {
    int id;               // Identificador do processo
    int tempo_ativacao;   // Quando o processo fica ativo
    int tempo_restante;   // Tempo restante para execução
    IO io[10];            // Lista de operações de IO
    int quantidade_io;    // Número de IOs
} Processo;

typedef struct No {
    Processo processo;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

// Funções auxiliares para manipulação de filas
Fila* inicializaFila() {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void inserirFila(Fila *fila, Processo processo) {
    No *novo = (No *)malloc(sizeof(No));
    novo->processo = processo;
    novo->proximo = NULL;
    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
}

bool removerFila(Fila *fila, Processo *processo) {
    if (fila->inicio == NULL) return false;
    No *removido = fila->inicio;
    *processo = removido->processo;
    fila->inicio = removido->proximo;
    if (fila->inicio == NULL) fila->fim = NULL;
    free(removido);
    return true;
}

void imprimirFila(Fila *fila, const char *nome) {
    printf("Fila %s: ", nome);
    No *atual = fila->inicio;
    if (atual == NULL) {
        printf("Vazia\n");
        return;
    }
    while (atual != NULL) {
        printf("P%d(T=%d) ", atual->processo.id, atual->processo.tempo_restante);
        atual = atual->proximo;
    }
    printf("\n");
}


// Função principal de escalonamento Round Robin
void roundRobin(Fila *pendentes) {
    Fila *alta = inicializaFila();
    Fila *baixa = inicializaFila();
    Fila *IO = inicializaFila();

    // TODO: Função que pega todos os processos no arquivo e joga para essa fila


    int tempo = 0; // tempo global
    int processos_concluidos = 0; 
    int count = 0; // para comparar com o timeslice

    // Deixando aqui só pra facilitar minha cabeça na hora de programar
    Processo *processo_atual;
    Fila *fila_atual;

    while (processos_concluidos != MAX_PROCESSES) {
        printf("\n=== Tempo: %d ===\n", tempo);

        //* 1. Checar se temos algum processo novo que chegou (inserir na fila de alta prioridade)
        if (pendentes->inicio != NULL && pendentes->inicio->processo.tempo_ativacao == tempo) {
            Processo temp;
            removerFila(pendentes, &temp);
            inserirFila(alta, temp);
            printf("Processo P%d chegou na fila de alta prioridade.\n", temp.id);
        }

        //* 2. Verificar se o tempo de retorno de algum I/O é igual ao tempo corrente
        No *IOatual = IO->inicio;
        while (IOatual != NULL) {
            for (int i = 0; i < IOatual->processo.quantidade_io; i++) {
                if (tempo == IOatual->processo.io[i].tempo_retorno) {
                    removerFila(IO, &IOatual->processo);
                    inserirFila(alta, IOatual->processo);
                    printf("Processo P%d retornou do IO e foi para a fila de alta prioridade.\n", IOatual->processo.id);
                }
            }
            IOatual = IOatual->proximo;
        }

        //* Imprimir o estado atual das filas
        imprimirFila(alta, "Alta");
        imprimirFila(baixa, "Baixa");
        imprimirFila(IO, "IO");

        //* 3. Selecionar a proxima fila de execucao 
        if (alta->inicio != NULL) {
            fila_atual = alta;
        } else if (baixa->inicio != NULL) {
            fila_atual = baixa;
        } else {
            printf("Nenhum processo disponível. CPU ociosa.\n");
            tempo++;
        }
        processo_atual = &fila_atual->inicio->processo;
        printf("Executando processo P%d.\n", processo_atual->id);

        //* 4. Checar se o processo atual continuará executando ou sofrerá preempção/IO

        //* 4.1 Checar se o processo já acabou
        if (processo_atual->tempo_restante == 0) {
            count = 0;
            processos_concluidos++;
            removerFila(fila_atual, processo_atual);
            printf("Processo P%d concluído.\n", processo_atual->id);
        }

        //* 4.2 Verificar se o processo tem IO
        else if (processo_atual->io != NULL) {
            for (int i = 0; i < processo_atual->quantidade_io; i++) {
                if (tempo == processo_atual->io[i].tempo_ativacao) {
                    removerFila(fila_atual, processo_atual);
                    inserirFila(IO, *processo_atual);
                    printf("Processo P%d entrou em IO.\n", processo_atual->id);
                }
            }
        }

        //* 4.3 Comparar o tempo em que o processo já esteve executando com o Quantum máximo
        else if (count == QUANTUM) {
            count = 0;
            removerFila(fila_atual, processo_atual);
            inserirFila(baixa, *processo_atual);
            printf("Quantum atingido. Processo P%d movido para fila de baixa prioridade.\n", processo_atual->id);
        } else {
            processo_atual->tempo_restante--;
            count++;
            tempo++;
            printf("Processo P%d continua executando. Tempo restante: %d.\n", processo_atual->id);
        }
    }

    printf("\n=== Todos os processos foram concluídos em %d unidades de tempo. ===\n", tempo);
}

// Main para inicializar e testar
int main() {
    Fila *pendentes = inicializaFila();

    // Criar processos para teste
    Processo p1 = {1, 0, 6, {{2, 5}, {4, 7}}, 2}; // Processo 1
    Processo p2 = {2, 1, 4, {{3, 6}}, 1};         // Processo 2
    Processo p3 = {3, 3, 8, {{5, 9}}, 1};         // Processo 3

    // Adicionar processos à fila de pendentes
    inserirFila(pendentes, p1);
    inserirFila(pendentes, p2);
    inserirFila(pendentes, p3);

    imprimirFila(pendentes, "Pendentes");
    // printf("Iniciando Round Robin com IO.\n");
    // roundRobin(pendentes);

    return 0;
}
