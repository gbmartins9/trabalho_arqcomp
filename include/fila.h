#ifndef FILA_H
#define FILA_H

//*BIBLIOTECAS E HEADERS*//

#include "commons.h"

//*DEFINIÇÕES*//

//Definição da struct de Nó de uma fila
typedef struct no {
    Processo processo;
    struct no *proximo_processo;
} No;

//Definição da struct de fila
typedef struct {
    No *inicio;
    No *fim;
} Fila;

//Definição das três filas como variáveis globais
//Assim, é possível usá-las em todo o código
//Sem nos preocupar em passá-las como ponteiros
extern Fila *fila_baixa;
extern Fila *fila_alta;
extern Fila *io;

//*FUNÇÕES BÁSICAS DE FILA*//

//Inicializa uma Fila, colocando seus ponteiros para NULL.
//Retorna NULL se não conseguir inicializar. 
Fila *inicializaFila();

//Cria um novo nó contendo o processo p. 
No *novoNo(Processo p);

//Função para mostrar todos os processos da fila. 
void mostrarFila(Fila *f, const char *nome);

//*FUNÇÕES DE INSERÇÃO/REMOÇÃO EM FILAS*//

//Insere um processo na Fila, e retorna se conseguiu ou não. 
bool inserirFila(Fila *f, Processo p);

//Remove o primeiro processo da Fila, e o retorna. 
//Se não tiver nenhum processo, retorna um processo
//Vazio. 
Processo removerFila(Fila *f);

//Remove o processo com o id igual ao passado como argumento.
//Se estiver vazia ou não encontrar, retorna um processo 
//Vazio. Usado como auxílio para função removerFilaIO.
Processo removerFilaEspecifico(Fila *f, int id);


//*FUNÇÕES PARA FILA DE I/O*//

//Adiciona o processo na fila de IO,
//Calculando o tempo de retorno com base no tempo atual
void inserirFilaIO(Processo *p, int i, int tempo_atual);

//Remove um processo específco da fila de IO,
//E o redireciona para a fila correta.
void removerFilaIO(Processo *p, int i);

#endif