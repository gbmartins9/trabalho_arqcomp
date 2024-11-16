#ifndef COMMONS_H
#define COMMONS_H

/*BIBLIOTECAS E HEADERS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*DEFINIÇÕES*/

//Definições de tags para o código.
#define QUANTUM 5
#define MAX_PROCESSES 5

#define MAX_IO 10

//! Se tirar o identificador, tirar isso
#define PRIORIDADE_BAIXA 0
#define PRIORIDADE_ALTA 1

//! Se não usar tira
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
    int tempo_retorno;
} IO;

typedef struct {
    int id;
    int tempo_servico;
    int tempo_restante;
    int instante_ativacao;
    int prioridade;
    int quantidade_io;
    Estado estado; 
    IO *io; 
} Processo;

/*FUNÇÕES*/

IO novoIO(Tipo_IO tipo, int tempo_ativacao);

//? Não sei se deixo aqui, ou se movo para outro arquivo header depois. Por enquanto deixarei aqui por simplicidade. 

//? Mantenho como variável mesmo, ou mudo para ponteiro?
//? Talvez pra funcionalidade de "deletar processo" seja necessário, caso o processo chegue ao final da fila
Processo novoProcesso(int id, int tempo_servico, int instante_ativacao, int prioridade, int quantidade_io, IO *io);

void mostraProcesso(Processo p);

#endif