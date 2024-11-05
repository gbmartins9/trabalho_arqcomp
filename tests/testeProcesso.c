#include "../include/commons.h"
#include "../include/fila.h"

int main() {

    Processo *p = (Processo *) malloc(sizeof(Processo));
    *p = novoProcesso(1, 10, 10, 5);

    printf("Testando processos: \n");
    mostraProcesso(*p);
    

    return 0;
}

