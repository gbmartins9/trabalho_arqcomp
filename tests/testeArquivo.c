#include "../include/commons.h"
#include "../include/fila.h"

void mostraProcesso(Processo p) {
    printf("\nProcesso #%d: ", p.id);
    printf("\n\tTempo de Servico: %d", p.tempo_servico);
    printf("\n\tTempo Restante: %d", p.tempo_restante);
    printf("\n\tIOs: ");
    mostraIO(p.io, p.quantidade_io);
    printf("\n");
}

void mostraIO(IO io[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf(" [%d; %d] ", io[i].tipo, io[i].tempo_ativacao);
    }
    printf("\n");
}

Fila* lerTeste(char *nome_teste) {

    // Abertura do arquivo
    FILE *teste;
    teste = fopen(nome_teste, "r");
    
    // Inicialização da fila de pendentes que será retornada
    Fila *pendentes = inicializaFila();

    // Variável que receberá cada linha do arquivo
    char linha[100]; 
    
    // Teste para verificar se o arquivo foi aberto corretamente
    if (teste == NULL) printf("\nErro ao abrir arquivo!\n");

    // Para cada linha do arquivo
    while (fgets(linha, sizeof(linha), teste)) {
        // Verifica se é uma linha de I/O. Se for, pula para a próxima.
        if (linha[0] == ';') continue;

        // Lê os parâmetros para a criação do processo.
        int id, tempo_servico, instante_ativacao, quant_ios;
        sscanf(linha, "%d; %d; %d; %d;", &id, &tempo_servico, &instante_ativacao, &quant_ios);

        // Leitura dos I/O, caso houver (quantidade de ios não for 0).
        IO *io = NULL;
        if (quant_ios > 0) {
            io = malloc(quant_ios * sizeof(IO));
            // Para cada I/O da linha seguinte
            for (int i = 0; i < quant_ios; i++) {
                int tipo, tempo_execucao, tempo_ativacao; 
                // Lê os parâmetros para a criação do I/O.
                fgets(linha, sizeof(linha), teste);
                sscanf(linha, "; %d; %d; %d;", &tipo, &tempo_execucao, &tempo_ativacao);
                // Cria um novo I/O e adiciona ao vetor de I/O do processo.
                IO novo = novoIO(tipo, tempo_ativacao);
                io[i] = novo;
            }
        }
        // Insere o processo na fila de pendentes.
        inserirFila(pendentes, novoProcesso(id, tempo_servico, instante_ativacao, quant_ios, io));
    }
    // Fecha o arquivo teste.
    fclose(teste);
    // Retorna nossa lista final dos processos criados.
    return pendentes;
}

void printTeste(char *nome_teste) {

    // Inicializamos lista de teste para receber o arquivo.
    Fila *teste = lerTeste(nome_teste);

    // Nó que usaremos para iterar sobre a lista teste.
    No *atual = teste->inicio;

    // Vetor que fará a "tradução" do tipo numérico para textual do I/O.
    const char *tipoIOStrings[] = {"DISCO", "FITA", "IMPRESSORA"};
    
    // Cabeçalho da tabela
    printf("+----------+------------------+-------------------+-----------------------------------------------+------------------------+\n");
    printf("| Processo | Instante Ativ.   | Tempo de Servico  | Instantes de tempo das operacoes de I/O       | Tipo de operacao de I/O|\n");
    printf("+----------+------------------+-------------------+-----------------------------------------------+------------------------+\n");

    // Iterando os processos na fila.
    while (atual) {

        // Variável que recebe o processo a cada iteração.
        Processo p = atual->processo;

        // Primeira linha do processo.
        printf("| P%d       | %-16d | %-17d |", p.id, p.instante_ativacao, p.tempo_servico);

        // Verificação de I/O.
        if (p.quantidade_io > 0) {
            printf(" %-41d     | %-22s |\n", p.io[0].tempo_ativacao, tipoIOStrings[p.io[0].tipo]);

            // Outras linhas dos IOs (se houver mais de 1)
            for (int i = 1; i < p.quantidade_io; i++) {
                printf("|          |                  |                   | %-41d     | %-22c |\n", p.io[i].tempo_ativacao, tipoIOStrings[p.io[0].tipo]);
            }
        } else {
            // Sem IOs
            printf(" %-41s     | %-22s |\n", "-", "-");
        }

        // Linha de separação entre processos
        printf("+----------+------------------+-------------------+-----------------------------------------------+------------------------+\n");

        // Próximo processo.
        atual = atual->proximo_processo;
    }
}


int main() {
    
    printTeste("tests/1.txt");
    
    return 0;
}