// UnixFinal version

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

bool verbose, fileMode = false;		// option flags
double percentage = -1;		// default to invalid value
int opt, num_trials = -1;	// default to invalid value; getopt's -1 return value dictates that opt be an integer type
int devnull_fd, filename_fd = 0;			// file descriptors
vector<pair<pid_t, int>> results; //collects child process metadata
char * filename;



const char * const showStatus(int &s) 
	{
	switch (s) 
		{
		case 768: 		// success 
			return "success"; 
		case 1024: 		// failure
			return "failure";
		default:
			printf("err %d\n", s);	
			return "unexpected status code";
		}
	}
	
int main(int argc, char * const argv[]) {

	//read command line args
		while ((opt = getopt(argc, argv, "vp:o:")) != -1) 
		{
		switch (opt) 
			{
			case 'o':
				filename = optarg;		
				fileMode = true;
				break;
			case 'v':
				verbose = true;
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

	if (optind >= argc)		// number of trials has not been specified
		printError("You need to specify the number of trials to run!");

	if (percentage == -1)	// percentage not given
		printError("You need to specify a percentage!");

	num_trials = atoi(argv[optind]);	// convert numTrials to integer

	if (num_trials == -1)	// error
		printError("You need to specify a number of trials to run!");
		
		
	//spawn child (hand) processes
	
	pid_t child_pid;
	int child_status;
	for (size_t i = 0; i < num_trials; i++) 
		{	
		if ((child_pid = fork()) < 0)		// child spawn was unsuccessful
			fprintf(stderr, "Child process failed to execute.");
		if (child_pid == 0) 
			{
			// redirect stdout to /dev/null to suppress child's output
			devnull_fd = open("/dev/null", O_RDONLY);
			dup2(devnull_fd, 1);	
			close(1);	
			execv("./hand", argv);	// spawn child and pass args to it  
			// execl("./hand", "hand", argv[1], argv[2], (char*) NULL);	
			
			// statements below are reached only if execl() failed for some reason
			printf("execl() failure!\n\n");
			_exit(1);
			} 
		else 
			{	
			wait(&child_status);	// child's exit code replaces the value of child_status
			results.push_back(make_pair(child_pid, child_status));		// push <child pid, child status> pair to results vector
			}
		}

	//display results of each child process, for verbose mode
	if (verbose) 
		{
		for (pair<pid_t, int> p : results)
			printf("PID %d returned %s.\n", p.first, showStatus(p.second));
		printf("\n");
		}

	printf("Created %d processes.\n", num_trials);		

	//tally the successes and failures
	double successes = 0, failures = 0;
	for (pair<pid_t, int> p : results) 
		{
		switch (p.second) 	// switch based on the child's exit code (i.e., its status)
			{
			case 768:  	// success exit code returned by child -- increment success count
				successes++;
				break;
			case 1024:	// failure exit code returned by child -- increment failure count
				failures++;
				break;
			}
		}
 
	// output results to records file if fileMode flag is set
	if (fileMode)																			
		{
		if (strcmp((const char *) filename, "") == 0)
			printError("You need to specify a file name when using the -o option!");
		else 
			{
			filename_fd = open(filename, O_CREAT | O_WRONLY | O_RDONLY | O_APPEND, 0644 );	// last arg is the permission mode
			if (filename_fd == -1)		// failed to open or create file
				printf("File failed to open!  Error number %d" , errno);	
			else 	// successfully opened or created file
				{	// write results to file
				printf("Successfully opened or created file!\n");		// ***testing***
				dprintf(filename_fd, "%.2f %.2f\n", successes / num_trials * 100, failures / num_trials * 100);
				}
			}  
		}
	
	// display results
	printf("Success - %.2f%%\nFailure - %.2f%%\n", successes / num_trials * 100, failures / num_trials * 100);

	return EXIT_SUCCESS;
}
