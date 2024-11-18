#include "../include/commons.h"
#include "../include/fila.h"
#include "../include/arquivos.h"

extern Fila *fila_baixa;
extern Fila *fila_alta;
extern Fila *io;

void roundRobin(Fila *pendentes) {
    
    //*DEFINIÇÃO DE VARIÁVEIS*//
    
    int tempo = 0;
    int processos_concluidos = 0; 
    int tempo_passado = 0;
    Processo *processo_atual = NULL;
    Fila *fila_atual = NULL;
    fila_baixa = inicializaFila();
    fila_alta = inicializaFila();
    io = inicializaFila();
    bool troca;

    //*LÓGICA DO ESCALONADOR*//

    while (processos_concluidos != MAX_PROCESSES) {
        
        //Mostramos o intervalo de tempo atual
        printf("\n=== Tempo: %d - %d ===\n", tempo, tempo + 1);
        
        //* 1. Checar se temos algum processo novo que chegou (inserir na fila de alta prioridade)
        //Percorremos a fila de pendentes, enquanto esta não terminar, e enquanto o instante de ativação
        //Do processo for o tempo corrente, sabendo que esta fila está ordenada por instante de ativação 
        while(pendentes->inicio != NULL && pendentes->inicio->processo.instante_ativacao == tempo) {
            Processo temp = removerFila(pendentes); //Remove o processo da fila de pendentes
            inserirFila(fila_alta, temp); //Insere o processo na fila de alta prioridade
            printf("\n-> Processo P%d chegou na fila de alta prioridade.\n", temp.id);
        }

        //* 2. Verificar se o tempo de retorno de algum I/O é igual ao tempo corrente
        //Percorremos a fila de IO, enquanto esta não terminar, e checamos o tempo de 
        //Cada IO, de cada processo na fila. Para cada processo que tiver o tempo de retorno
        //Como o tempo corrente, o retiramos da fila de IO e o movemos para a fila correta 
        //(Lógica interna da função removerFilaIO). 
        No *IOatual = io->inicio;
        while(IOatual != NULL) {
            for(int i = 0; i < IOatual->processo.quantidade_io; i++) {
                if(tempo == IOatual->processo.io[i].tempo_retorno) {
                    removerFilaIO(&(IOatual->processo), i);
                }
            }
            IOatual = IOatual->proximo_processo;
        }

        //Mostramos as três filas no tempo corrente
        printf("\n");
        mostrarFila(fila_alta, "Alta");
        mostrarFila(fila_baixa, "Baixa");
        mostrarFila(io, "I/O");
        printf("\n");

        //* 3. Selecionar a proxima fila de execucao 
        //Checamos se a fila de alta possui processos. Se possuir, ela será a fila atual. Caso contrário, checamos a fila 
        //De baixa prioridade. Se nenhuma das duas filas estiver com processos, isso quer dizer que todos os processos no
        //Tempo corrente estão bloqueados (em I/O), ou que ainda há processos restantes, mas eles ainda não chegaram em 
        //Seus tempos de ativação. 
        if (fila_alta->inicio != NULL) {
            fila_atual = fila_alta;
        }
        else if (fila_baixa->inicio != NULL){
            fila_atual = fila_baixa;
        }
        else {
            printf("-> Nenhum processo disponivel. CPU ociosa.\n");
            tempo++; //Neste caso, o tempo ainda passa. 
            continue; //Pulamos para a próxima iteração. 
        }

        //* Executar o processo atual
        //Selecionamos o processo no início da fila atual, mas não o retiramos ainda. 
        processo_atual = &(fila_atual->inicio->processo); 
        printf("-> Executando processo P%d:\n\tTempo de servico total: %d\n\tTempo restante antes da operacao: %d.\n", processo_atual->id, processo_atual->tempo_servico, processo_atual->tempo_restante);
    
        //Executamos o processo
        processo_atual->tempo_restante--; //tempo restante diminui
        tempo++; //tempo global incrementa
        tempo_passado++; //contador incrementa
        troca = false; //definimos a flag troca como false

        //* 4. Checar se o processo atual continuará executando ou sofrerá preempção/IO

        //* 4.1 Checar se o processo já acabou
        //Se o tempo restante for nulo após a execução,
        //Então o processo terminou, e poderá ser removido da fila atual.
        if(processo_atual->tempo_restante == 0) {
            tempo_passado = 0; //Zeramos o contador
            processos_concluidos++; //Incrementamos a quantidade de processos concluídos
            Processo p = removerFila(fila_atual);
            printf("-> Processo P%d Concluido.\n", p.id);
            continue; //Podemos ir para a próxima iteração, pois sabemos que as próximas checagens serão falsas
        }

        //* 4.2 Verificar se o processo tem IO
        //Se o processo tiver a quantidade total de IOs diferente de 0, 
        //Percorremos por todo o vetor contendo seus IOs, checando se o tempo de ativação
        //De algum deles é o tempo corrente. Se for, colocamos o processo na fila de IO. 
        if (processo_atual->quantidade_io != 0) {
            for (int i = 0; i < processo_atual->quantidade_io; i++) {
                if(processo_atual->tempo_servico - processo_atual->tempo_restante == processo_atual->io[i].tempo_ativacao) {
                    tempo_passado = 0;  //Zeramos o contador
                    troca = true; //Colocamos a flag troca como true
                    Processo temp = removerFila(fila_atual);
                    inserirFilaIO(&temp, i, tempo);
                    printf("-> Processo P%d solicitou IO: \n\t Atingiu o tempo de execucao: %d \n\t Tempo restante apos a operacao: %d.\n", temp.id, temp.tempo_servico - temp.tempo_restante, temp.tempo_restante);
                    break; //Podemos sair do loop, pois sabemos que não haverá mais nenhum IO com instante de ativação no tempo corrente
                }
            }
        }

        //* 4.3 Comparar o tempo em que o processo já esteve executando com o Quantum máximo
        //Se não tiver tido troca na checagem anterior, e se o contador de 
        //Quantos instantes de tempo o mesmo processo já esteve executando chegar ao valor do quantum,
        //O processo sofrerá preempção, sendo enviado para a fila de baixa prioridade,
        //Como especificado nas premissas. 
        if (!troca && tempo_passado == QUANTUM) {
            tempo_passado = 0; //Zeramos o contador
            Processo p = removerFila(fila_atual); 
            inserirFila(fila_baixa, p); 
            printf("-> Quantum atingido: \n\tProcesso P%d movido para fila de baixa prioridade\n\tTempo restante apos a operacao: %d\n", p.id, p.tempo_restante);
        }

        //Se não tiver tido nenhum tipo de troca, informamos que não houve preempção nem I/O, e informamos o tempo restante após este instante de tempo. 
        else if (!troca) {
            printf("-> Processo P%d nao sofreu preempcao nem I/O.\n\tTempo restante apos a operacao: %d.\n", processo_atual->id, processo_atual->tempo_restante);
        }
    }

    //Se todos os processos tiverem sido concluídos, informamos o último instante de tempo,
    //E mostramos as filas vazias

    printf("\n=== Tempo: %d ===\n", tempo);

    printf("\n");
    mostrarFila(fila_alta, "Alta");
    mostrarFila(fila_baixa, "Baixa");
    mostrarFila(io, "I/O");
    printf("\n");

    printf("=== Todos os processos foram concluidos em %d unidades de tempo. ===\n", tempo); 
    return;
}


int main() {

    //Leitura do arquivo de entrada    
    Fila *pendentes = lerArquivo("Docs/Entrada4.txt");
    
    //Mostramos os processos lidos na forma de tabela
    printProcessos(pendentes);

    //Execução do simulador
    roundRobin(pendentes);
    
    return 0;
}
