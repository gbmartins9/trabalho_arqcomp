#include "../include/commons.h"

//TODO: Também temos que garantir que tempo restante <= tempo de serviço sempre. 
//TODO: Implementar instante de ativação corretamente.
//TODO: Implementar inicialização da lista de IOs. 
Processo novoProcesso(int id, int tempo_servico, int instante_ativacao, int prioridade, int quantidade_io, IO io[]) {
    Processo p;
    p.id = id;
    p.tempo_servico = tempo_servico; 
    p.tempo_restante = tempo_servico; 
    p.prioridade = prioridade;
    p.instante_ativacao = instante_ativacao;
    if (io != NULL) {p.io = io;}
    p.quantidade_io = quantidade_io;
    p.estado = NOVO; // Estado inicial
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

IO novoIO(Tipo_IO tipo, int tempo_ativacao) {
    IO io;
    io.tipo = tipo;

    switch(tipo) {
        case 0:
            io.tempo_execucao = 7;
            break;
        case 1:
            io.tempo_execucao = 8;
            break;
        case 2:
            io.tempo_execucao = 4;
            break;
        default:
            //TODO: Botar mensagem de que não existe o tipo de IO passado
            io.tempo_execucao = 0;
            break;
    }

    io.tempo_ativacao = tempo_ativacao;
    io.tempo_retorno = -1;
    return io;
}