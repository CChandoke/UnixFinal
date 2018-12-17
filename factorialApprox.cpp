
#include <gsl/gsl_sf_gamma.h>	// gsl_sf_lngamma()
#include <stdio.h>		
#include <math.h>		// log()

const double PI = 3.141592653589793;
double lnfact, approx, error, errorRatio;
	
	
int main()
	{
	int x = 100;
	
	printf("N\t\tln(Factorial)\t\tStirling's Formula\tError\t\t\tError Percent\n");
	for (double i = 1; i <= x; i++)
		{	
		lnfact = gsl_sf_lngamma(i+1);  		// calculate ln(N!)
		approx = i * log(i) - i;			// approximate ln(N!) using Stirling's formula
		error = lnfact - approx;  			// calculate approximation error 
		errorRatio = error / lnfact * 100;	// calculate percent approximation error
		printf("%d\t\t%.6e\t\t%.6e\t\t%.6e\t\t%.d\n", static_cast<int>(i), lnfact, approx, error, errorRatio);
		}
	}

	

	
	
	
