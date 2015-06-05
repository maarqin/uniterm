#include "uniterm.h"

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

const int TAMANHO_COMANDO = 21;
const int TAMANHO_PARAMETROS = 201;

void uniterm_laco_principal() {

    while (true) {
        char comando[TAMANHO_COMANDO], parametros[TAMANHO_PARAMETROS];

        digitar_prompt();
        ler_comando(comando, parametros);
        executar_comando(comando, parametros);
    }
}

void digitar_prompt() {
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    char *dir = getwd(NULL);
    
    printf("%d:%s@%s > ", pw->pw_uid, pw->pw_name, dir);    
}

void ler_comando(char * comando, char * parametros) {

    char cmd_typed[TAMANHO_COMANDO + TAMANHO_PARAMETROS];
    char c;
    int x = 0;
    // Reading datas from user
    while ((c = getchar()) != '\n') {
        cmd_typed[x++] = c;
    }
    cmd_typed[x] = '\0';

    // Partition between command and params
    int p = 0;
    while ((p < TAMANHO_COMANDO) &&
            (cmd_typed[p] != ' ')) {

        comando[p] = cmd_typed[p];
        p++;
    }
    comando[p++] = '\0';

    int i = 0;
    while ((i < TAMANHO_PARAMETROS) && (cmd_typed[p] != '\0')) {

        parametros[i] = cmd_typed[p];
        p++;
        i++;
    }
    parametros[i] = '\0';
}

void executar_comando(char * comando, char * parametros) {
    int cod_erro = 0;
    
    if (strcmp(comando, "terminar") == 0) {
        cod_erro = comando_terminar();
    } else if (strcmp(comando, "datahora") == 0) {
        cod_erro = comando_datahora();
    } else if (strcmp(comando, "arquivos") == 0) {
        cod_erro = comando_arquivos();
    } else if ( strcmp(comando, "novodir") == 0 ) {
        cod_erro = comando_novodir(parametros);
    } else if ( strcmp(comando, "apagadir") == 0 ) {
        cod_erro = comando_apagadir(parametros);
    } else if ( strcmp(comando, "mudadir") == 0 ) {
        cod_erro = comando_mudadir(parametros);
    } else if ( strcmp(comando, "limpar") == 0 ) {
        system("clear");
    } else if( strcmp(comando, "") != 0 ) {
        printf("-uniterm: %s: Comando não encontrado\n", comando);
    }
    /* Outros comandos continuam aqui, similares aos acima */
}

int comando_terminar() {
    printf("Good bye.\n");
    pid_t pid = getpid();
    kill(pid, SIGKILL);
    return 0;
}

int comando_datahora() {

    char resultado[200];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);

    strftime(resultado, sizeof (resultado), "%d/%m/%Y às %H:%M", tmp);

    printf("%s\n", resultado);

    return 0;
}

int comando_arquivos() {

    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while (n--) {
            printf("%s\n", namelist[n]->d_name);
        }
        free(namelist);
    }

    return 0;
}

int comando_novodir(char * nome_dir) {

    mode_t permission = 0777;
    mkdir(nome_dir, permission);
    return 0;
}

int comando_apagadir(char * nome_dir) {
    
    rmdir(nome_dir);
    return 0;
}

int comando_mudadir(char * nome_dir) {

    chdir(nome_dir);
    return 0;
}

int lancar_programa(char * nome_prog, char * parametros) {
    printf("Funcionalidade ainda nao implementada pelo aluno.");
    return 1;
}

