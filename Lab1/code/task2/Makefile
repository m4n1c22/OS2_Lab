#MakeFile for Task 2 in OS2 Lab-1

#Compiler macro
CC=gcc

#Compiler flags
CFLAGS=--std=c99 -Wall -Werror -O1
DIR_CFLAG=-D_BSD_SOURCE
OUTPUT_FLAG=-o

#Source Code Specifiers for server and client versions of various tasks.
SERVER_SRC_TASK2_1=server_task2_1.c
SERVER_SRC_TASK2_2=server_task2_2.c
SERVER_SRC_TASK2_3=server_task2_3.c

CLIENT_SRC_TASK2_2=client_task2_2.c
CLIENT_SRC_TASK2_3=client_task2_3.c

#Output Specifier for various tasks-server and client versions.
OUTPUT_SERVER_TASK2_1=server_task2_1.bin
OUTPUT_SERVER_TASK2_2=server_task2_2.bin
OUTPUT_SERVER_TASK2_3=server_task2_3.bin

OUTPUT_CLIENT_TASK2_2=client_task2_2.bin
OUTPUT_CLIENT_TASK2_3=client_task2_3.bin

#Test script specifier for various tasks.
TASK2_1_SHELL_SCR=task2_1.sh
TASK2_2_SHELL_SCR=task2_2.sh
TASK2_3_SHELL_SCR=task2_3.sh

#Target to compile all internal dependency
all: comp_server_task2_1 comp_server_task2_2 comp_server_task2_3 comp_client_task2_2 comp_client_task2_3

#Target for internal dependency in task 2_1 and compiling the server code in task2_1
comp_server_task2_1:
	$(CC) $(CFLAGS) $(SERVER_SRC_TASK2_1) $(OUTPUT_FLAG) $(OUTPUT_SERVER_TASK2_1)
#Target for internal dependency in task 2_2 and compiling the server code in task2_2
comp_server_task2_2:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(SERVER_SRC_TASK2_2) $(OUTPUT_FLAG) $(OUTPUT_SERVER_TASK2_2)
#Target for internal dependency in task 2_3 and compiling the server code in task2_3
comp_server_task2_3:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(SERVER_SRC_TASK2_3) $(OUTPUT_FLAG) $(OUTPUT_SERVER_TASK2_3)


#Target for internal dependency in task 2_2 and compiling the client code in task2_2
comp_client_task2_2:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(CLIENT_SRC_TASK2_2) $(OUTPUT_FLAG) $(OUTPUT_CLIENT_TASK2_2)	
#Target for internal dependency in task 2_3 and compiling the client code in task2_3
comp_client_task2_3:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(CLIENT_SRC_TASK2_3) $(OUTPUT_FLAG) $(OUTPUT_CLIENT_TASK2_3)	


#Target to execute the shell script described in task2_1
test_task2_1: comp_server_task2_1
	sh $(TASK2_1_SHELL_SCR)

#Target to execute the shell script described in task2_2
test_task2_2: comp_server_task2_2
	sh $(TASK2_2_SHELL_SCR)

#Target to execute the shell script described in task2_3
test_task2_3: comp_server_task2_3
	sh $(TASK2_3_SHELL_SCR)

#Target to execute the task2_1 server program.
server_exec_task2_1: comp_server_task2_1
	./$(OUTPUT_SERVER_TASK2_1)

#Target to execute the server program for task2_2
server_exec_task2_2: comp_server_task2_2	
	./$(OUTPUT_SERVER_TASK2_2)

#Target to execute the server program for task2_3
server_exec_task2_3: comp_server_task2_3	
	./$(OUTPUT_SERVER_TASK2_3)


#Target to execute client program for task2_2
client_exec_task2_2: comp_client_task2_2	
	./$(OUTPUT_CLIENT_TASK2_2)
#Target to execute client program for task2_3
client_exec_task2_3: comp_client_task2_3	
	./$(OUTPUT_CLIENT_TASK2_3)


#Clean up the code.
clean:
	rm -f *.bin *.o
#clean up the log files
cleanlog:
	rm -f *.log
#Clean up everything
cleanall: clean cleanlog