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




void mostrarFila(Fila *f, const char *nome) {
    No *aux = f->inicio;
    printf("Fila %s: ", nome);
    while (aux != NULL) {
        printf(" [%d] ", aux->processo.id);
        aux = aux->proximo_processo;
    }
    printf("\n");
}


//! TIRAR ESSA FUNÇÃO
/*
? OBS: se tirarmos as checagens de f1 == NULL ou f2 == NULL, acho que podemos 
? fazer retornar void.
*/ 
bool atualizaPrioridade(Fila *f1, Fila *f2) {
    if (f1 == NULL || f2 == NULL) {
        return false;
    }
    else {
        if (f1->inicio == NULL) {
            f1->inicio = f2->inicio;
            f1->fim = f2->fim;
        }
        else {
            f1->fim->proximo_processo = f2->inicio;
            f1->fim = f2->fim;
        } 
        f2->inicio = NULL;
        f2->fim = NULL;
        return true;
    }
}