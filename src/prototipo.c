#include <stdio.h>
#include <stdlib.h>
#include "../include/commons.h"
#include "../include/fila.h"

/* 
 *Processos novos entram direto na alta prioridade
 *Processos novos com I/O depende
 *Processos com preempção entram na baixa prioridade 
*/

Fila *fila_baixa;
Fila *fila_alta;
Fila *io;


int main() {
    

    /*INICIALIZAÇÃO*/
    
    fila_baixa = inicializaFila(); 
    fila_alta = inicializaFila(); 
    io = inicializaFila();

    Processo *lista_processos = (Processo *) malloc(sizeof(Processo) * 5);
    IO io1 = novoIO(0, 7, 2);
    IO io2 = novoIO(1, 8, 5);
    IO io3 = novoIO(2, 4, 1);
    IO io4 = novoIO(1, 8, 10);
    IO empty[] = {};
    IO lista_io1[] = {io1, io2};
    IO lista_io2[] = {io3};
    IO lista_io3[] = {io4};


    lista_processos[0] = novoProcesso(1, 10, 3, 0, empty);
    lista_processos[1] = novoProcesso(2, 1, 1, 2, lista_io1);
    lista_processos[2] = novoProcesso(3, 2, 3, 0, empty);
    lista_processos[3] = novoProcesso(4, 1, 4, 1, lista_io2);
    lista_processos[4] = novoProcesso(5, 5, 2, 1, lista_io3);

    Processo atual;
    int tempo = 0;
    int teste = 0;
    int processos_completados = 0;

    /*ALGORITMO*/
    //* Supondo que todos os processos já foram ordenados por ordem de ativação, e todos tem ativação 0 (chegaram no mesmo tempo). 
    //* Supondo sistema sem I/O. 
    //* Supondo critério de parada como sendo a fila ficar vazia (não é realmente útil, como explicado em tarefas.txt, mas como nesse caso todos chegaram no mesmo tempo vale)

    //TODO: Função que lida com o início do I/O
    //TODO: Função que lida com o fim do I/O
   
    
    mostrarFila(fila_baixa);

    while (processos_completados < MAX_PROCESSES) {
        removerFila(fila_baixa, &atual);
        if((atual.tempo_restante - QUANTUM) > 0) { //Ainda há tempo restante
            atual.tempo_restante -= QUANTUM;
            inserirFila(fila_baixa, atual);    
        }
        else {
            //TODO: CONSIDERAR CASO O TEMPO DO QUANTUM SEJA MAIOR QUE O TIME SLICE NECESSÁRIO
        }
        teste++;
        mostrarFila(fila_baixa);
    }


    mostrarFila(fila_baixa);
    printf("\n[%d]\n", teste);
    

    return 0;
}


//TODO: Tirar essa função
bool setEscalonador(Fila *f, Processo lista_processos[]) {
    for (int i = 0; i < 5; i++) {
        if(inserirFila(f, lista_processos[i]) == false) return false;
    }
    return true;
}

//Função que adiciona o processo na fila de IO, calculando o tempo de retorno com base no tempo atual
void inserirFilaIO(Processo *p, int i, int tempo_atual) {
    inserirFila(&io, *p);
    printf("Processo %d foi para fila de I/O\n", p->id);
    p->io[i].tempo_retorno = tempo_atual + p->io[i].tempo_execucao;
}

//Função que remove um processo da fila de IO e o redireciona para a fila correta.
void removerFilaIO(Processo *p, int i) {
    int tipoIO = p->io[i].tipo;
    //! INCONSISTÊNCIA: ESTAMOS REMOVENDO UM CARA ESPECÍFICO MAS A FILA REMOVE O PRIMEIRO
    removerFila(io, p);
    switch (tipoIO) {
        case 0:
            inserirFila(fila_baixa, *p);
            printf("Processo %d completou I/O de disco e foi para fila de baixa prioridade\n", p->id);
            break;
        case 1:
            inserirFila(fila_alta, *p);
            printf("Processo %d completou I/O de fita e foi para fila de baixa prioridade\n", p->id);
            break;
        case 2:
            inserirFila(fila_alta, *p);
            printf("Processo %d completou I/O de impressora e foi para fila de baixa prioridade\n", p->id);
            break;
    }
}