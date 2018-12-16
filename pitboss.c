
#include <vector>
#include <utility>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "commonFunc.c"

using namespace std;

double percentage = -1;		// default to invalid value
int opt = -1;	// default to invalid value; getopt's -1 return value dictates that opt be an integer type
ssize_t numBytesRead = 0;
int filename_fd = 0;			// file descriptor 
char * filename;
char * buffer = (char *) malloc(30 * sizeof(char));		
double successRatio = 0, failureRatio = 0;		// read in from records file
const char * argString;
	
int main(int argc, char * const argv[]) {

	//read command line args
		while ((opt = getopt(argc, argv, "o:p:")) != -1) 
		{
		switch (opt) 
			{
			case 'o':
				filename = optarg;		
				break;
			case 'p':
				percentage = atoi(optarg);		//convert percentage arg to integer
				break;
			default:
				fprintf(stderr, "Unrecognized option %c\n", optarg);
				exit(EXIT_FAILURE);
			}
		}


	//validate that command line args are provided correctly by user

	if (optind >= argc + 1)		// number of trials has not been specified
		printError("Wrong number of arguments!");

	if (percentage == -1)	// percentage not given
		printError("You need to specify a percentage!");


 
	// main functionality -- read from records file 

		if (strcmp((const char *) filename, "") == 0 || strcmp((const char *) filename, "-p") == 0) 
			printError("You need to specify a file name when using the -o option!");
		else 
			{
			filename_fd = open(filename, O_RDONLY);		// open file for reading
			if (filename_fd == -1)		// failed to open or create file
				{
				fprintf(stderr, "File failed to open for reading!  Error number %d \n", errno);
				exit(1);
				}	
			else 	// read from file
				{	
				printf("Successfully opened file for reading!\n");		// ***testing***
				numBytesRead = read(filename_fd, buffer, 24);
				if (numBytesRead == -1)
					fprintf(stderr, "read() failure!  Error number %d \n", errno);	
				printf("Read %d bytes.\n", filename_fd, 24);
				printf("Those bytes are as follows: %s\n", buffer);
				}
			close(filename_fd);
			}  
	
	// display results
	printf("Success - %.2f%%\nFailure - %.2f%%\n", successRatio, failureRatio);

	return EXIT_SUCCESS;
}
