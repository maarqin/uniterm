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
#include <fcntl.h>

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
    } else if (strcmp(comando, "novodir") == 0) {
        cod_erro = comando_novodir(parametros);
    } else if (strcmp(comando, "apagadir") == 0) {
        cod_erro = comando_apagadir(parametros);
    } else if (strcmp(comando, "mudadir") == 0) {
        cod_erro = comando_mudadir(parametros);
    } else {
        cod_erro = lancar_programa(comando, parametros);
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

    strftime(resultado, sizeof (resultado), "São %H:%M de %d/%m/%Y", tmp);

    printf("%s\n", resultado);

    return 0;
}

int comando_arquivos() {

    struct dirent **arquivos;
    int n;

    n = scandir(".", &arquivos, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while (n--) {
            printf("%s\n", arquivos[n]->d_name);
        }
        free(arquivos);
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

    int result;
    const char *nome = nome_prog;
    result = access(nome, F_OK);
    if (result < 0) {
        printf("Comando ou programa '%s' inexistente.\n", nome_prog);
        return 1;
    } else if (result == 0) {
        result = access(nome, X_OK);
        if (result < 0) {
            printf("Arquivo '%s' não tem permissão para execução.\n", nome_prog);
            return 1;
        } else if (result == 0) {
            pid_t pid = fork();
            int status;
            if (pid < 0) {
                perror("fork() falhou\n");
                return 1;
            }
            
            // Executar outros programas

            if (pid == 0) {
                execv(nome_prog, NULL);
            } else {
                waitpid(pid, &status, 0);
                if( status > 0 ){
                    printf("ERRO: o programa indicou termino com falha!\n");
                }
            }

            return 0;
        }
    }

    return 1;
}


