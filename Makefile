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

#OBJS guarda todos os meus objects .o
OBJS = main.o uniterm.o
OBJS_HW = ola_mundo.o 
OBJS_BW = adeus_mundo.o

#BIN
EXEC = main ola_mundo adeus_mundo

all: default ola_mundo adeus_mundo

default: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main
	
main.o: main.c uniterm.h
	$(CC) $(CFLAGS) -c main.c

uniterm.o: uniterm.c uniterm.h
	$(CC) $(CFLAGS) -c uniterm.c

ola_mundo: $(OBJS_HW)
	$(CC) $(CFLAGS) $(OBJS_HW) -o ola_mundo
	
ola_mundo.o: ola_mundo.c
	$(CC) $(CFLAGS) -c ola_mundo.c
	
adeus_mundo: $(OBJS_BW)
	$(CC) $(CFLAGS) $(OBJS_BW) -o adeus_mundo
	
adeus_mundo.o: adeus_mundo.c
	$(CC) $(CFLAGS) -c adeus_mundo.c

clean:
	rm -f *.o $(EXEC)