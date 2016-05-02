####OS LAB

####Objective:
Understanding concept of Process Pairs

####Code 
#####Structure
The folder contains: 
- Makefile 
- task1.c - Implementation of task1 C Program. 
- task1_1.sh - Implementation of task1_1 shell script to execute the C Program in task1.c. 

#####Build & Run
 
Makefile is meant to build the various tasks in the given folder.
For compiling the tasks use the command ```make```. 
If you run ```make``` without target, it will build all the targets.
Thus, compiling all tasks.

######Steps to run Task 1
 - ```make exec``` will execute the task1 by invoking the fork method call once. Which internally 
 creates a parent-child relationship. It invokes the executable named ***prog***
 - ```make test``` will execute the shell script ***task1_1.sh*** provided in the folder. The script will generate 
 5 calls to the executable ***prog*** generate after compilation.
 - ```make clean``` will clear all the executables from the folder.
 - ```make prog``` will compile the source code and generate the executable in the name referenced as ***prog***.
 
 
 For more details refer the [document](https://github.com/m4n1c22/OS2_Lab/blob/master/Lab1/doc/lab1-process-pairs.pdf)
 
