#include "../include/commons.h"
#include "../include/fila.h"

Fila* leituraTeste(char *nome_teste) {

    // Abertura do arquivo
    FILE *teste;
    teste = fopen(nome_teste, "r");
    
    // Inicialização da fila de pendentes que será retornada
    Fila *pendentes = inicializaFila();

    // Variável que receberá cada linha do arquivo
    char linha[100]; 

    // Essa variável servirá somente para abrigar uma flag temporária.
    char flag;
    
    // Teste para verificar se o arquivo foi aberto corretamente
    if (teste == NULL) printf("\nErro ao abrir arquivo!\n");

    // Para cada linha do arquivo
    while (fgets(linha, sizeof(linha), teste)) {
        // Verifica se é uma linha de I/O. Se for, pula para a próxima.
        if (linha[0] == 'F') continue;

        // Lê os parâmetros para a criação do processo.
        int id, tempo_servico, instante_ativacao, quant_ios;
        sscanf(linha, "%d; %d; %d; %d;", &id, &tempo_servico, &instante_ativacao, &quant_ios);

        // Leitura dos I/O, caso houver (quantidade de ios não for 0).
        IO io[quant_ios];
        if (quant_ios != 0) {
            // Para cada I/O da linha seguinte
            for (int i = 0; i < quant_ios; i++) {
                int tipo, tempo_execucao, tempo_ativacao; 
                // Lê os parâmetros para a criação do I/O.
                fgets(linha, sizeof(linha), teste);
                sscanf(linha, "%c; %d; %d; %d;", &flag, &tipo, &tempo_execucao, &tempo_ativacao);
                // Cria um novo I/O e adiciona ao vetor de I/O do processo.
                IO novo = novoIO(tipo, tempo_execucao, tempo_ativacao);
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

int main() {
    
    Fila *pendentes = leituraTeste("tests/1.txt");
    
    return 0;
}