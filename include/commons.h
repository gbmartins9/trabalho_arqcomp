#ifndef COMMONS_H
#define COMMONS_H

//*BIBLIOTECAS E HEADERS*//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*DEFINIÇÕES*//

//Definição de booleano
#define bool int
#define true 1
#define false 0

//Definições de tags para o código
//Usadas de acordo com as premissas
#define QUANTUM 5
#define MAX_PROCESSES 5
#define MAX_IO 10 //? Tirar

//Definição do tipo de enum, usando um IO
typedef enum {
    DISCO = 0,
    FITA = 1,
    IMPRESSORA = 2
} Tipo_IO;

//Definição da struct IO
//Usado para representar os IOs de cada processo 
typedef struct {
    Tipo_IO tipo;
    int tempo_execucao;
    int tempo_ativacao;
    int tempo_retorno;
} IO;

//Definição da struct Processo
typedef struct {
    int id;
    int tempo_servico;
    int tempo_restante;
    int instante_ativacao;
    int quantidade_io;
    IO *io; 
} Processo;

//*FUNÇÕES*//

//Função para instanciar um novo IO dentro do Processo
IO novoIO(Tipo_IO tipo, int tempo_ativacao);

//Função para instanciar um novo Processo
Processo novoProcesso(int id, int tempo_servico, int instante_ativacao, int quantidade_io, IO *io);

#endif