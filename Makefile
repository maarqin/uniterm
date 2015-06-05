######################################
#Makefile| make| make clear|
#
#@Author  Marcos Vinicius Thomaz
#@Author  Adilson Aguillera
#@Version 04/06/2015
#
######################################

#Variaveis#

#O compilador a ser usado
CC=clang

#Para nao silenciar os warnings
CFLAGS= -Wall

#OBJS guarda todos os meus objcts .o
OBJS = main.o uniterm.o

#BIN
EXEC = main

all: default

default: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

main.o: main.c uniterm.h
	$(CC) $(CFLAGS) -c main.c

uniterm.o: uniterm.c uniterm.h
	$(CC) $(CFLAGS) -c uniterm.c

clean:
	rm -f *.o $(EXEC)