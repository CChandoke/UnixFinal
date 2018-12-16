
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
int offset = 0;		// byte offset for lseek()
char * filename;
double buffer [2]; // read in from records file
	
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
			if (filename_fd == -1)		// failed to open file
				{
				fprintf(stderr, "File failed to open for reading!  Error number %d \n", errno);
				exit(1);
				}	
			else 	// read from file
				{	
				printf("Successfully opened file for reading!\n");		// ***testing***
				offset = sizeof(buffer) * ((percentage / 10) -1) ;
				lseek(filename_fd, offset, SEEK_SET);		// set position to read from file
				numBytesRead = read(filename_fd, buffer, sizeof(buffer)); 	// read from file and check for read error (-1)
				if (numBytesRead == -1)
					fprintf(stderr, "read() failure!  Error number %d \n", errno);
				printf("Read %d bytes.\n", sizeof(buffer));
				}
			close(filename_fd);
			}  
	
	// display results
	printf("Success - %.2f%%\nFailure - %.2f%%\n", buffer[0], buffer[1]);

	return EXIT_SUCCESS;
}
