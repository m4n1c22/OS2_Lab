/** 
	\file		:	server_task3_1.c
	\author		:	Sreeram Sadasivam, Gizem Güleşir
	\brief		:	Task 2.3 for Operating Systems:Dependability & Trust Lab - 
					Design a simple stateless server program to process client requests.
	\copyright	:	Copyrights reserved @2016
*/

/**MACROS*/
#define DEFAULT_MAX_RESTARTS 		5
#define DEFAULT_FAILURE_CHANCE		0
#define READ_END					0
#define WRITE_END					1

/**Standard Headerfiles*/
#include <stdio.h>
#include <stdlib.h>

/**Headerfiles for Family of Wait system calls*/
#include <sys/wait.h>		
/**Headerfiles defined for the system types encountered.*/
#include <sys/types.h>
/**usleep Header file*/
#include <unistd.h>
/**String Header file*/
#include <string.h>
/**Directory Header File*/
#include <dirent.h>
/**time header for random number seed*/
#include <time.h>
/**signal header file for use of signaling between processes .*/
#include <signal.h>
/**errno header file for detecting EPIPE error.*/
#include <errno.h>

/**Storage variable for the number of restarts encountered by the parent server process.*/
int num_of_restarts=0;
/**File descriptor used between parent and child processes for communication (read, write).*/
int pipefd[2];

