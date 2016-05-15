/** 
	\file		:	server_task2_2.c
	\author		:	Sreeram Sadasivam
	\brief		:	Task 2.2 for Operating Systems:Dependability & Trust Lab - 
					Design a simple stateless server program to process client requests.
	\copyright	:	Copyrights reserved @2016
*/

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
/**String Header file*/
#include <string.h>
/**Directory Header File*/
#include <dirent.h>

/**Storage variable for the number of restarts encountered by the parent server process.*/
int num_of_restarts=0;

/** 
	Function which creates a backup process for the given server parent process.
	Backup function forks new child process only when failure occurs.
	max_restarts is the limiting parameter which handles the number of child process being spawned. 
*/
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

/**
	Function which removes the request from the requests directory.
	The function takes req_file_name as the input for unlinking the file
	from the given location.
*/
int removeRequest(char *req_file_name) {

	/**Failure in unlink function call*/
	if (unlink(req_file_name)!=0)
	{
		fprintf(stderr, "Error:Unlink failed.");
		/**Process returns and terminates with error.*/
		return EXIT_FAILURE;
	}
	/**Process returns and terminates with success.*/
	return EXIT_SUCCESS;
}
/**
	Function which opens and processes the request.
	Request is processed by opening the request file with the filename - req_file_name
	Assumption is to have files named with substring req_ to indicate they are request files.
*/
int readRequest(char *req_file_name) {

	/**Open the request file in read mode.*/
	FILE *fp = fopen(req_file_name,"r");
	
	/**
		Check if the file open function failure. File pointer fp returns an error
		in this regard.
	*/
	if(fp == NULL) {
		fprintf(stderr, "Error:File Open failed.");
		/**Process returns and terminates with error.*/
		return EXIT_FAILURE;
	}

	printf("Server: %d req %s\n", getpid(), req_file_name);

	/**Check if the file Close operation has failed or not.*/
	if(fclose(fp)!=0) {
		fprintf(stderr, "Error:File Close failed.");
		/**Process returns and terminates with error.*/
		return EXIT_FAILURE;

	}
	/**Process returns and terminates with success.*/
	return EXIT_SUCCESS;
}

/**
	Function which handles the server process management.
	The function polls the requests directory for new requests generated
	by the client processes.
	The server process management function requires max_restarts as a limitation
	for graceful degradation.
*/
int server(int max_restarts) {

	/**Directory pointer used to point to the directory location requests.*/
	DIR *dirp;
	/**Storage variable for return variable for usleep function call.*/
	int ret_val_usleep;

	/**Directory entry pointer.*/
	struct dirent *dp;

	printf("Server Process has begun processing the requests...\n");
	/**Check for Failure in generation of backup process.*/
	if(backup(max_restarts)==EXIT_SUCCESS) {
		printf("successfully executed...\n");		
	}
	/**If backup process cannot be created. The parent process takes control.(Graceful Degradation)*/
	else {		
		fprintf(stderr, "Error:Backup cannot be created.\nParent server process PID:%d taking control.\n",getpid());
	}

	while(1) {
		/**Open the requests directory.*/
		dirp = opendir("./requests");
		/**Condition to check if the opendir function has failed or not.*/
		if(dirp==NULL) {
			fprintf(stderr, "Error:Open Directory function failed.\n");
			/**Process returns and terminates with error.*/
			return EXIT_FAILURE;	
		}

		while(dirp) {
			/**Storage variable to generate the absolute path for the request file name.*/
			char request_name[100]="requests/";
			/**
				Condition to check if the readdir function has reached end of the directory
				or not. It is a condition to detect even failures for the readdir function calls.
				readdir() returns the directory entry pointer to the next directory file inside the
				given directory location.
			*/	    
    		if ((dp = readdir(dirp)) != NULL) {
        		/**
        			Check if the request file name contains req_ as the substring in the file name.
        			And if the type of the file is Regular file or not.
        		*/        		
        		if ((strstr(dp->d_name,"req_")!=NULL)&&(dp->d_type == DT_REG))
        		{
        			/**Generating the absolute path of the request file name.*/
        			if(strcat(request_name,dp->d_name)==NULL) {
        				fprintf(stderr, "Error:String Concatenation function failed.\n");
        				return EXIT_FAILURE;	
        			}
        			/**
        				Performing readRequest Call with requesting file name and failure chance.
        				Condition checks if the readRequest call failed or not.
        			*/	
        			if(readRequest(request_name)==EXIT_FAILURE) {
        				fprintf(stderr, "Error:readRequest function failed.\n");
        				return EXIT_FAILURE;
        			}
        			/**
        				Performing removeRequest Call with requesting file name.
        				Condition checks if the removeRequest call failed or not.
        			*/	
        			if(removeRequest(request_name)==EXIT_FAILURE) {
						fprintf(stderr, "Error:removeRequest function failed.\n");
        				return EXIT_FAILURE;
        			}
        			/**Sleeping the process for 500ms.*/
					ret_val_usleep = usleep(500000);
					/**Failure in usleep call*/
					if(ret_val_usleep<0) {
						
						fprintf(stderr, "Error:Usleep function failed.\n");
						/**Process returns and terminates with error*/
						return EXIT_FAILURE;
					}
        		}
    		}
    		else {
    			/**Directory end reached.*/
    			break;
    		}        
		}
		/**Close the requests directory. Check if the close operation was successful or not.*/
		if(closedir(dirp)<0) {
			fprintf(stderr, "Error:Usleep function failed.\n");
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
	/**Storage variable for max_restarts*/
	int max_restarts;
	/**
		Check if the argument count is 3 or 1. If the argc is 1, it means assume default value as 5.
		Else, pass the limit for forks with option -n within a range 1-50.
	*/
	if((argc!=3)&&(argc!=1)) {
		printf("Invalid usage of the command server_task2_2.bin.\nUsage: server_task2_2.bin -n <N> where N is a number in the range 1-50");
		/**Process returns and terminates with error*/
		return EXIT_FAILURE;
	}
	/**Assume default argument.*/
	else if(argc == 1) {
		/**Setting default value for max_restarts*/
		max_restarts = DEFAULT_MAX_RESTARTS;
	} 
	else {
		/**Setting the passed argument for max_restarts.*/
		max_restarts = atoi(argv[argc-1]);
		/**Check if the argument passed is not the given range of 1-50 or not.*/
		if((max_restarts>50)||(max_restarts<1)) {

			fprintf(stderr, "Error:Max Restarts out of range. Expected range 1-50\n");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
		else if(strcmp(argv[argc-2],"-n")!=0) {
			printf("Invalid usage of the command server_task2_2.bin.\nUsage: server_task2_2.bin -n <N> where N is a number in the range 1-50");
			/**Process returns and terminates with error*/
			return EXIT_FAILURE;
		}
	}
	/**Invoking the request processing method.*/
	if(server(max_restarts)==EXIT_SUCCESS) {
		/**Process returns and terminates with success*/
		return EXIT_SUCCESS;
	}
	else {
		fprintf(stderr, "Error:Testing Task2 has failed.\n");
		/**Process returns and terminates with error*/
		return EXIT_FAILURE;
	}
}
