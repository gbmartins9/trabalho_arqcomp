#include <stdio.h>
#include <stdlib.h>
#include "../include/commons.h"
#include "../include/fila.h"

//TODO: Tirar o retorno
int roundRobin() {
    int tempo_aux = -1;
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

    fila_alta = inicializaFila();
    fila_baixa = inicializaFila();
    io = inicializaFila();


    // Adiciona processos com diferentes instantes de ativação
    inserirFila(pendentes, novoProcesso(1, 13, 0, 1, 1, lista_io1));
    inserirFila(pendentes, novoProcesso(2, 11, 1, 1, 0, empty));
    inserirFila(pendentes, novoProcesso(3, 7, 5, 1, 0, empty));
    //inserirFila(pendentes, novoProcesso(4, 8, 7, 1, 0, empty));
    //inserirFila(pendentes, novoProcesso(5, 16, 10, 1, 0, empty));


    //TODO: Função que pega todos os processos no arquivo e joga para essa fila
    
    int tempo = 0; // tempo global
    int processos_concluidos = 0; 
    int count = 0; // para comparar com o timeslice

    //Deixando aqui só pra facilitar minha cabeça na hora de programar
    Processo *processo_atual = NULL;
    Fila *fila_atual = NULL;

    while (processos_concluidos != 3) {
        
        printf("\n=== Tempo: %d ===\n", tempo);
        
        //* 1. Checar se temos algum processo novo que chegou (inserir na fila de alta prioridade)
        while(pendentes->inicio != NULL && pendentes->inicio->processo.instante_ativacao == tempo) {
            Processo temp = pendentes->inicio->processo;
            removerFila(pendentes, &temp);
            inserirFila(fila_alta, temp);
            printf("Processo P%d chegou na fila de alta prioridade.\n", temp.id);
        }

        //* 2. Verificar se o tempo de retorno de algum I/O é igual ao tempo corrente
        No *IOatual = io->inicio;
        while(IOatual != NULL) {
            for(int i = 0; i < IOatual->processo.quantidade_io; i++) {
                if(tempo == IOatual->processo.io[i].tempo_retorno) {
                    removerFilaIO(&(IOatual->processo), i);
                    printf("Processo P%d retornou do IO.\n", IOatual->processo.id);
                }
            }
            IOatual = IOatual->proximo_processo;
        }
        // printf("Debug: Tempo = %d, Processos Concluídos = %d\n", tempo, processos_concluidos);
        mostrarFila(fila_alta, "Alta");
        mostrarFila(fila_baixa, "Baixa");
        mostrarFila(io, "I/O");

        //* 3. Selecionar a proxima fila de execucao 
        if (fila_alta->inicio != NULL) {
            fila_atual = fila_alta;
        }
        else if (fila_baixa->inicio != NULL){
            fila_atual = fila_baixa;
        }
        else {
            //! Checar se deixaria ocioso.
            printf("Nenhum processo disponível. CPU ociosa.\n");
            tempo++;
        }
        processo_atual = &(fila_atual->inicio->processo); 
        printf("Executando processo P%d.\n", processo_atual->id);


        //* 4. Checar se o processo atual continuará executando ou sofrerá preempção/IO
        
        //* 4.1 Checar se o processo já acabou
        if(processo_atual->tempo_restante == 0) {
            count = 0;
            processos_concluidos++;
            Processo p = removerFila2(fila_atual);
            //removerFila(fila_atual, processo_atual); //Não precisaria armazenar o processo sendo tirado, mas tá aí por causa da função
            printf("Processo P%d concluido.\n", p.id);
        }

        //* 4.2 Verificar se o processo tem IO
        else if (processo_atual->quantidade_io != 0) {
            //Percorrer vetor de IO do processo.
            
            bool teste = false;

            for (int i = 0; i < processo_atual->quantidade_io ; i++) {
                if(tempo == processo_atual->io[i].tempo_ativacao) {
                    Processo p = removerFila2(fila_atual);
                    // removerFila(fila_atual, processo_atual);
                    inserirFilaIO(&p, i, tempo);
                    printf("Processo P%d entrou em IO.\n", p.id);
                    count = 0;  
                    teste = true;
                    break;
                }
            }
            if(teste == false) {
                processo_atual->tempo_restante--; 

                count++;
                tempo++;
                printf("Processo P%d continua executando. Tempo restante: %d.\n", processo_atual->id, processo_atual->tempo_restante);
            }
            //!! SE ISSO EXECUTAR MAS SAIR DO FOR, TEM QUE EXECUTAR O ELSE TAMBÉM 
        }

        //* 4.3 Comparar o tempo em que o processo já esteve executando com o Quantum máximo
        else if (count == QUANTUM) {
            count = 0;
            Processo p = removerFila2(fila_atual);
            //processo_atual = removerFila2(fila_atual);
            inserirFila(fila_baixa, p); // Sempre para de baixa, de acordo com as premissas
            printf("Quantum atingido. Processo P%d movido para fila de baixa prioridade.\n", p.id);
        } 

        else {
            //Se nada aconteceu, então o processo continua executando, e count é incrementado
            processo_atual->tempo_restante--;
            tempo++;
            count++;
            printf("Processo P%d continua executando. Tempo restante: %d.\n", processo_atual->id, processo_atual->tempo_restante);
        }
    }
    printf("\n=== Todos os processos foram concluídos em %d unidades de tempo. ===\n", tempo);
    return 0;
}

int main() {
    roundRobin();
    return 0;
}