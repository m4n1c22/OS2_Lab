#MakeFile for the OS2 Lab-1
CC=gcc
CFLAGS=--std=c99 -Wall -Werror -O1
OBJFLAG=-c
OUTPUT_FLAG=-o
SOURCES = task3.c
OUT_FILE=prog

#Default target which is executed
all: exec

#Target to execute the task3
exec: prog	
	./$(OUT_FILE)

#Target for internal dependency
prog: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(OUTPUT_FLAG) $(OUT_FILE)

#Clean up the code.
clean:
	rm -f $(OUT_FILE)