/* close the file descriptor, 0 for closing read side, 1 for closing write side */
int closePipe(int close_end) {

	int ret_val_close = close(pipefd[close_end]);
	if(ret_val_close < 0) {
		fprintf(stderr, "Error: close function failed.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int backup(int max_restarts) {

	/**Storage variable for Return values from the system functions: fork, waitpid, pipe*/
	int ret_val_fork, ret_val_wait, ret_val_pipe;

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
			Pipe is created for process pair communication between
			the parent and child process. pipefd, file descriptor
			given as an input, pipefd[0] is used for reading from pipe
			pipefd[1] is used for writing to the pipe.
		*/

		ret_val_pipe = pipe(pipefd);
		if (ret_val_pipe < 0) {
			fprintf(stderr, "Error: pipe function failed.\n");
			/** process returns and terminates with error */
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
		if (ret_val_fork < 0) {

			fprintf(stderr, "Error:Fork function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
		/**Child process gets the return value from fork as 0*/
		else if (ret_val_fork == 0) {
			/**	child closes unused read end of the pipe, since it
			  	will only use the write end of the pipe.
			*/
			closePipe(READ_END);
			/** Print the process id of the child(server) process to the console.
			*/
			printf("server %d\n", getpid());	
			return EXIT_SUCCESS;
		}
		

		/**Parent process block.*/
		/**Parent process closes write end of the pipe, since it will
	           only use the read end of the pipe.
		*/
		closePipe(WRITE_END);
		ret_val_wait = waitpid(ret_val_fork, &child_exit_status, 0);
		/**Waitpid function fails*/
		if(ret_val_wait<0) {
			fprintf(stderr, "Error:waitpid function failed.\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
		/**Before exiting, parent process closes read end of the pipe.
		*/
		closePipe(READ_END);
	}	
	return EXIT_SUCCESS;
}

/** 	Function for detecting parent process failure. Child function sends polling messages until
	read side of the pipe at parent process is open. When write function fails at child side,
	child can conclude that parent has crashed or terminated, therefore it resets the execution
	of the program and it becomes the new parent.
*/
int backupTerminated (int fd[2], int max_restarts, int failure_chance) {

	/**Storage variable for return values from the system functions: write, usleep and execl.*/
	int ret_val_write,ret_val_usleep,ret_val_execl;
	/**Heartbeat message which client periodically sends to the parent in order to detect and failure.*/
	char poll_message[] = "I am alive\n";

	char c_arg1[100], c_arg2[100];

	/**Reduce the polling frequency.*/
	ret_val_usleep = usleep(500000);
	/**Failure in usleep call.*/
	if(ret_val_usleep < 0) {
		fprintf(stderr, "Error: usleep function failed.\n");
		/**Process returns and terminates with error.*/
		return EXIT_FAILURE;
	}	
	/**Child writes the message in the poll_message array to the pipe.*/
	ret_val_write = write(fd[1], poll_message, strlen(poll_message));
	if (ret_val_write < 0) {
		fprintf(stderr, "Error from %d: write function failed.\n", getpid());
		/** Detecting the EPIPE error, which happens when the read end of the pipe is closed.*/
		ret_val_write = errno;
		if (errno == EPIPE) {
			printf("From id %d: Parent (backup) process failed\n", getpid());
			/** 	Child (server) process closes write end of the pipe, before resetting the
				program.
			*/
			closePipe(WRITE_END);
			
			/**Convert max restart and failure chance into char *.*/
			if(sprintf(c_arg1,"%d",max_restarts)<0) {
				fprintf(stderr, "Error:STDOUT failed.");
				return EXIT_FAILURE;			
			}
			if(sprintf(c_arg2,"%d", failure_chance)<0) {
				fprintf(stderr, "Error:STDOUT failed.");
				return EXIT_FAILURE;			
			}

			ret_val_execl = execl("./server_task3_1.bin", "server_task3_1.bin", "-n", c_arg1, "-f", c_arg2, (char *)NULL);
			if(ret_val_execl < 0) {
				fprintf(stderr, "Error: execl function failed.\n");
				/**Process returns and terminates with error.*/
				return EXIT_FAILURE;
			}
		}
		/**Process returns and terminates with error.*/
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
int removeRequest(char *req_file_name) {

	if (unlink(req_file_name)!=0)
	{
		fprintf(stderr, "Error:Unlink failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int readRequest(char *req_file_name, int failure_chance) {

	FILE *fp = fopen(req_file_name,"r");

	if(fp == NULL) {
		fprintf(stderr, "Error:File Open failed.");
		return EXIT_FAILURE;
	}

	printf("Failure rate %d\n", failure_chance);

	if (strstr(req_file_name,"fail")!=NULL) {
		int random_number;
		int failure_rate= 0;
		//srand(time(NULL));
		random_number = rand();
		if(failure_chance!=0) {
			failure_rate = 100/failure_chance;
			if (random_number % failure_rate == 0){
				fprintf(stderr, "Error:Child process failed.");
				return EXIT_FAILURE;
			}
		}
	}

	printf("Server: %d req %s\n", getpid(), req_file_name);
	fclose(fp);
	return EXIT_SUCCESS;
}

int server(int max_restarts, int failure_chance) {

	DIR *dirp;
	int ret_val_usleep, ret_backup;

	struct dirent *dp;

	printf("Server Process has begun processing the requests...\n");
	ret_backup = backup(max_restarts);
	if(ret_backup == EXIT_SUCCESS) {
		printf("successfully executed...\n");		

	}
	else {		
		fprintf(stderr, "Error:Backup cannot be created.\nParent server process PID:%d taking control.\n",getpid());
	}
	
	while(1) {
		/**Open the current directory.*/
		dirp = opendir("./requests");
		while(dirp) {
			char request_name[100]="requests/";
			if(ret_backup == EXIT_SUCCESS) {
				backupTerminated(pipefd, max_restarts, failure_chance);
				//printf("successfully executed...\n");		

			}	    
    		if ((dp = readdir(dirp)) != NULL) {
        		//printf("Directory Name: %s\n", dp->d_name);
        		if ((strstr(dp->d_name,"req_")!=NULL)&&(dp->d_type == DT_REG))
        		{
        			if(strcat(request_name,dp->d_name)==NULL) {
        				fprintf(stderr, "Error:String Concatenation function failed.\n");
        				return EXIT_FAILURE;	
        			}

        			if(readRequest(request_name, failure_chance)==EXIT_FAILURE) {
        				fprintf(stderr, "Error:readRequest function failed.\n");
        				return EXIT_FAILURE;
        			}

        			if(removeRequest(request_name)==EXIT_FAILURE) {
						fprintf(stderr, "Error:removeRequest function failed.\n");
        				return EXIT_FAILURE;
        			}
					ret_val_usleep = usleep(500000);
					/**Failure in usleep call.*/
					if(ret_val_usleep<0) {
						
						fprintf(stderr, "Error:Usleep function failed.\n");
						/**Process returns and terminates with error.*/
						return EXIT_FAILURE;
					}
        		}
    		}
    		else {
    			break;
    		}        
		}
		/**Close the requests directory.*/
		closedir(dirp);
	}
	return EXIT_SUCCESS;
}

int main(int argc, char const *argv[])
{
	int max_restarts=-1, failure_chance=-1;
	/** 	Ignore SIGPIPE signal, so that child process gets error when it attemps to write to the pipe
		which the other side is closed by parent process, due to failure, crash etc.
	*/
        signal(SIGPIPE, SIG_IGN);
	/**
		Check if the argument count is 4 or 1. If the argc is 1, it means assume default value as 5 and 0 for
		max restarts and failure chance respectively.
		Else, pass the limit for forks with option -n within a range 1-50 and -f failure option.
	*/
	if((argc!=5)&&(argc!=1)&&((argc!=3))) {
		printf("Invalid usage of the command prog.\nUsage: prog -n <N> -f <F> where N is a number in the range 1-50\nF is a number in the range of 0-100");
		return EXIT_FAILURE;
	}
	/**Assume default argument.*/
	else if(argc == 1) {
		failure_chance = DEFAULT_FAILURE_CHANCE;
		max_restarts = DEFAULT_MAX_RESTARTS;

	} else if(argc == 3) {
		if(strcmp(argv[argc-2],"-n")==0) {
			
			failure_chance=DEFAULT_FAILURE_CHANCE;
			max_restarts = atoi(argv[argc-1]);
			if((max_restarts>50)||(max_restarts<1)) {

				fprintf(stderr, "Error:Max Restarts out of range. Expected range 1-50\n");
				return EXIT_FAILURE;
			}	
		}
		else if(strcmp(argv[argc-2],"-f")==0) {

			max_restarts = DEFAULT_MAX_RESTARTS;				
			failure_chance = atoi(argv[argc-1]);
			if((failure_chance>100)||(failure_chance<0)) {

				fprintf(stderr, "Error:Failure Chance out of range. Expected range 0-100\n");
				return EXIT_FAILURE;
			}
		}
		
	} else if((strcmp(argv[argc-2],"-f")==0)&&(strcmp(argv[argc-4],"-n")==0)) {
		max_restarts = atoi(argv[argc-3]);
		if((max_restarts>50)||(max_restarts<1)) {

			fprintf(stderr, "Error:Max Restarts out of range. Expected range 1-50\n");
			return EXIT_FAILURE;
		}
		failure_chance = atoi(argv[argc-1]);			
		if((failure_chance>100)||(failure_chance<0)) {

				fprintf(stderr, "Error:Failure Chance out of range. Expected range 0-100\n");
				return EXIT_FAILURE;
		}
	} else if((strcmp(argv[argc-2],"-n")==0)&&(strcmp(argv[argc-4],"-f")==0)) {
		max_restarts = atoi(argv[argc-1]);
		if((max_restarts>50)||(max_restarts<1)) {

			fprintf(stderr, "Error:Max Restarts out of range. Expected range 1-50\n");
			return EXIT_FAILURE;
		}
		failure_chance = atoi(argv[argc-3]);			
		if((failure_chance>100)||(failure_chance<0)) {

				fprintf(stderr, "Error:Failure Chance out of range. Expected range 0-100\n");
				return EXIT_FAILURE;
		}
	} else {
		printf("Invalid usage of the command prog.\nUsage: prog -n <N> -f <F> where N is a number in the range 1-50\nF is a number in the range of 0-100");
		return EXIT_FAILURE;	
	}

	/**Invoking the request processing method.*/
	if(server(max_restarts, failure_chance)==EXIT_SUCCESS) {
		return EXIT_SUCCESS;
	}
	else {
		fprintf(stderr, "Error:Testing Task3 has failed.\n");
		return EXIT_FAILURE;
	}
}
