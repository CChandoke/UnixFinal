
#include <stdlib.h>
#include <stdio.h>		
#include <getopt.h>
	
int main(int argc, char * const argv[])
	{
	int n, aliquotSum, opt;	
	bool isPerfect = false;
    aliquotSum = 1; 
	
	//read command line args

	opterr = 0;		// tell getopt to ignore nonsense options 
					// rather than output error messages by default
	
	while ((opt = getopt(argc, argv, "n:")) != -1) 
		{
		switch (opt) 
			{
			case 'n':
				n = atoi(optarg);	// convert number to from string to integer 
				break;
			}
		}

	if (n -1)	// error case
		fprintf(stderr, "Wrong number of arguments!\n\n");	
		
    // Efficient way to calculate sum of proper divisors (aliquot sum) 
    for (int i = 2; i*i <= n; i++)
		{
		if ( (n % i) == 0 ) 	// n is divisible by i
            aliquotSum = aliquotSum + i + n/i; 		// then add both the factor i and its pairing factor to the sum
		}
	if ( (aliquotSum == n) && (n <= 1) ) 	// N is perfect if it equals its aliquot sum 
		printf("%d is a perfect number!\n\n", n); 
	else if (aliquotSum < n)		// deficient number
		printf("%d is a deficient number!  It's deficiency is %d\n\n", n, n - aliquotSum); 
	else 							// abundant number
		printf("%d is an abundant number!  It's abundance is %d\n\n", n, aliquotSum - n); 
	}

	
	

