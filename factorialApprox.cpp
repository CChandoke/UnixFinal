
#include <gsl/gsl_sf_gamma.h>	// gsl_sf_lngamma()
#include <stdio.h>		
#include <math.h>				// log()
#include <queue>				// get first accurate estimate


	
	
int main()
	{
	int x = 100;
	std::queue<int> q;
	const double PI = 3.141592653589793;
	double lnfact, approx, error, errorRatio;
	
	printf("N\t\tln(Factorial)\t\tStirling's Formula\tError\t\t\tError Percent\n");
	
	for (double i = 1; i <= x; i++)
		{	
		lnfact = gsl_sf_lngamma(i+1);  				// calculate ln(N!)
		approx = i * log(i) - i;					// approximate ln(N!) using Stirling's formula
		error = fabs(approx - lnfact);  			// calculate approximation error 
		
		if ( (errorRatio = error / fabs(approx) * 100) < 1 )	// calculate percent approximation error
			q.push(i);
			
		printf("%d\t\t%.6e\t\t%.6e\t\t%.6e\t\t%.6e\n", static_cast<int>(i), lnfact, approx, error, errorRatio);
		}
		
	printf("\n\n The first Stirling value accurate to within 0.1%% is:\t%d\n\n", q.front());
	}

	

	
	
	
