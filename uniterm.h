#ifndef UNITERM_H
#define UNITERM_H

/**
 * Funcao principal do UniTerm.
 */
void uniterm_laco_principal();

/**
 * Escreve o prompt na saida padrao.
 */
void digitar_prompt();

/**
 * Preenche as strings comando e parametros com a entrada do usuario do terminal.
 * A primeira palavra digitada eh sempre o nome do comando desejado. Quaisquer
 * outras palavras subsequentes sao parametros para o comando. A palavras sao
 * separadas pelo caractere de espaco ' '. A leitura de um comando eh feita ate
 * que o usuario pressione a tecla <ENTER>, ou seja, ate que seja lido o caractere
 * EOL (End Of Line).
 *
 * 'comando' pode ter no maximo 20 caracteres, e contem uma unica palavra.
 * 'parametros' pode ter ate 200 caracteres e pode contar nenhuma ou varias palavras.
 */
void ler_comando(char * comando, char * parametros);


/**
 * Recebe o comando lido e os parametros, verifica se eh um comando conhecido e,
 * se for, o executa.
 * 
 * Se nao for, verifica se eh o nome de um programa terceiro
 * localizado no diretorio atual de trabalho. Se for, cria um novo processo e o
 * executa. Enquanto esse processo executa, o processo do uniterm fica em espera.
 *
 * Se nao for nenhuma das situacoes anteriores, exibe uma mensagem de comando ou
 * programa desconhecido.
 */
void executar_comando(char * comando, char * parametros);


int comando_terminar();
int comando_datahora();
int comando_arquivos();
int comando_novodir(char * nome_dir);
int comando_apagadir(char * nome_dir);
int comando_mudadir(char * nome_dir);

int lancar_programa(char * nome_prog, char * parametros);

struct dirent *arquivos();

#endif

