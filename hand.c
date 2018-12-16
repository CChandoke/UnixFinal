
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

	int opt;
	size_t percentage = -1;

	//read command line args

	opterr = 0;		// tell getopt to ignore nonsense options 
					// rather than output error messages by default
	
	while ((opt = getopt(argc, argv, "p:")) != -1) 
		{
		switch (opt) 
			{
			case 'p':
				percentage = atoi(optarg);		// convert percentage to integer so we can compare it
				break;
			}
		}

	if (percentage == -1)	// no percentage given
		printError("You need to specify a percentage!");

	//main functionality

	gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);	
	struct timespec tp;
	if (clock_gettime(CLOCK_REALTIME, &tp) == -1)		// get clock time; used as seed for random number generator; -1 returned if failure
		{
		printError("Failed to retrieve seed for GSL random number generator! Aborting.");
		exit(1);
		}
	gsl_rng_set(rng, tp.tv_nsec);		// seed with time in nanoseconds a
	if (rng == NULL)
		{
		printError("Failed to initialize GSL random number generator! Aborting.");
		exit(1);
		}

	double randVal = gsl_rng_uniform (rng) * 100;	// generate random number and convert to percentage
	gsl_rng_free (rng);		// free memory resources associated with the random number generator

	if (randVal <= percentage) 
		{		
		printf("success!\n"); 
		exit(TRIAL_SUCCESS);
		} 
	else 
		{
		printf("failure!\n");
		exit(TRIAL_FAILURE);		
		}
		
}
