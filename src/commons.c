#include "../include/commons.h"

Processo novoProcesso(int id, int tempo_servico, int tempo_restante, int prioridade) {
    Processo p;
    p.id = id;
    p.tempo_servico = tempo_servico;
    p.tempo_restante = tempo_restante;
    p.prioridade = prioridade;
    return p;
}

void mostraProcesso(Processo p) {
    printf("\nProcesso #%d: ", p.id);
    printf("\n\tTempo de Servico: %d", p.tempo_servico);
    printf("\n\tTempo Restante: %d", p.tempo_restante);
    printf("\n\tPrioridade: %d", p.prioridade);
    printf("\n");
}