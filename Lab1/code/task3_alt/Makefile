#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
DIR_CFLAG=-D_BSD_SOURCE
OUTPUT_FLAG=-o

SERVER_SRC_TASK3_1=server_task3_1.c

CLIENT_SRC_TASK3_1=client_task3_1.c

OUTPUT_SERVER_TASK3_1=server_task3_1.bin

OUTPUT_CLIENT_TASK3_1=client_task3_1.bin

TASK3_1_SHELL_SCR=task3_2.sh

#Target to compile all internal depenndencies
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