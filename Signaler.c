
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <gsl/gsl_rng.h>
#include "commonFunc.c"

int main(int argc, char * const argv[]) {

	//declare variables, initialize

	int opt, signalNum;
	size_t percentage = -1;


	// generate random signal between 1-31 inclusive

	gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);	
	struct timespec tp;
	if (clock_gettime(CLOCK_REALTIME, &tp) == -1)		// get clock time; used as seed for random number generator; -1 returned if failure
		{
		printError("Failed to retrieve seed for GSL random number generator! Aborting.");
		exit(1);
		}
	gsl_rng_set(rng, tp.tv_nsec);		// seed with time in nanoseconds 
	if (rng == NULL)
		{
		printError("Failed to initialize GSL random number generator! Aborting.");
		exit(1);
		}

	double randVal = gsl_rng_uniform (rng) * 100;	// generate random number and convert to percentage
	gsl_rng_free (rng);		// free memory resources associated with the random number generator
	
	// convert the random numbber to be in range 1-31
	
	while (signalNum == 0) 
		signalNum = (int) (randVal % 32);		
	
	//spawn child (hand) processes
	
	pid_t child_pid;
	int child_status;
	for (size_t i = 0; i < num_trials; i++) 
		{	
		if ((child_pid = fork()) < 0)		// child spawn was unsuccessful
			fprintf(stderr, "Child process failed to execute.");
			
		if (child_pid == 0) // in child
			{
			// redirect stdout to /dev/null to suppress child's output
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
}
