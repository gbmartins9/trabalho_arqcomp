#include "../include/commons.h"

//! TEMOS QUE VER O QUE OCORRE NOS CASOS DEGENERADOS
//! PROPONHO AVISAR QUE NÃO SERÁ EXECUTADO AQUELE IO, MAS CONTINUAR COM 
//! O SIMULADOR

//Função para instanciar um novo IO dentro do Processo
IO novoIO(Tipo_IO tipo, int tempo_ativacao) {

    //Criamos um novo IO
    IO io;

    //Atribuímos à ele seu tipo
    io.tipo = tipo;

    //Com base no tipo, associamos à ele seu tempo de execução,
    //Baseando-nos nas premissas
    switch(tipo) {
        case DISCO:
            io.tempo_execucao = 7;
            break;
        
        case FITA:
            io.tempo_execucao = 8;
            break;
        
        case IMPRESSORA:
            io.tempo_execucao = 4;
            break;

        default:
            //Se o tipo não for um dos pré-existentes, definimos seu tempo de ativação
            //Como -1, para nunca ser executado, e o retornamos
            printf("\n-> O tipo de IO passado nao existe! Este IO nao sera executado\n");
            io.tempo_ativacao = -1;
            io.tempo_execucao = 0;
            io.tempo_retorno = -1;
            return io;
    }

    //Caso o tipo de IO tenha sido encontrado,
    //Definimos o tempo de ativação, E o tempo
    //De retorno como -1, já que este será atualizado futuramente
    io.tempo_ativacao = tempo_ativacao;
    io.tempo_retorno = -1;

    //Então, o retornamos
    return io;
}

Processo novoProcesso(int id, int tempo_servico, int instante_ativacao, int quantidade_io, IO io[]) {

    //Criamos um novo processo
    Processo p;

    //Definimos os atributos básicos do processo
    //Note que o tempo restante é o tempo de serviço inicialmente
    p.id = id;
    p.tempo_servico = tempo_servico; 
    p.tempo_restante = tempo_servico; 
    p.instante_ativacao = instante_ativacao;
    
    //Atribuímos a quantidade de IOs e o vetor com os IOs para o processo
    //Checamos se a lista não está vazia, e se nenhum dos tempos de ativação
    //Dos IOs supera o tempo de serviço do processo.
    p.quantidade_io = quantidade_io;

    if (io != NULL) {
        p.io = io;
    }

    for (int i = 1; i <= quantidade_io; i++) {
        if(tempo_servico < p.io[i-1].tempo_ativacao) {
            printf("\n-> O tempo de ativacao do IO %d do processo P%d supera seu tempo de servico\nEste IO nao sera executado!\n", i, id);
        }
    }

    //Então, retornamos o processo p
    return p;
}