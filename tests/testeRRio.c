// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include "../include/commons.h"
#include "../include/fila.h"
// #include "../src/arquivos.c"
// #include "../src/roundRobin.c"

// Definição de constantes e estruturas
// #define MAX_PROCESSES 3
// #define QUANTUM 3

// Main para inicializar e testar
int main() {
    Fila *pendentes = lerTeste("tests/2.txt");
    
    // mostrarFila(pendentes, "Teste");
    printTeste(pendentes);
    roundRobin(pendentes);
    return 0;
}
