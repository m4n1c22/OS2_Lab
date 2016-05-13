####OS LAB

####Objective:
Understanding concept of Process Pairs

####Code 
#####Structure
The folder contains subfolders task1, task2, task3, task3_alt

***task1/***-> Deals with simple parent-child relationship.
- Makefile 
- task1.c - Implementation of task1 C Program which deals with parent-child relationship. 
- task1_3.c - Implementation of task1.3 C Program which deals with parent-child relationship which generates 50%
              error in the child process. 
- task1_1.sh - Implementation of task1_1 shell script to execute the C Program in task1.c. 
- task1_3.sh - Implementation of task1_3 shell script to execute the C Program in task1_3.c. 

***task2/***-> Deals with a simple stateless server program to process client requests which makes use of process pair concept.
- Makefile 
- server_task2_1.c - Implementation stateless server program for handling task2.1 and uses process pair concept.
- server_task2_2.c - Implementation stateless server program for handling task2.2, uses process pair concept
                     and handles request processing of the various client requests.
- server_task2_3.c - Implementation stateless server program for handling task2.3, uses process pair concept
                     and handles various request processing of the client requests for a provided failure rate
                     which the server(child) process will fail.
- client_task2_2.c - Implementation client program for testing in task2.2.
- client_task2_3.c - Implementation client program for testing in task2.3. And generates filenames with fail as 
                     the substring.
- task2_1.sh - Implementation of task2_1 shell script to execute the task2.1. 
- task2_2.sh - Implementation of task2_2 shell script to execute the task2.2.
- task2_3.sh - Implementation of task2_3 shell script to execute the task2.3.

***task3/***-> Deals with a simple stateless server program to process client requests which makes use of process pair 
               with linking concept.
- Makefile 
- server_task3_1.c - Implementation stateless server program for handling task3.1, uses process pair with linking
                     concept and handles various request processing of the client requests for a provided failure 
                     rate which the server(child) process will fail. The program utilizes the concept of pipe for linking.
- client_task3_1.c - Implementation client program for testing in task3.1.
- task3_2.sh - Implementation of task3 shell script.


***task3_alt/***-> Deals with a simple stateless server program to process client requests which makes use of process pair 
               with linking concept it uses the concept of Parent Process ID instead of pipes.
- Makefile 
- server_task3_1.c - Implementation stateless server program for handling task3.1, uses process pair with linking
                     concept and handles various request processing of the client requests for a provided failure 
                     rate which the server(child) process will fail. The program utilizes the concept of
                     parent process ID for linking.
- client_task3_1.c - Implementation client program for testing in task3.1.
- task3_2.sh - Implementation of task3 shell script.


#####Build & Run

Makefile is meant to build the various tasks in the given folder.
For compiling the tasks use the command ```make```. 
If you run ```make``` without target, it will build all the targets.
Thus, compiling all tasks.

######Steps to run Task 1
 - ```make exec``` will execute the task1 by invoking the fork method call once. Which internally 
 creates a parent-child relationship. It invokes the executable named ***prog.bin***
 - ```make test``` will execute the shell script ***task1_1.sh*** provided in the folder. The script will generate 
 calls to the executable ***prog.bin*** generate after compilation.
 - ```make prog``` will compile the source code and generate the executable in the name referenced as ***prog.bin***.
 - ```make exec_1_3``` will execute the task1.3 by invoking the fork method call once. Which internally 
 creates a parent-child relationship. It invokes the executable named ***prog_1_3***
 - ```make test_task1_3``` will execute the shell script ***task1_3.sh*** provided in the folder. The script will generate 
 calls to the executable ***prog_1_3.bin*** generate after compilation.
 - ```make prog_1_3``` will compile the source code and generate the executable in the name referenced as ***prog_1_3.bin***.
 - ```make clean``` will clear all the executables from the folder.
 
######Steps to run Task 2
 - ```make comp_server_task2_1``` will compile the server source code for task2.1 and generate the executable in the name                                   referenced as ***server_task2_1.bin***.
 - ```make server_exec_task2_1``` will execute the task2.1. It invokes the executable named ***server_task2_1.bin***.
 - ```make test_task2_1``` will execute the shell script ***task2_1.sh*** provided in the folder. The script will generate 
                           calls to the executable ***server_task2_1.bin*** generate after compilation.
 - ```make comp_server_task2_2``` will compile the server source code for task2.2 and generate the executable in the name                                   referenced as ***server_task2_2.bin***. 
 - ```make server_exec_task2_2``` will execute the server program for task2.2. It invokes the executable named  
                                  ***server_task2_2.bin***. The executable expects one option and a value to be passed 
                                  via command line arguments. The invocation needs to be ```./server_task2_2.bin -n 5``` where -n is the option indicating number of forks possible and 5 is the value for the option specified.
 - ```make comp_client_task2_2``` will compile the client source code for task2.2 and generate the executable in the name                                   referenced as ***client_task2_2.bin***. 
 - ```make client_exec_task2_2``` will execute the client program for task2.2. It invokes the executable named                                              ***client_task2_2.bin***.
 - ```make test_task2_2``` will execute the shell script ***task2_2.sh*** provided in the folder. The script will generate 
                           calls to the executable ***server_task2_2.bin*** and ***client_task2_2.bin*** generate after compilation.
 - ```make comp_server_task2_3``` will compile the server source code for task2.3 and generate the executable in the name                                   referenced as ***server_task2_3.bin***. 
 - ```make server_exec_task2_3``` will execute the server program for task2.3. It invokes the executable named  
                                  ***server_task2_3.bin***. The executable expects two options and two values to be passed 
                                  via command line arguments. The invocation needs to be ```./server_task2_3.bin -n 5 -f 50``` where -n is the option indicating number of forks possible and 5 is the value for the option specified and, -f is failure rate and 50 is the rate of failure.
 - ```make comp_client_task2_3``` will compile the client source code for task2.3 and generate the executable in the name                                   referenced as ***client_task2_3.bin***. 
 - ```make client_exec_task2_3``` will execute the client program for task2.3. It invokes the executable named                                              ***client_task2_3.bin***.
 - ```make test_task2_3``` will execute the shell script ***task2_3.sh*** provided in the folder. The script will generate 
                           calls to the executable ***server_task2_3.bin*** and ***client_task2_3.bin*** generate after compilation.
   
 - ```make clean``` will clear all the executables from the folder.
 
######Steps to run Task 3 and Task 3_alt
 - ```make comp_server_task3_1``` will compile the server source code for task3.1 and generate the executable in the name                                   referenced as ***server_task3_1.bin***. 
 - ```make server_exec_task3_1``` will execute the server program for task3.1. It invokes the executable named  
                                  ***server_task3_1.bin***. The executable expects two options and two values to be passed 
                                  via command line arguments. The invocation needs to be ```./server_task3_1.bin -n 5 -f 50``` where -n is the option indicating number of forks possible and 5 is the value for the option specified and, -f is failure rate and 50 is the rate of failure.
 - ```make comp_client_task3_1``` will compile the client source code for task3.1 and generate the executable in the name                                   referenced as ***client_task3_1.bin***. 
 - ```make client_exec_task3_1``` will execute the client program for task3.1. It invokes the executable named                                              ***client_task3_1.bin***.
 - ```make test``` will execute the shell script ***task3_2.sh*** provided in the folder. The script will generate 
                           calls to the executable ***server_task3_1.bin*** and ***client_task3_1.bin*** generate after compilation.
 - ```make clean``` will clear all the executables from the folder.

 For more details refer the [document](https://github.com/m4n1c22/OS2_Lab/blob/master/Lab1/doc/lab1-process-pairs.pdf)
 
