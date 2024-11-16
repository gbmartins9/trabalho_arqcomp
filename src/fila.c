#include "../include/commons.h"
#include "../include/fila.h"

//*FUNÇÕES BÁSICAS DE FILA*//

//Inicializa uma Fila, colocando seus ponteiros para NULL.
//Retorna NULL se não conseguir inicializar. 
Fila *inicializaFila() {
    Fila *f = (Fila *) malloc(sizeof(Fila));

    if (f == NULL) {
        printf("\nErro: nao foi possivel inicializar a fila!\n");
        return NULL;
    }

    else {
        f->inicio = NULL;
        f->fim = NULL;
        return f;
    }
}

//Cria um novo nó contendo o processo p. 
No *novoNo(Processo p) {
    No *novo = (No *) malloc(sizeof(No));

    if (novo == NULL) {
        printf("\nErro: nao foi possivel inicializar o processo P%d!\n", p.id);
        return NULL;
    }

    else {
        (*novo).processo = p;
        novo->proximo_processo = NULL;
        return novo;
    }
}

//Mostra todos os processos da fila. 
void mostrarFila(Fila *f, const char *nome) {
    No *aux = f->inicio;

    printf("Fila %s: ", nome);
    while (aux != NULL) {
        printf(" [%d] ", aux->processo.id);
        aux = aux->proximo_processo;
    }
    
    printf("\n");
}

//*FUNÇÕES DE INSERÇÃO/REMOÇÃO EM FILAS*//

//Insere um processo na Fila, e retorna se conseguiu ou não. 
bool inserirFila(Fila *f, Processo p) {

    if (f == NULL) {
        printf("\nErro: uma fila vazia foi passada como argumento da funcao inserirFila para o processo P%d!\n", p.id);
        return false;
    }

    else {
        No *novo = novoNo(p);
        if(novo == NULL) {
            printf("\nErro: nao foi possivel inicializar o processo P%d na funcao inserirFila!\n", p.id);
            return false;
        }

        else {

            if (f->inicio == NULL) {
                f->inicio = novo;
            }
            
            else {
                f->fim->proximo_processo = novo;
            }
            
            f->fim = novo;
            return true;
        }
    }
}

//Remove o primeiro processo da Fila, e o retorna. 
//Se não tiver nenhum processo, retorna um processo
//vazio. 
Processo removerFila(Fila *f) {
    if (f == NULL || f->inicio == NULL) {
        printf("\nErro: Tentativa de remover um processo de uma fila vazia em removerFila\n");
        Processo p_vazio = {0};
        return p_vazio;
    }

    Processo p = f->inicio->processo;
    No *deletar = f->inicio;
    
    f->inicio = f->inicio->proximo_processo;
    
    free(deletar);
    
    if(f->inicio == NULL) {
        f->fim = NULL;
    }

    return p;
}

//Remove o processo com o id igual ao passado como argumento.
//Se estiver vazia ou não encontrar, retorna um processo 
//Vazio. Usado como auxílio para função removerFilaIO.
Processo removerFilaEspecifico(Fila *f, int id) {
    if (f == NULL || f->inicio == NULL) {
        printf("\nErro: Tentativa de remover um processo de uma fila vazia em removerFila\n");
        Processo p_vazio = {0};
        return p_vazio;
    }

    No *atual = f->inicio;
    No *anterior = NULL;

    // Percorre a fila até encontrar o processo com o mesmo id
    while (atual != NULL && atual->processo.id != id) {
        anterior = atual;
        atual = atual->proximo_processo;
    }

    // Se o processo não foi encontrado, retorna um processo vazio
    if (atual == NULL) {
        Processo p_vazio = {0};
        return p_vazio;
    }

    // Se o processo está no início da fila
    if (anterior == NULL) {
        f->inicio = atual->proximo_processo;
    } else {
        anterior->proximo_processo = atual->proximo_processo;
    }

    // Se o processo está no fim da fila
    if (atual == f->fim) {
        f->fim = anterior;
        if (anterior != NULL) {
            anterior->proximo_processo = NULL;
        }
    }

    Processo p = atual->processo;

    free(atual);

    return p;
}

//*FUNÇÕES PARA FILA DE I/O*//

//Adiciona o processo na fila de IO,
//Calculando o tempo de retorno com base no tempo atual.
void inserirFilaIO(Processo *p, int i, int tempo_atual) {
    inserirFila(io, *p);
    p->io[i].tempo_retorno = tempo_atual + p->io[i].tempo_execucao;
}

//Remove um processo específco da fila de IO,
//E o redireciona para a fila correta.
void removerFilaIO(Processo *p, int i) {
    int tipoIO = p->io[i].tipo;
    Processo temp = removerFilaEspecifico(io, p->id);
    
    printf("\n");
    switch (tipoIO) {
        case DISCO:
            inserirFila(fila_baixa, temp);
            printf("-> Processo P%d completou I/O de disco e foi para fila de baixa prioridade\n", temp.id);
            break;
        case FITA:
            inserirFila(fila_alta, temp);
            printf("-> Processo P%d completou I/O de fita e foi para fila de alta prioridade\n", temp.id);
            break;
        case IMPRESSORA:
            inserirFila(fila_alta, temp);
            printf("-> Processo P%d completou I/O de impressora e foi para fila de alta prioridade\n", temp.id);
            break;
    }
}