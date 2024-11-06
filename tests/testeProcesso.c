#include "../include/commons.h"
#include "../include/fila.h"

int main() {
    //Teste de processos com IO

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
    
    for(int i = 0; i < 5; i++) {
        mostraProcesso(lista_processos[i]);
    }

    return 0;
}

