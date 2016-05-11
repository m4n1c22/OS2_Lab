#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
OBJFLAG=-c
OUTPUT_FLAG=-o
TASK_1_SRC = task1.c
TASK_1_SHELL_SCR = task1_1.sh
OUT_TASK_1_FILE = prog.bin

TASK_1_3_SRC = task1_3.c
TASK_1_3_SHELL_SCR = task1_3.sh
OUT_TASK_1_3_FILE = prog_1_3.bin


#Default target which is executed
all: exec

#Target to execute the shell script described in task1.1
test: prog
	sh $(TASK_1_SHELL_SCR)

#Target to execute the task1.2
exec: prog	
	./$(OUT_TASK_1_FILE)

#Target for internal dependency
prog: $(TASK_1_SRC)
	$(CC) $(CFLAGS) $(TASK_1_SRC) $(OUTPUT_FLAG) $(OUT_TASK_1_FILE)

#Target to execute the shell script described in task1.3
test_task1_3: prog_1_3
	sh $(TASK_1_3_SHELL_SCR)

#Target to execute the task1.3
exec_1_3: prog_1_3	
	./$(OUT_TASK_1_3_FILE)

#Target for internal dependency
prog_1_3: $(TASK_1_3_SRC)
	$(CC) $(CFLAGS) $(TASK_1_3_SRC) $(OUTPUT_FLAG) $(OUT_TASK_1_3_FILE)

#Clean up the code.
clean:
	rm -f *.bin *.o
