#Compile all the tasks.
all: 
	cd task1; make
	cd task2; make
	cd task3; make
	cd task3_alt; make
#Cleanup all the tasks
clean:
	cd task1; make clean
	cd task2; make clean
	cd task3; make clean
	cd task3_alt; make clean
#Cleanup all the tasks including log files.
cleanall:
	cd task1; make cleanall
	cd task2; make cleanall; rm -r -f requests
	cd task3; make cleanall; rm -r -f requests
	cd task3_alt; make cleanall; rm -r -f requests
.PHONY: all clean cleanall