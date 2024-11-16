#include "../include/commons.h"
#include "../include/fila.h"

/*  
? OBS: não sei se as checagens de f == NULL são realmente necessárias, pois em tese já 
? checaremos após criarmos a fila se f retornou NULL ou não.
*/

Fila *inicializaFila() {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    if (f == NULL) {
        return NULL;
    }
    else {
        f->inicio = NULL;
        f->fim = NULL;
        return f;
    }
}

No *novoNo(Processo p) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        return NULL;
    }
    else {
        (*novo).processo = p;
        novo->proximo_processo = NULL;
        return novo;
    }
}

int tamanhoFila(Fila *f) {
    if (f == NULL) {
        return -1; //! Fila não foi iniciada corretamente.
    }

    No *atual = f->inicio;
    int tamanho = 0;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo_processo;
    }
    return tamanho;
}

bool inserirFila(Fila *f, Processo p) {
    if (f == NULL) {
        return false;
    }
    else {
        No *novo = novoNo(p);
        if(novo == NULL) {
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

bool removerFila(Fila *f, Processo *p) {
    if (f == NULL || f->inicio == NULL || p == NULL) {
        return false;
    }

    No *atual = f->inicio;
    No *anterior = NULL;

    // Percorre a fila até encontrar o processo com o mesmo ID
    while (atual != NULL && atual->processo.id != p->id) {
        anterior = atual;
        atual = atual->proximo_processo;
    }

    // Se o processo não foi encontrado, retorna false
    if (atual == NULL) {
        return false;
    }

    // Se o processo está no início da fila
    if (anterior == NULL) {
        f->inicio = atual->proximo_processo;
    } else {
        anterior->proximo_processo = atual->proximo_processo;
    }

    // Se o processo está no fim da fila, atualiza f->fim
    if (atual == f->fim) {
        f->fim = anterior;
    }

    free(atual);
    return true;
}

Processo removerFila3(Fila *f, int id) {
    if (f == NULL || f->inicio == NULL) {
        Processo p_vazio = {0}; // Retorna um processo vazio indicando falha
        return p_vazio;
    }

    No *atual = f->inicio;
    No *anterior = NULL;

    // Percorre a fila até encontrar o processo com o mesmo ID
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

    // Se o processo está no fim da fila, atualiza f->fim
    if (atual == f->fim) {
        f->fim = anterior;
        if (anterior != NULL) {
            anterior->proximo_processo = NULL;
        }
    }

    Processo p = atual->processo;
    // printf("Processo: %d\n", p.id);

    free(atual);
    return p;
}


Processo removerFila2(Fila *f) {
    if (f->inicio == NULL) return;
    Processo p = f->inicio->processo;
    No *deletar = f->inicio;
    f->inicio = f->inicio->proximo_processo;
    free(deletar);
    if(f->inicio == NULL) f->fim = NULL;
    return p;
}




void mostrarFila(Fila *f, const char *nome) {
    No *aux = f->inicio;
    printf("Fila %s: ", nome);
    while (aux != NULL) {
        printf(" [%d] ", aux->processo.id);
        aux = aux->proximo_processo;
    }
    printf("\n");
}


//Função que adiciona o processo na fila de IO, calculando o tempo de retorno com base no tempo atual
void inserirFilaIO(Processo *p, int i, int tempo_atual) {
    inserirFila(io, *p);
    //printf("Processo P%d foi para fila de I/O\n", p->id);
    p->io[i].tempo_retorno = tempo_atual + p->io[i].tempo_execucao;
}

//Função que remove um processo da fila de IO e o redireciona para a fila correta.
void removerFilaIO(Processo *p, int i) {
    int tipoIO = p->io[i].tipo;
    //! INCONSISTÊNCIA: ESTAMOS REMOVENDO UM CARA ESPECÍFICO MAS A FILA REMOVE O PRIMEIRO    
    //removerFila(io, p);
    Processo temp = removerFila3(io, p->id);
    
    printf("\n");
    switch (tipoIO) {
        case 0:
            inserirFila(fila_baixa, temp);
            printf("-> Processo P%d completou I/O de disco e foi para fila de baixa prioridade\n", temp.id);
            break;
        case 1:
            inserirFila(fila_alta, temp);
            printf("-> Processo P%d completou I/O de fita e foi para fila de alta prioridade\n", temp.id);
            break;
        case 2:
            inserirFila(fila_alta, temp);
            printf("-> Processo P%d completou I/O de impressora e foi para fila de alta prioridade\n", temp.id);
            break;
    }
}