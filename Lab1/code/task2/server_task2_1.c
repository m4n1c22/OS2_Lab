/** 
	\file		:	server_task2_1.c
	\author		:	Sreeram Sadasivam
	\brief		:	Task 2 for Operating Systems:Dependability & Trust Lab - 
					Design a simple stateless server program to process client requests.
	\copyright	:	Copyrights reserved @2016
*/

/**Define BSD SOURCE FOR <GLIBC 2.12. Since Compilation done with option std=c99. Used in regard with usleep().*/
#define _BSD_SOURCE

/**MACROS*/
#define DEFAULT_MAX_RESTARTS 	5

/**Standard Headerfiles*/
#include <stdio.h>
#include <stdlib.h>

/**Headerfiles for Family of Wait system calls*/
#include <sys/wait.h>		
/**Headerfiles defined for the system types encountered.*/
#include <sys/types.h>
/**usleep Header file*/
#include <unistd.h>

/**Storage variable for the number of restarts encountered by the parent server process.*/
int num_of_restarts=0;


int backup(int max_restarts) {

	/**Storage variable for Return values from the system functions: fork, waitpid*/
	int ret_val_fork, ret_val_wait;

	/**Storage variable for the child exit status*/
	int child_exit_status;

	for (;;)
	{
		num_of_restarts++;
		/**Verify if the fork limit is reached or not.*/
		if(num_of_restarts > max_restarts){
			
			fprintf(stderr, "Error:Fork function limit reached and failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;	
		}

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
			printf("server %d\n", getpid());	
			return EXIT_SUCCESS;
		}
		

		/**Parent process block.*/
		ret_val_wait = waitpid(ret_val_fork, &child_exit_status, 0);
		/**Waitpid function fails*/
		if(ret_val_wait<0) {
			fprintf(stderr, "Error:waitpid function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
	}	
	return EXIT_SUCCESS;

}

int request_processing(int max_restarts) {

	printf("Server Process has begun processing the requests...\n");
	if(backup(max_restarts)==EXIT_SUCCESS) {
		printf("successfully executed...\n");
		return EXIT_SUCCESS;
	}
	else {		
		fprintf(stderr, "Error:Backup cannot be created.\nParent server process PID:%d taking control.\n",getpid());
		return EXIT_FAILURE;
	}
}

int main(int argc, char const *argv[])
{
	int max_restarts;

	/**
		Check if the argument count is 3 or 1. If the argc is 1, it means assume default value as 5.
		Else, pass the limit for forks with option -n within a range 1-50.
	*/
	if((argc!=3)&&(argc!=1)) {
		printf("Invalid usage of the command prog.\nUsage: prog -n <N> where N is a number in the range 1-50");
		return EXIT_FAILURE;
	}
	/**Assume default argument.*/
	else if(argc == 1) {
		max_restarts = DEFAULT_MAX_RESTARTS;
	} else {
		max_restarts = atoi(argv[argc-1]);
		if((max_restarts>50)||(max_restarts<1)) {

			fprintf(stderr, "Error:Max Restarts out of range. Expected range 1-50\n");
			return EXIT_FAILURE;
		}
	}
	/**Invoking the request processing method.*/
	if(request_processing(max_restarts)==EXIT_SUCCESS) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}
