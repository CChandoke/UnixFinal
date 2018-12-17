
#include <stdlib.h>
#include <stdio.h>		

	
int main()
	{
	int num;
	
	printf("\nPrinting ugly numbers below 10,000:\n\n");
	
	for (int i = 1; i < 10000; i++)
		{
		num = i;		// copy current value since we need to modify it but still use for loop count
		while (num%2 == 0) 
			num = num/2; 
		while (num%3 == 0) 
			num = num/3; 
		while (num%5 == 0) 
			num = num/5; 
		if (num == 1)	// i is an ugly number
			printf("%d\n", i);
		}
	}

	

	
	
	
