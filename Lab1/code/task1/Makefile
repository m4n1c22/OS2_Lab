#MakeFile for task 1 in OS2 Lab-1

#Compiler macro
CC=gcc

#Compiler flags
CFLAGS=--std=c99 -Wall -Werror -O1
OUTPUT_FLAG=-o

#Source code specifier for task1
TASK_1_SRC = task1.c
TASK_1_3_SRC = task1_3.c

#Output files for task1
OUT_TASK_1_FILE = prog.bin
OUT_TASK_1_3_FILE = prog_1_3.bin

#Test Scripts for task1
TASK_1_SHELL_SCR = task1_1.sh
TASK_1_3_SHELL_SCR = task1_3.sh

#Default target which is executed
all: prog prog_1_3

#Target to execute the shell script described in task1.1
test: prog
	sh $(TASK_1_SHELL_SCR)

#Target to execute the task1.2
exec: prog	
	./$(OUT_TASK_1_FILE)

#Target for internal dependency in task 1
prog:
	$(CC) $(CFLAGS) $(TASK_1_SRC) $(OUTPUT_FLAG) $(OUT_TASK_1_FILE)

#Target to execute the shell script described in task1.3
test_task1_3: prog_1_3
	sh $(TASK_1_3_SHELL_SCR)

#Target to execute the task1.3
exec_1_3: prog_1_3	
	./$(OUT_TASK_1_3_FILE)

#Target for internal dependency in task 1.3
prog_1_3: $(TASK_1_3_SRC)
	$(CC) $(CFLAGS) $(TASK_1_3_SRC) $(OUTPUT_FLAG) $(OUT_TASK_1_3_FILE)

#Clean up the code.
clean:
	rm -f *.bin *.o
#clean up the log files
cleanlog:
	rm -f *.log
#Clean up everything
cleanall: clean cleanlog

.PHONY: all clean cleanall cleanlog  test exec prog prog_1_3 exec_1_3 test_task1_3