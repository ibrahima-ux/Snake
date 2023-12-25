### VARIABLES ###

CC = gcc
CFLAGS = -ansi \
         -pedantic \
         -lgraph
EXE = Snake
OFILES = snake.o \
         elSnake.o
 
### BUT PAR DEFAUT ###
 
but : ${EXE}
 
### REGLES ESSENTIELLES ###
 
snake.o : snake.c
 
elSnake.o : elSnake.c
 
${EXE} : ${OFILES}
	$(CC) $(CFLAGS) -o ${EXE} ${OFILES}
 
### REGLES OPTIONNELLES ###
 
clean :
	-rm -f ${OFILES}
