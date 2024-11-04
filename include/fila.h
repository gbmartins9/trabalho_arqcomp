#ifndef FILA_H
#define FILA_H

#include "commons.h"

//Definição de nó de uma Fila
typedef struct no {
    Processo p; //Mudar o nome depois
    Processo *proximo_processo;
} No;

//Definição de Fila
typedef struct {
    No *inicio;
    No *fim;
} Fila;

//Inicializa uma Fila.
bool inicializaFila(Fila *f);

//Insere um processo na Fila, e retorna se conseguiu ou não. 
bool inserirFila(Fila *f, Processo p);

//Remove um processo da Fila, e retorna se conseguiu ou não.
//Passamos processo como ponteiro para armazená-lo, caso seja necessário 
//Colocá-lo novamente na Fila. 
bool removerFila(Fila *f, Processo *p);

//Para cada elemento de f2, passa esse elemento para f1. 
//Retorna se conseguiu passar todos ou não. 
bool atualizaPrioridade(Fila *f1, Fila *f2);

#endif