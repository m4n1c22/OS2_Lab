/** 
	\file		:	task1.c
	\author		:	Sreeram Sadasivam
	\brief		:	Task 1 for Operating Systems:Dependability & Trust Lab - 
					Design a simple program to perform the creation of a 
					parent-child relationship using fork() and wait function calls.
	\copyright	:	Copyrights reserved @2016
*/

/**Define BSD SOURCE FOR <GLIBC 2.12. Since Compilation done with option std=c99. Used in regard with usleep().*/
#define _BSD_SOURCE

/**Standard Headerfiles*/
#include <stdio.h>
#include <stdlib.h>

/**Headerfiles for Family of Wait system calls*/
#include <sys/wait.h>		
/**Headerfiles defined for the system types encountered.*/
#include <sys/types.h>
/**usleep Header file*/
#include <unistd.h>


int test_task1() {

	/**Storage variable for Return values from the system functions: fork, waitpid, usleep*/
	int ret_val_fork, ret_val_wait, ret_val_usleep;

	int child_exit_status;
	/**
		Parent Process calls fork() to generate a child process.
		If the function call is successful, child's PID is returned
		to the parent process. And the value 0 is returned to child.
		Since there is a limit in the number of forkable user processes,
		there is a need to perform error handling.
	*/
	ret_val_fork = fork();
	/**Fork function fails*/
	if (ret_val_fork<0) {

		fprintf(stderr, "Error:Fork function failed.\n");
		/**Process returns and terminates with error*/
		return EXIT_FAILURE;
	}
	/**Child process gets the return value from fork as 0*/
	else if (ret_val_fork == 0)
	{
		/**Slow down the processes.*/
		ret_val_usleep = usleep(250000);
		/**Failure in usleep call*/
		if(ret_val_usleep<0) {
			
			fprintf(stderr, "Error:Usleep function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
		printf("I am the child process. My PID is %d\n", getpid());	
		/**Slow down the child process to prolong its execution.*/
		ret_val_usleep = usleep(500000);
		/**Failure in usleep call*/
		if(ret_val_usleep<0) {
			
			fprintf(stderr, "Error:Usleep function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
	}
	/**Parent process block.*/
	else {
		/**Slow down the processes.*/
		ret_val_usleep = usleep(250000);
		/**Failure in usleep call*/
		if(ret_val_usleep<0) {
			
			fprintf(stderr, "Error:Usleep function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
		printf("I am the parent process. My PID is %d\n", getpid());
		printf("Creation of child successful. Child's PID is %d\n", ret_val_fork);
		
		ret_val_wait = waitpid(ret_val_fork, &child_exit_status, 0);
		/**Waitpid function fails*/
		if(ret_val_wait<0) {
			fprintf(stderr, "Error:waitpid function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
		else if(ret_val_wait==ret_val_fork){
			if(WIFEXITED(child_exit_status)){
				printf("Termination of child successful with status:%d. Child's PID was %d\n", WEXITSTATUS(child_exit_status), ret_val_fork);
			}
			if(!WIFEXITED(child_exit_status)){
				printf("Child exited abnormally with status:%d. Child's PID was %d\n", child_exit_status, ret_val_fork);
			}
		}
		else {
			fprintf(stderr,"Error: waitpid has returned a positive value which is not the pid of child we were waiting for");
		}
	}

	return EXIT_SUCCESS;

}

int main(int argc, char const *argv[])
{
int ret_val_test_task1;
	ret_val_test_task1 = test_task1();
	if(ret_val_test_task1 != EXIT_SUCCESS) {
		fprintf(stderr, "Error:Testing Task1 Failed.\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
