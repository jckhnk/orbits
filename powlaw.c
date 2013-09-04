/* cc -o power-law power-law.c ran2.c -lm */

/* This routines generates random numbers between r0 and r1
   according to a power law distribution, where the power law exponent 
   is b.

   n(x)dx = k * x^b dx, where k is a normalizing factor.

   This program is wrong for b=-1;

   Also, r1 needs to be bigger than r0, and both should be positive.
   No checks are made in the code.  Only you can prevent bugs!
   
   */

#include <stdio.h>
#include <math.h>

double powlaw(double r0, double r1, double b, long *idum)
{
  double r, k, x;
  double ran2();

  if(b != -1.0){

    if(b < -1.0 && (r0 == 0.0 || r1 == 0.0)){
      fprintf(stderr, "bad powlaw values %lf %lf %lf\n", r0, r1, b);
      exit(-1);
    }

    k = (b+1.0)/(pow(r1, b+1.0)-pow(r0, b+1.0));
    r = ran2(idum);
    x = pow((b+1.0)/k*r + pow(r0, b+1.0), 1.0/(b+1.0));

  }else{
    
    if(r0 <= 0.0 || r1 <= 0.0){
      fprintf(stderr, "bad powlaw values %lf %lf %lf\n", r0, r1, b);
      exit(-1);
    }
    
    k = 1.0/(log(r1) - log(r0));
    r = ran2(idum);
    x = exp(r/k);
    
  }
  return(x);
}

