
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <gsl/gsl_rng.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commonFunc.c"

pid_t child_pid;
int signalNum = 0;
int child_status = 0;


void child_sig_handler(int signalNum)     // child's signal handler
			{
			printf("Signal %d has been received by child\n", signalNum);
			if (signalNum > 31)
				signal(signalNum, SIG_DFL);		// if signal is greater than 31, then use default handler 
			}	
			
			
void parent_sig_handler(int signalNum)		// parent's signal handler
			{
			printf("Signal %.2d has been received by parent\n", signalNum);
			kill(child_pid, SIGKILL);		// send the randomly generated signal to child 
			wait(&child_status);    		// wait for child
			printf("Parent will exit now\n");
			exit(0);
			}
			

				
int main(int argc, char * const argv[]) {

        //declare variables, initialize

        int opt;
        size_t percentage = -1;
		double randVal;
			
        
		// initialize random number generator and retrieve seed
		
		gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
		struct timespec tp;
		
		if (clock_gettime(CLOCK_REALTIME, &tp) == -1)           // get clock time; used as seed for random number generator; -1 returned if failure
			{
			printError("Failed to retrieve seed for GSL random number generator! Aborting.");
			exit(1);
			}
			
		gsl_rng_set(rng, tp.tv_nsec);           // seed with time in nanoseconds
		if (rng == NULL)
			{
			printError("Failed to initialize GSL random number generator! Aborting.");
			exit(1);
			}
			
		// set timespect to half a second for use as arg to nanosleep()	
		tp.tv_sec = 0;			// set seconds to 0
		tp.tv_nsec = 5E8;		// set timespec nanosec value to half a second

		
		for(int i = 1; i <= 31; i++)	// specify that we will use child's handler for signals 1-31, so child will this behavior.  
										// parent also inherits this behavior, so this modification will be undone in parent process
			{
			signal(i, child_sig_handler);	// tell kernel to call user-defined handler when a signal is received
			}
			
		//spawn child process
		
		if ( (child_pid = fork()) < 0 )           // child spawn was unsuccessful
				fprintf(stderr, "Child process failed to execute.");
			
			
		// in child:
		if (child_pid == 0) 	
			{					
			// loop infinitely
			for(;;)
				{
				printf("Child waiting\n");
				nanosleep(&tp, NULL);	// sleep for half a second 
				}
			}
			
		// in parent:
		else		
			{
			// tell kernel to specifically use parent signal handler for signals 1-31
			for(int i = 1; i <= 31; i++)	
				{
				signal(i, parent_sig_handler);	
				}
							
			// loop infinitely
			for(;;)		
				{	
				// generate random signal between 1-31 inclusive
				do 
					{
					randVal = gsl_rng_uniform (rng) * 100;   // generate random number and convert to percentage
					signalNum = ( static_cast<int>(randVal) % 32 );		// convert the random number to be in range 1-31;  remainder will be less than 32
					}
				while (signalNum == 0);		// ensure the random number is not zero
				// random signal number has been generated 
				printf("Sending signal %d to child\n", signalNum);
				kill(child_pid, signalNum);		// send the randomly generated signal to child 
				nanosleep(&tp, NULL);	// sleep for half a second 
				}
			}
			
			
	
	
	
	gsl_rng_free (rng);             // free memory resources associated with the random number generator
			
			
}			
			
			
			
			
			
			
			
			
			
			
			
