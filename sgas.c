#include <math.h>

double sgas(double stand, long *idum)
{
  double ran2(), gasdev();
  double r0, r1, f;

  do{
    r0 = fabs(stand*gasdev(idum)); /* for comparison function */
    r1 = ran2(idum)*exp(-r0*r0/(2.0*stand*stand));
    f = sin(r0)*exp(-r0*r0/(2.0*stand*stand));
  }while(r1>f);
  return(r0);
}
