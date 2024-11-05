#include "../include/commons.h"

//TODO: Na inicialização, tempo restante = tempo de serviço. 
//TODO: Também temos que garantir que tempo restante <= tempo de serviço sempre. 
//TODO: Implementar instante de ativação corretamente.
Processo novoProcesso(int id, int tempo_servico, int prioridade) {
    Processo p;
    p.id = id;
    p.tempo_servico = tempo_servico; 
    p.tempo_restante = tempo_servico; 
    p.prioridade = prioridade;
    p.instante_ativacao = 0; //! MUDAR
    return p;
}

void mostraProcesso(Processo p) {
    printf("\nProcesso #%d: ", p.id);
    printf("\n\tTempo de Servico: %d", p.tempo_servico);
    printf("\n\tTempo Restante: %d", p.tempo_restante);
    printf("\n\tPrioridade: %d", p.prioridade);
    printf("\n");
}