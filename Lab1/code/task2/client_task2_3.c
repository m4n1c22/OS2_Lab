/** 
	\file		:	client_task2_3.c
	\author		:	Sreeram Sadasivam
	\brief		:	Task 2.3 for Operating Systems:Dependability & Trust Lab - 
					Design a client program to send client requests.
	\copyright	:	Copyrights reserved @2016
*/

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



int removeRequest(char *req_file_name) {
	
	if (unlink(req_file_name)!=0)
	{
		fprintf(stderr, "Error:Unlink failed.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int createRequest(char *req_file_name) {

	FILE *fp = fopen(req_file_name,"w");
	
	if(fp == NULL) {
		fprintf(stderr, "Error:File Open failed.");
		return EXIT_FAILURE;
	}

	printf("Client %d creating request %s\n", getpid(), req_file_name);

	fclose(fp);
	return EXIT_SUCCESS;
}

int client() {

	DIR *dirp;

	struct dirent *dp;

	printf("Client Process has begun sending the requests...\n");
	while(1) {
			
		char request_file_name[100],request_name[100];
		int isRequestIDSame = 0;
		int ret_val_usleep;
		/**Open the current directory.*/	
		dirp = opendir("./requests");
		
		if(sprintf(request_name,"req_%d",rand()%10000)<0) {
			fprintf(stderr, "Error:STDOUT failed.");
			return EXIT_FAILURE;			
		}

		while(dirp) {
			    
    		if ((dp = readdir(dirp)) != NULL) {
        		//printf("Directory Name: %s\n", dp->d_name);
        		if (strcmp(dp->d_name,request_name)==0)
        		{
        			isRequestIDSame = 1;
        		}
    		}
        	else {
        		break;
        	}
		}


		/**Close the requests directory.*/
		closedir(dirp);

		if(!isRequestIDSame) {
			if(sprintf(request_file_name,"./requests/%s",request_name)<0) {
				fprintf(stderr, "Error:STDOUT failed.");
				return EXIT_FAILURE;			
			}

	        if(createRequest(request_file_name)==EXIT_FAILURE) {
				fprintf(stderr, "Error:createRequest function failed.\n");
				return EXIT_FAILURE;
			}

			ret_val_usleep = usleep(500000);
			/**Failure in usleep call*/
			if(ret_val_usleep<0) {
				
				fprintf(stderr, "Error:Usleep function failed.\n");
				/**Process returns and terminates with error*/
				return EXIT_FAILURE;
			}
		}	
	}
	return EXIT_SUCCESS;
}

int main(int argc, char const *argv[])
{
	/**Invoking the request creation method.*/
	if(client()==EXIT_SUCCESS) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}
