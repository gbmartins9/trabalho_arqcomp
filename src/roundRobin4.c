#include <stdio.h>
#include <stdlib.h>
#include "../include/commons.h"
#include "../include/fila.h"

Fila *fila_baixa = NULL;
Fila *fila_alta = NULL;
Fila *io = NULL;

//TODO: Tirar o retorno
int roundRobin() {
    int tempo_aux = -1;
    Fila *pendentes = inicializaFila();
    if (pendentes == NULL) {
        printf("Erro ao inicializar a fila de pendentes.\n");
        return -1;
    }

    fila_alta = inicializaFila();
    fila_baixa = inicializaFila();
    io = inicializaFila();
    
    IO empty[] = {};
    IO lista_ioP1[] = {novoIO(0, 4)};
    IO lista_ioP2[] = {novoIO(1, 6), novoIO(0, 6)};
    IO lista_ioP5[] = {novoIO(0, 2), novoIO(1, 7)};

    inserirFila(pendentes, novoProcesso(1, 13, 0, 1, lista_ioP1));
    inserirFila(pendentes, novoProcesso(2, 11, 4, 2, lista_ioP2));
    inserirFila(pendentes, novoProcesso(3, 7, 5, 0, empty));
    inserirFila(pendentes, novoProcesso(4, 8, 7, 0, empty));
    inserirFila(pendentes, novoProcesso(5, 16, 10, 2, lista_ioP5));


    //TODO: Função que pega todos os processos no arquivo e joga para essa fila
    
    int tempo = 0; // tempo global
    int processos_concluidos = 0; 
    int count = 0; // para comparar com o timeslice

    //Deixando aqui só pra facilitar minha cabeça na hora de programar
    Processo *processo_atual = NULL;
    Fila *fila_atual = NULL;

    while (processos_concluidos != MAX_PROCESSES) {
        
        printf("\n=== Tempo: %d - %d ===\n", tempo, tempo + 1);
        
        //* 1. Checar se temos algum processo novo que chegou (inserir na fila de alta prioridade)
        while(pendentes->inicio != NULL && pendentes->inicio->processo.instante_ativacao == tempo) {
            Processo temp = pendentes->inicio->processo;
            removerFila(pendentes, &temp);
            inserirFila(fila_alta, temp);
            printf("\n-> Processo P%d chegou na fila de alta prioridade.\n", temp.id);
        }

        //* 2. Verificar se o tempo de retorno de algum I/O é igual ao tempo corrente
        No *IOatual = io->inicio;
        while(IOatual != NULL) {
            for(int i = 0; i < IOatual->processo.quantidade_io; i++) {
                if(tempo == IOatual->processo.io[i].tempo_retorno) {
                    removerFilaIO(&(IOatual->processo), i);
                    //printf("-> Processo P%d retornou do IO.\n", IOatual->processo.id);
                }
            }
            IOatual = IOatual->proximo_processo;
        }

        printf("\n");
        mostrarFila(fila_alta, "Alta");
        mostrarFila(fila_baixa, "Baixa");
        mostrarFila(io, "I/O");
        printf("\n");


        //* 3. Selecionar a proxima fila de execucao 
        if (fila_alta->inicio != NULL) {
            fila_atual = fila_alta;
        }
        else if (fila_baixa->inicio != NULL){
            fila_atual = fila_baixa;
        }
        else {
            //! Checar se deixaria ocioso.
            printf("-> Nenhum processo disponivel. CPU ociosa.\n");
            tempo++;
            continue;
        }
        processo_atual = &(fila_atual->inicio->processo); 
        printf("-> Executando processo P%d:\n\tTempo de servico total: %d\n\tTempo restante antes da operacao: %d.\n", processo_atual->id, processo_atual->tempo_servico, processo_atual->tempo_restante);
 
        processo_atual->tempo_restante--;
        tempo++;
        count++;
        bool troca = false;

        //* 4. Checar se o processo atual continuará executando ou sofrerá preempção/IO

        //* 4.2 Verificar se o processo tem IO
        if (processo_atual->quantidade_io != 0) {
            //Percorrer vetor de IO do processo.
            //! bool teste = false;

            for (int i = 0; i < processo_atual->quantidade_io ; i++) {
                if(processo_atual->tempo_servico - processo_atual->tempo_restante == processo_atual->io[i].tempo_ativacao) {
                    Processo p = removerFila2(fila_atual);
                    // removerFila(fila_atual, processo_atual);
                    inserirFilaIO(&p, i, tempo);
                    printf("-> Processo P%d solicitou IO: \n\t Atingiu o tempo de execucao: %d \n\t Tempo restante apos a operacao: %d.\n", p.id, p.tempo_servico - p.tempo_restante, p.tempo_restante);
                    count = 0;  
                    //! teste = true;
                    troca = true;
                    break;
                }
            }
        }

        //* 4.1 Checar se o processo já acabou       
        if(!troca && processo_atual->tempo_restante == 0) {
            count = 0;
            processos_concluidos++;
            Processo p = removerFila2(fila_atual);
            printf("-> Processo P%d Concluido.\n", p.id);
        }

        //* 4.3 Comparar o tempo em que o processo já esteve executando com o Quantum máximo
        else if (!troca && count == QUANTUM) {
            count = 0;
            Processo p = removerFila2(fila_atual);
            //processo_atual = removerFila2(fila_atual);
            inserirFila(fila_baixa, p); // Sempre para de baixa, de acordo com as premissas
            printf("-> Quantum atingido: \n\tProcesso P%d movido para fila de baixa prioridade\n\tTempo restante apos a operacao: %d\n", p.id, p.tempo_restante);
        }

        else if (!troca) {
            printf("-> Processo P%d nao sofreu preempcao nem I/O.\n\tTempo restante apos a operacao: %d.\n", processo_atual->id, processo_atual->tempo_restante);
        }
    }

    printf("\n=== Tempo: %d ===\n", tempo);

    printf("\n");
    mostrarFila(fila_alta, "Alta");
    mostrarFila(fila_baixa, "Baixa");
    mostrarFila(io, "I/O");
    printf("\n");

    printf("=== Todos os processos foram concluidos em %d unidades de tempo. ===\n", tempo); 
    return 0;
}

int main() {
    roundRobin();
    return 0;
}