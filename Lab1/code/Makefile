# Compiling the Hamming Code Program
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
OUTPUT_FLAG=-o
TASK_1_EXEC=task1.exe
TASK_1_SRC=task1.c
prog:
	$(CC) $(TASK_1_SRC) $(CFLAGS) $(OUTPUT_FLAG) $(TASK_1_EXEC)

exec: prog
	./$(TASK_1_EXEC)

clean:
	rm $(TASK_1_EXEC)