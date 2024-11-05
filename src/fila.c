#include "../include/commons.h"
#include "../include/fila.h"

/*  
? OBS: não sei se as checagens de f == NULL são realmente necessárias, pois em tese já 
? checaremos após criarmos a fila se f retornou NULL ou não.
*/

Fila *inicializaFila(int identificador) {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    if (f == NULL) {
        return NULL;
    }
    else {
        f->inicio = NULL;
        f->fim = NULL;
        f->identificador = identificador;
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
    if (f == NULL || f->inicio == NULL) {
        return false;
    }
    else {
        No *deletar = f->inicio;
        *p = f->inicio->processo;
        f->inicio = f->inicio->proximo_processo;

        if (f->inicio == NULL) {
            f->fim = NULL;
        }

        free(deletar);
        return true;        
    }
}

void mostrarFila(Fila *f) {
    No *aux = f->inicio;
    printf("Fila %d: ", f->identificador);
    while (aux != NULL) {
        printf(" [%d] ", aux->processo.id);
        aux = aux->proximo_processo;
    }
    printf("\n");
}

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