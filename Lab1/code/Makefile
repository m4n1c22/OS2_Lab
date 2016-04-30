#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=-c
CWFLAGS=--std=c99 -Wall -Werror -O1
OUTPUT_FLAG=-o
TASK_1_EXEC=task1.exe
TASK_1_OBJ=task1.o
TASK_1_SRC=task1.c
TASK_1_SHELL_SCR=task1_1.sh

$(TASK_1_OBJ):
	$(CC) $(CFLAGS) $(TASK_1_SRC) $(CWFLAGS)

prog: $(TASK_1_OBJ)
	$(CC) $(OUTPUT_FLAG) $(TASK_1_EXEC) $(TASK_1_OBJ)

exec: prog
	./$(TASK_1_EXEC)

test: prog
	sh $(TASK_1_SHELL_SCR)
clean:
	rm *.o *.exe