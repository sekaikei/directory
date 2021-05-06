####################### Makefile #######################
# GRR20190475 - Vinicius Hideyoshi Correa Yoshida
########################################################

# exeutaveis
EXE = myavl

# object files
OBJS = $(C_SOURCE:.c=.o)

# compilador
CC = gcc 

# flags pro compilador
CFLAGS = -Wall

# compilacao e dependencia
all: $(EXE)

myavl: avl.o myavl.o

# targets dependem do .c e do .h
avl.o: avl.c avl.h

# remove arquivos temporarios
clean:
	-rm -f *.o *~

# remove tudo o que nao for codigo fonte
purge: clean
	-rm -f $(EXE)