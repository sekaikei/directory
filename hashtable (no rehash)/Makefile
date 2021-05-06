####################### Makefile #######################
# GRR20190475 - Vinicius Hideyoshi Correa Yoshida
########################################################

# exeutaveis
EXE = myht

# compilador
CC = gcc 

# flags pro compilador
CFLAGS = -Wall

# compilacao e dependencia
all: $(EXE)

myht: hashtable.o myht.o

# targets dependem do .c e do .h
hashtable.o: hashtable.c hashtable.h

# remove arquivos temporarios
clean:
	-rm -f *.o *~

# remove tudo o que nao for codigo fonte
purge: clean
	-rm -f $(EXE)