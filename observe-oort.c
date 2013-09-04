/*
compile with
// cc -o observe-oort observe-oort.c ran2.c kepcart.c machine-epsilon.c -lm
cc -o observe-oort observe-oort.c ran2.c kepcart.c

example:

observe-oort 100 10 100 -1 -1

*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "observe.h"

#define G 39.476926421373015  /* units are AU, year, and solar masses */
#define Msun 1.00000597682    /* mass of sun, augmented by inner planets */

State p;

int main(int argc, char **argv)
{

  int i, j, n;
  double r, r2, v, v2;
  double gm, a, e, incl, longnode, argperi, meananom, cosi;
  double amin, amax;
  double lnamin, lnamax, lna, fa;
  double beta;
  double fe, sum;
  double ran2(), powlaw();
  long sd;

  if(argc != 6) {
    printf("args: n amin amax beta sd\n");
    exit(-1);
  }

  printf("# ");
  for(i=0; i<argc; i++){
    printf("%s ", argv[i]);
  }
  printf("\n");

  sscanf(argv[1], "%d", &n);
  sscanf(argv[2], "%lf", &amin);
  sscanf(argv[3], "%lf", &amax);
  sscanf(argv[4], "%lf", &beta);
  sscanf(argv[5], "%d", &sd);

  machine_epsilon = 1e-14;

  sd = -abs(sd); /* guarantee it is negative */

  gm = G*Msun;
  a = 1.0;
  incl = 0.0;
  longnode = 0.0;
  argperi = 0.0;

  sum = 0.0;
  
  j=0;
  while(j<n){

    fe = ran2(&sd);
    e = sqrt(1.0-fe);   //this comes from assumption that e dist is thermal
    // could just be e = sqrt(fe);
    
    a = powlaw(amin, amax, beta, &sd);

    longnode = 2.0*PI*ran2(&sd);
    argperi  = 2.0*PI*ran2(&sd);
    cosi = 2*ran2(&sd) - 1.0;
    incl = acos(cosi);
    meananom = 2.0*PI*ran2(&sd);

    cartesian(gm, a, e, incl, longnode, argperi, meananom, &p);

    r2 = p.x*p.x + p.y*p.y + p.z*p.z;
    r = sqrt(r2);

    v2 = p.xd*p.xd + p.yd*p.yd + p.zd*p.zd;
    v = sqrt(v2);

    printf("%lf\n", fe);
    // printf("%lf %lf %lf %lf %lf\n", r, v, a, e, a*(1. - e));  //q = a(1-e)
    j++;
  }
}


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
