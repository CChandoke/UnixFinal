#include <getopt.h>
#include <stdbool.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <gsl/gsl_rng.h>

bool within100 = false;
time_t start;
int opt;
size_t numTrials = -1;

// increment counter if random trial point falls within the unit circle in Quadrant I
void incIn(gsl_rng *rng, size_t *in) 
	{
	if (cabs(gsl_rng_uniform (rng) + gsl_rng_uniform (rng) * I) <= 1)
		(*in)++;
	}

int main(int argc, char * const argv[]) {
	if (argv[1] == NULL) 
		{
		printf("SYNOPSIS: %s: <-c count | -1>\n\tRun count trials, or run as many trials as we can in 100 seconds. If both options are specified, the 100 seconds option takes precedence.\n", argv[0]);
		return 0;
		}
	

	
	//read cmdline args
	opterr = 0;
	while ((opt = getopt(argc, argv, "c:1")) != -1) 
		{
		switch (opt) 
			{
			case 'c':
				numTrials = atoi(optarg);	// convert numTrials from string to integer
				break;
			case '1':
				within100 = true;
				break;
			}
		}

	if (numTrials == -1 && !within100)
		{ 
		perror("You must specify a number of trials. Aborting.");
		exit(EXIT_FAILURE); 
		}

	// seed random generator
	gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	start = tp.tv_sec; //used for "max number of approximations in 100 sec" task
	gsl_rng_set(rng, tp.tv_nsec);
	if (rng == NULL)
		{ 
		perror("Failed to initialize GSL random number generator! Aborting.");
		exit(EXIT_FAILURE); 
		}

	size_t in = 0, trialsRun = 0;
	if (within100) 
		{
		time_t now;
		while (now - start <= 100) 
			{
			clock_gettime(CLOCK_REALTIME, &tp); // we reuse tp because we can; it's not used anywhere after here
			now = tp.tv_sec;
			incIn(rng, &in);
			trialsRun++;
			}
		} 
		else
			{
			for (size_t i = 0; i < numTrials; i++)
				incIn(rng, &in);
			}
			
	gsl_rng_free(rng);	// free resources associated with random number generator
	if (within100) 
		printf("Approximation of Archemedes' constant (%lu trials:) %f\n", trialsRun, 4 * ((double) in) / trialsRun);
	else 
		printf("Approximation of Archemedes' constant: %f\n", 4 * ((double) in) / numTrials);
}

