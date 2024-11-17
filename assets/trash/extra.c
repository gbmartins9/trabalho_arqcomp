// #include "../include/extra.h"

void mostraIO(IO io[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf(" [%d; %d] ", io[i].tipo, io[i].tempo_ativacao);
    }
    printf("\n");
}
void mostraProcesso(Processo p) {
    printf("\nProcesso #%d: ", p.id);
    printf("\n\tTempo de Servico: %d", p.tempo_servico);
    printf("\n\tTempo Restante: %d", p.tempo_restante);
    printf("\n\tIOs: ");
    mostraIO(p.io, p.quantidade_io);
    printf("\n");
}
