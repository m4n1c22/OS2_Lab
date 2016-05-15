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
/**time header for random number seed*/
#include <time.h>


int test_task1_3() {

	/**Storage variable for Return values from the system functions: fork, waitpid, usleep*/
	int ret_val_fork, ret_val_wait, ret_val_usleep;
	/**Storage variable for checking the child process exit status.*/
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
		/**Storage variable for random number*/
		int random_number;
		/**Creating seed for the random number generator.*/
		srand(time(NULL));
		/**Generating the random number.*/
		random_number = rand();
		/**Checking if the random number is divisible by 2. Indirectly making a failure rate of 50%*/
		if (random_number % 2 == 0){
			/**Process returns and terminates with success.*/
			return EXIT_SUCCESS;
		}
		else {
			/**Child process terminates with exit code.*/
			exit(-1);
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
		
		/**Waitpid function is invoked where parent process waits for the child.*/
		ret_val_wait = waitpid(ret_val_fork, &child_exit_status, 0);
		/**Waitpid function fails*/
		if(ret_val_wait<0) {
			fprintf(stderr, "Error:waitpid function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
		else if(ret_val_wait==ret_val_fork){
			/**Check if the child process terminated successfully or not.*/
			if(child_exit_status!=EXIT_SUCCESS) {
				fprintf(stderr,"Error: Child exited abnormally with status:%d. Child's PID was %d\n", child_exit_status, ret_val_fork);
				/**Process returns and terminates with error*/
				return EXIT_FAILURE;
			}

			else {
				printf("Termination of child successful with status:%d. Child's PID was %d\n", WEXITSTATUS(child_exit_status), ret_val_fork);
				return EXIT_SUCCESS;
			}
		}
		else {
			fprintf(stderr,"Error: waitpid has returned a positive value which is not the pid of child we were waiting for");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
	}
	/**Process returns and terminates with success.*/
	return EXIT_SUCCESS;

}
/**Main Function with command line arguments.*/
int main(int argc, char const *argv[])
{
	/**Storage variable for return values from the method call to test_task1()*/
	int ret_val_test_task1_3;
	/**Invoking task1 function.*/
	ret_val_test_task1_3 = test_task1_3();
	/**Check if the function executed successfully or not.*/
	if(ret_val_test_task1_3 != EXIT_SUCCESS) {
		fprintf(stderr, "Error:Testing Task1 Failed.\n");
		/**Process returns and terminates with error*/
		return EXIT_FAILURE;
	}
	/**Process returns and terminates with success*/
	return EXIT_SUCCESS;
}
