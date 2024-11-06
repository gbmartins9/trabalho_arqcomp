#include "../include/commons.h"

//TODO: Também temos que garantir que tempo restante <= tempo de serviço sempre. 
//TODO: Implementar instante de ativação corretamente.
//TODO: Implementar inicialização da lista de IOs. 
Processo novoProcesso(int id, int tempo_servico, int prioridade, int quantidade_io, IO io[]) {
    Processo p;
    p.id = id;
    p.tempo_servico = tempo_servico; 
    p.tempo_restante = tempo_servico; 
    p.prioridade = prioridade;
    p.instante_ativacao = 0; //! MUDAR
    if (io != NULL) {p.io = io;}
    p.quantidade_io = quantidade_io;
    return p;
}

//TODO: Mudar o tipo do IO para uma string com o nome
void mostraIO(IO io[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf(" [%d; %d; %d] ", io[i].tipo, io[i].tempo_execucao, io[i].tempo_ativacao);
    }
    printf("\n");
}

void mostraProcesso(Processo p) {
    printf("\nProcesso #%d: ", p.id);
    printf("\n\tTempo de Servico: %d", p.tempo_servico);
    printf("\n\tTempo Restante: %d", p.tempo_restante);
    printf("\n\tPrioridade: %d", p.prioridade);
    printf("\n\tIOs: ");
    mostraIO(p.io, p.quantidade_io);
    printf("\n");
}

IO novoIO(Tipo_IO tipo, int tempo_execucao, int tempo_ativacao) {
    IO io;
    io.tipo = tipo;
    io.tempo_execucao = tempo_execucao;
    io.tempo_ativacao = tempo_ativacao;
    io.tempo_retorno = 0;
    return io;
}