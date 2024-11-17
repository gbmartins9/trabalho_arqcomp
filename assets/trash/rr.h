#include <stdio.h>
#include <stdlib.h>
#include "../include/commons.h"
#include "../include/fila.h"

extern Fila *fila_baixa;
extern Fila *fila_alta;
extern Fila *io;

void roundRobin(Fila *pendentes);