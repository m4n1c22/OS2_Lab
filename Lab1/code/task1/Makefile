#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
OBJFLAG=-c
OUTPUT_FLAG=-o
TASK_1_SRC=task1.c
TASK_1_SHELL_SCR=task1_1.sh

#Default target which is executed
all: exec

#Target to execute the shell script described in task1.1
test: prog
	sh $(TASK_1_SHELL_SCR)

#Target to execute the task1.2
exec: prog	
	./prog

#Target for internal dependency
prog: 
	$(CC) $(CFLAGS) $(TASK_1_SRC) $(OUTPUT_FLAG) $@

#Clean up the code.
clean:
	rm -f prog