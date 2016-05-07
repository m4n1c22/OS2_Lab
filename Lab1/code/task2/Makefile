#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
DIR_CFLAG=-D_BSD_SOURCE
OUTPUT_FLAG=-o
SERVER_SRC_task2_1=server_task2_1.c
SERVER_SRC_task2_2=server_task2_2.c
OUTPUT_TASK_2_1=prog_task_2_1.bin
OUTPUT_TASK_2_2=prog_task_2_2.bin
TASK_2_SHELL_SCR=task2_1.sh

#Target for internal dependency in task 2_1
prog_task_2_1:
	$(CC) $(CFLAGS) $(SERVER_SRC_task2_1) $(OUTPUT_FLAG) $(OUTPUT_TASK_2_1)
#Target for internal dependency in task 2_1
prog_task_2_2:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(SERVER_SRC_task2_2) $(OUTPUT_FLAG) $(OUTPUT_TASK_2_2)


#Target to execute the shell script described in task2_1
test_task_2_1: prog_task_2_1
	sh $(TASK_2_SHELL_SCR)

#Target to execute the shell script described in task2_2
test_task_2_2: prog_task_2_2
	sh $(TASK_2_SHELL_SCR)

#Target to execute the task2_1
exec_task_2_1: prog_task_2_2	
	./prog_task_2_1.bin

#Target to execute the task2_2
exec_task_2_2: prog_task_2_2	
	./prog_task_2_2.bin

#Clean up the code.
clean:
	rm -f *.bin
