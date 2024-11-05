#ifndef COMMONS_H
#define COMMONS_H

/*BIBLIOTECAS E HEADERS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*DEFINIÇÕES*/

//Definições de tags para o código.
#define QUANTUM 5
#define MAX_IO 10

//TODO: Definir corretamente como faremos a prioridade.
#define PRIORIDADE_BAIXA 0
#define PRIORIDADE_ALTA 1

#define TAMANHO_MAX_STRING 10

#define bool int
#define true 1
#define false 0

//Definições dos estados do processo.
//Usando modelo de 5 estados. 
typedef enum {
    NOVO,
    PRONTO,
    EXECUTANDO,
    FINALIZADO,
    BLOQUEADO
} Estado;

typedef enum {
    disco = 0,
    fita = 1,
    impressora = 2
} Tipo_IO;

typedef struct {
    Tipo_IO tipo; 
    int tempo_execucao;
    int tempo_ativacao;
} IO;

typedef struct {
    int id;
    int tempo_servico;
    int tempo_restante;
    int prioridade;
    // IO lista_io[MAX_IO]; //* Tirei momentaneamente para testar os processos.
} Processo;

/*FUNÇÕES*/

//? Não sei se deixo aqui, ou se movo para outro arquivo header depois. Por enquanto deixarei aqui por simplicidade. 

//? Mantenho como variável mesmo, ou mudo para ponteiro?
//? Talvez pra funcionalidade de "deletar processo" seja necessário, caso o processo chegue ao final da fila
Processo novoProcesso(int id, int tempo_servico, int tempo_restante, int prioridade);

void mostraProcesso(Processo p);

#endif