
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
		{	// *** lnFact = gsl_sf_lnfact (i);   -- requires <gsl/gsl_sf.h>    -- then i should be declared as unsigned int 
		lnfact = gsl_sf_lngamma(i+1);  approx = i * log(i) - i;
		error = lnfact - approx;  errorRatio = error / lnfact * 100;
		printf("%d\t\t%.6e\t\t%.6e\t\t%.6e\t\t%.d\n", static_cast<int>(i), lnfact, approx, error, errorRatio);
		}
	}

	

	
	
	
