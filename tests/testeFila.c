#include "../include/commons.h"
#include "../include/fila.h"

int main() {

    Fila *f1 = inicializaFila(1);
    Fila *f2 = inicializaFila(2);

    printf("Mostrando fila 1 e fila 2 vazias: \n");

    mostrarFila(f1);
    mostrarFila(f2);

    printf("Adicionando processo 1 para fila 1: \n");
    
    Processo p = novoProcesso(1, 10, 8, 2);
    inserirFila(f1, p);
    mostrarFila(f1);

    printf("Adicionando processos 2 e 3 para fila 2: \n");
    
    p = novoProcesso(2, 5, 2, 1);
    inserirFila(f2, p);

    p = novoProcesso(3, 10, 4, 1);
    inserirFila(f2, p);

    mostrarFila(f2);
    
    printf("Tirando processo na frente da fila: \n");
    removerFila(f1, &p);
    mostraProcesso(p);
    mostrarFila(f1);

    printf("Mandando todos os processos de f2 para f1: \n");
    atualizaPrioridade(f1, f2);
    mostrarFila(f1);
    mostrarFila(f2);

    return 0;
}