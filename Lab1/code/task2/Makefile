#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
DIR_CFLAG=-D_BSD_SOURCE
OUTPUT_FLAG=-o
SERVER_SRC_task2_1=server_task2_1.c
SERVER_SRC_task2_2=server_task2_2.c
CLIENT_SRC_task2_2=client_task2_2.c
OUTPUT_SERVER_TASK_2_1=server_task_2_1.bin
OUTPUT_SERVER_TASK_2_2=server_task_2_2.bin
OUTPUT_CLIENT_TASK_2_2=client_task2_2.bin
TASK_2_SHELL_SCR=task2_1.sh

#Target for internal dependency in task 2_1 and compiling the server code in task2_1
comp_server_task_2_1:
	$(CC) $(CFLAGS) $(SERVER_SRC_task2_1) $(OUTPUT_FLAG) $(OUTPUT_SERVER_TASK_2_1)
#Target for internal dependency in task 2_2 and compiling the server code in task2_2
comp_server_task_2_2:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(SERVER_SRC_task2_2) $(OUTPUT_FLAG) $(OUTPUT_SERVER_TASK_2_2)
#Target for internal dependency in task 2_2 and compiling the client code in task2_2
comp_client_task2_2:
	$(CC) $(CFLAGS) $(DIR_CFLAG) $(CLIENT_SRC_task2_2) $(OUTPUT_FLAG) $(OUTPUT_CLIENT_TASK_2_2)	

#Target to execute the shell script described in task2_1
test_task_2_1: comp_server_task_2_1
	sh $(TASK_2_SHELL_SCR)

#Target to execute the shell script described in task2_2
test_task_2_2: comp_server_task_2_2
	sh $(TASK_2_SHELL_SCR)

#Target to execute the task2_1 server program.
server_exec_task_2_1: comp_server_task_2_1
	./$(OUTPUT_SERVER_TASK_2_1)

#Target to execute the server program for task2_2
server_exec_task_2_2: comp_server_task_2_2	
	./$(OUTPUT_SERVER_TASK_2_2)


#Target to execute client program for task2_2
client_exec_task_2_2: comp_client_task2_2	
	./$(OUTPUT_CLIENT_TASK_2_2)


#Clean up the code.
clean:
	rm -f *.bin
