#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "../include/commons.h"
#include "../include/fila.h"

//Faz a leitura de um arquivo texto
//Contendo os atributos dos processos 
//Que serão utilizados no simulador.
//Retorna a fila com todos os processos
//Pendentes
Fila* lerArquivo(char *nome_arquivo);

//Mostra os processos lidos do arquivo
//No formato de uma tabela, para facilitar
//a apresentação 
void printProcessos(Fila *pendentes);

#endif