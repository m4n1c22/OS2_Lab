#MakeFile for the OS2 Lab-1

#Compiler macro
CC=gcc

#Compiler flags
CFLAGS=--std=c99 -Wall -Werror -O1
DIR_CFLAG=-D_BSD_SOURCE
OUTPUT_FLAG=-o

#Source Code Specifiers for server and client versions of various tasks.
SERVER_SRC_TASK3_1=server_task3_1.c
CLIENT_SRC_TASK3_1=client_task3_1.c

#Output Specifier for various tasks-server and client versions.
OUTPUT_SERVER_TASK3_1=server_task3_1.bin
OUTPUT_CLIENT_TASK3_1=client_task3_1.bin

#Test script specifier for various tasks.
TASK3_1_SHELL_SCR=task3_2.sh
PARENT_PROCESS_CRASH=parent_process_crash.sh

#Target to compile all internal dependencies.
all: comp_server_task3_1 comp_client_task3_1

#Target for internal dependency in task 3_1 and compiling the server code in task3_1
comp_server_task3_1:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(SERVER_SRC_TASK3_1) $(OUTPUT_FLAG) $(OUTPUT_SERVER_TASK3_1)
	
#Target for internal dependency in task 3_1 and compiling the client code in task3_1
comp_client_task3_1:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(CLIENT_SRC_TASK3_1) $(OUTPUT_FLAG) $(OUTPUT_CLIENT_TASK3_1)	

#Target to execute the shell script described in task3_1
test: comp_server_task3_1 comp_client_task3_1
	sh $(TASK3_1_SHELL_SCR)

#Target to execute the shell script for crashing the parent process described in task3
parent_crash:
	sh $(PARENT_PROCESS_CRASH)

#Target to execute the server program for task3_1
server_exec_task3_1: comp_server_task3_1	
	./$(OUTPUT_SERVER_TASK3_1)

#Target to execute client program for task3_1
client_exec_task3_1: comp_client_task3_1	
	./$(OUTPUT_CLIENT_TASK3_1)

#Clean up the code.
clean:
	rm -f *.bin *.o
#clean up the log files
cleanlog:
	rm -f *.log
#Clean up everything
cleanall: clean cleanlog

.PHONY: all clean cleanall cleanlog comp_client_task3_1 comp_server_task3_1 test parent_crash server_exec_task3_1 client_exec_task3_1