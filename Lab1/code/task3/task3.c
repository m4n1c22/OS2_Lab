/**Define BSD SOURCE FOR <GLIBC 2.12. Since Compilation done with option std=c99. Used in regard with usleep().*/
#define _BSD_SOURCE
#include <sys/wait.h>
#include <sys/types.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int backup_terminated (int fork_ret_val, int fd[2]) {
	int ret_val_write,ret_val_usleep;
	char buffer;
	char poll_message[] = "Hallo I am child (server) process, this is a polling message\n";

	// child (server) process
	if (fork_ret_val == 0) {
	        do {
			// reduce the polling frequency
			ret_val_usleep = usleep(500000);
			// failure in usleep call
			if(ret_val_usleep<0) {
				fprintf(stderr, "Error: usleep function failed.\n");
				// process returns and terminates with error
				return EXIT_FAILURE;
			}
			ret_val_write = write(fd[1], poll_message, strlen(poll_message));
			// TODO Error creation for testing
			/* child gets error, this usually only works if the signal SIGPIPE is ignored, see man 2 signal */
			if (ret_val_write < 0) {
				fprintf(stderr, "Error: write function failed.\n");
				printf("Parent (backup) process failed\n");

				// TODO here change server process into backup process clear state
				/* Change the server process into a backup process. A simple and clean way to achieve this
				is to replace the current server process image by a fresh instance of your program. This has
				the same effects as if you kill and restart your whole program. See man 3 exec for details
				on how to achieve this. Note that the original command line options have to survive this
				process image replacement.*/

				// process returns and terminates with error
				return EXIT_FAILURE;
			}
	        } while (ret_val_write > 0);

	// parent (backup) process
	} else if ( fork_ret_val > 0) {
		while (read(fd[0], &buffer, 1) > 0) {
                    ret_val_write = write(STDOUT_FILENO, &buffer, 1);
		    if(ret_val_write < 0) {
			fprintf(stderr, "Error: write function failed.\n");
			// process returns and terminates with error
			return EXIT_FAILURE;
		    }
	        }

                ret_val_write = write(STDOUT_FILENO, "\n", 1);
	        if(ret_val_write < 0) {
	       		fprintf(stderr, "Error: write function failed.\n");
			// process returns and terminates with error
			return EXIT_FAILURE;
	 	}
	} else {
	        
        	fprintf(stderr, "Error: fork function failed.\n");
		// process returns and terminates with error
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int test_task3() {
	int pipefd[2], ret_val_pipe, ret_val_close;
        pid_t ret_val_fork;
        
        ret_val_pipe = pipe(pipefd);
	if (ret_val_pipe < 0) {
		fprintf(stderr, "Error: pipe function failed.\n");
		// process returns and terminates with error
		return EXIT_FAILURE;
        }

        ret_val_fork = fork();
        if (ret_val_fork < 0) {
        	fprintf(stderr, "Error: fork function failed.\n");
		// process returns and terminates with error
		return EXIT_FAILURE;
        }
	// child (server) writes to pipe
        else if (ret_val_fork == 0) {
		// close unused read end              
		ret_val_close = close(pipefd[0]);
		if(ret_val_close < 0) {
	       		fprintf(stderr, "Error: close function failed.\n");
			return EXIT_FAILURE;
	 	}
		printf("I am the child process. My PID is %d\n", getpid());
		// child (server) process will continuously poll the parent (backup) process
		backup_terminated (ret_val_fork, pipefd);
		// parent (backup) process will see EOF
                ret_val_close = close(pipefd[1]);
		if(ret_val_close < 0) {
	       		fprintf(stderr, "Error: close function failed.\n");
			return EXIT_FAILURE;
	 	}
                exit(EXIT_SUCCESS);
         } else {
		// close unused write end
                ret_val_close = close(pipefd[1]);
		if(ret_val_close < 0) {
	       		fprintf(stderr, "Error: close function failed.\n");
			return EXIT_FAILURE;
	 	}
	 	printf("I am the parent process. My PID is %d\n", getpid());
		printf("Creation of child successful. Child's PID is %d\n", ret_val_fork);
		// parent (backup) process will continuously receive poll message from child (server) process
		backup_terminated (ret_val_fork, pipefd);
                ret_val_close = close(pipefd[0]);
		if(ret_val_close < 0) {
	       		fprintf(stderr, "Error: close function failed.\n");
			return EXIT_FAILURE;
	 	}
		// wait for child (server) process             
		wait(NULL);
                exit(EXIT_SUCCESS);
        }
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	int ret_val_test_task3;
	ret_val_test_task3 = test_task3();
	if(ret_val_test_task3 != EXIT_SUCCESS) {
		fprintf(stderr, "Error:Testing Task3 Failed.\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
