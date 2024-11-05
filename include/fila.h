#ifndef FILA_H
#define FILA_H

#include "commons.h"

//Definição de nó de uma Fila
typedef struct no {
    Processo processo; //Mudar o nome depois
    struct no *proximo_processo;
} No;

//Definição de Fila
typedef struct {
    No *inicio;
    No *fim;
    int identificador; //! Não sei se precisa ou não, pois temos que definir como será a prioridade de fato. 
} Fila;

//Inicializa uma Fila, colocando seus ponteiros para NULL.
//Retorna NULL se não conseguir inicializar. 
Fila *inicializaFila();

//Cria um novo nó contendo o processo p. 
No *novoNo(Processo p);

//Retorna o tamanho da fila (anotação: não sei se será necessário, caso não seja usado tirar depois)
int tamanhoFila(Fila *f);

//Insere um processo na Fila, e retorna se conseguiu ou não. 
bool inserirFila(Fila *f, Processo p);

//Remove um processo da Fila, e retorna se conseguiu ou não.
//Passamos processo como ponteiro para armazená-lo, caso seja necessário 
//Colocá-lo novamente na Fila. 
bool removerFila(Fila *f, Processo *p);

//Função para mostrar todos os processos da fila. 
void mostrarFila(Fila *f);

//Para cada elemento de f2, passa esse elemento para f1. 
//O que faz na prática e fazer o final de f1 apontar para o início de f2, e então zerar f2
bool atualizaPrioridade(Fila *f1, Fila *f2); //! TIRAR POIS NÃO TROCAM DE PRIORIDADE!!!

#endif