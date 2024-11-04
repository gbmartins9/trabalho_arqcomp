#ifndef COMMONS_H
#define COMMONS_H

#include <stdio.h>
#include <stdlib.h>

//Definições de tags para o código.
#define QUANTUM 5
#define MAX_IO 10
#define PRIORIDADE_BAIXA 0
#define PRIORIDADE_ALTA 1

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
    IO lista_io[MAX_IO];
} Processo;


#endif