#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
OUTPUT_FLAG=-o
TASK_1_SRC=task1.c
TASK_1_SHELL_SCR=task1_1.sh

all: exec

test: prog
	sh $(TASK_1_SHELL_SCR)

exec: prog	
	./prog

prog:
	$(CC) $(CFLAGS) $(TASK_1_SRC) $(OUTPUT_FLAG) $@

clean:
	rm -f prog