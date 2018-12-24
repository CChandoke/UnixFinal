// invoked with "./perfectNums -n <integer>"

#include <stdlib.h>
#include <stdio.h>		
#include <getopt.h>
	
int main(int argc, char * const argv[])
	{
	int n, i, aliquotSum, opt;	
	bool isPerfect = false;
    aliquotSum = 1; 
	
	//read command line args
	while ((opt = getopt(argc, argv, "n:")) != -1) 
		{
		switch (opt) 
			{
			case 'n':
				n = atoi(optarg);	// convert number to from string to integer 
				if (n <= 1)	// error case
					{
					fprintf(stderr, "Error: Integer argument must be greater than 1!\n\n");
					return 1;
					}
				break;	
			}
		}

	for (i = optind; i < argc; i++)
		printf("Non-option argument %s\n\n", argv[i]);
		
    // Efficient way to calculate sum of proper divisors (aliquot sum) 
    for (int i = 2; i*i <= n; i++)
		{
		if ( (n % i) == 0 ) 	// n is divisible by i
            aliquotSum = aliquotSum + i + n/i; 		// then add both the factor i and its pairing factor to the sum
		}
	if (aliquotSum == n) 	// N is perfect if it equals its aliquot sum 
		printf("%d is a perfect number!\n\n", n); 
	else if (aliquotSum < n)		// deficient number
		printf("%d is a deficient number!  It's deficiency is %d\n\n", n, n - aliquotSum); 
	else 							// abundant number
		printf("%d is an abundant number!  It's abundance is %d\n\n", n, aliquotSum - n); 
	return 0;
	}

	
	

