#include <stdio.h>
#include <stdlib.h>
#include "../include/commons.h"
#include "../include/fila.h"

/* 
 *Processos novos entram direto na alta prioridade
 *Processos novos com I/O depende
 *Processos com preempção entram na baixa prioridade 
*/

//! Inicialmente fazendo apenas com uma fila (sem feedback)
//* Acho que não vai precisar
bool setEscalonador(Fila *f, Processo lista_processos[]);

int main() {
    //* Tentando adicionar uma primeira lógica para o round robin padrão
    //! Se der certo, adicionar para main depois

    /*INICIALIZAÇÃO*/
    Fila *fila_baixa = inicializaFila(PRIORIDADE_BAIXA);
    Fila *fila_alta = inicializaFila(PRIORIDADE_ALTA);

    //? Quando fizermos a entrada do arquivo, acho que mudar para um vetor seria interessante e facilitaria o código
    Processo *lista_processos = (Processo *) malloc(sizeof(Processo) * 5);
    lista_processos[0] = novoProcesso(1, 10, 3);
    lista_processos[1] = novoProcesso(2, 1, 1);
    lista_processos[2] = novoProcesso(3, 2, 3);
    lista_processos[3] = novoProcesso(4, 1, 4);
    lista_processos[4] = novoProcesso(5, 5, 2);

    Processo atual;
    int tempo_passado;
    int teste = 0;

    /*ALGORITMO*/
    //* Supondo que todos os processos já foram ordenados por ordem de ativação, e todos tem ativação 0 (chegaram no mesmo tempo). 
    //* Supondo sistema sem I/O. 
    //* Supondo critério de parada como sendo a fila ficar vazia (não é realmente útil, como explicado em tarefas.txt, mas como nesse caso todos chegaram no mesmo tempo vale)

    //Função para dar "set" no simulador
    //Função para dar "play" no simulador, executando até o critério de parada

    if(setEscalonador(fila_baixa, lista_processos) == false) { //Joga todo mundo na fila apenas. //! Tirar depois
        printf("Nao foi possivel inicializar o escalonador\n");
        return -1;
    }
    
    mostrarFila(fila_baixa);

    while (fila_baixa->inicio != NULL) {
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

bool setEscalonador(Fila *f, Processo lista_processos[]) {
    for (int i = 0; i < 5; i++) {
        if(inserirFila(f, lista_processos[i]) == false) return false;
    }
    return true;
}