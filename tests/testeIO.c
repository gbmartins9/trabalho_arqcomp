#include "../include/commons.h"
#include "../include/fila.h"


Fila *fila_baixa;
Fila *fila_alta;
Fila *io;


//Função que adiciona o processo na fila de IO, calculando o tempo de retorno com base no tempo atual
void inserirFilaIO(Processo *p, int i, int tempo_atual) {
    inserirFila(io, *p);
    printf("Processo %d foi para fila de I/O\n", p->id);
    p->io[i].tempo_retorno = tempo_atual + p->io[i].tempo_execucao;
}

//Função que remove um processo da fila de IO e o redireciona para a fila correta.
void removerFilaIO(Processo *p, int i) {
    int tipoIO = p->io[i].tipo;
    // printf("\nProcesso: [%d]\n", p->id);
    // printf("\nI/O: [%d]\n", tipoIO);
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

int main() {

    /*INICIALIZAÇÕES*/

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
    
    inserirFilaIO(&lista_processos[1], 1, 5);
    inserirFilaIO(&lista_processos[3], 0, 7);
    inserirFilaIO(&lista_processos[4], 0, 8);
    removerFilaIO(&lista_processos[3], 0);
    mostrarFila(io);
    //mostraProcesso(lista_processos[3]);

    return 0;
}