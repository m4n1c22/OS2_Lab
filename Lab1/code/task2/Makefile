#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
OUTPUT_FLAG=-o
SERVER_SRC=server_task2_1.c
TASK_2_SHELL_SCR=task2_1.sh

#Target for internal dependency
prog:
	$(CC) $(CFLAGS) $(SERVER_SRC) $(OUTPUT_FLAG) $@

#Target to execute the shell script described in task2
test: prog
	sh $(TASK_2_SHELL_SCR)

#Target to execute the task2
exec: prog	
	./prog
#Clean up the code.
clean:
	rm -f prog
