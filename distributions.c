/* This routine supplies numbers from N distributions: exponential,
   uniform, and gaussian.  It makes sure that the numbers are within a 
   given range and follow a standard deviations or other appropriate 
   parameter.

   cc -o distributions distributions.c ran2.c sgas.c gasdev.c powlaw.c  -lm   

   distributions 6 1.0 10.0 0.3 100 -1

   */

#define PI 3.14159265358979323846

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main(argc, argv)
     int argc;
     char **argv;
{
  int i, n, dist_type;
  double tau, stand, mean, r, t, r0, r1, f, b;
  double xmin, xmax;
  double ran2(), gasdev(), sgas(), powlaw(), two_comp();
  double sg1, sg2, a;
  long sd;

  if(argc < 2) {
    printf("args: dist_type...\n");
    exit(-1);
  }

  sscanf(argv[1], "%d", &dist_type);

  switch(dist_type){
  case 1:
    /* exponential */
    if(argc != 7) {
      printf("args: dist_type tau xmin xmax n sd\n");
      exit(-1);
    }

    sscanf(argv[2], "%lf", &tau);
    sscanf(argv[3], "%lf", &xmin);
    sscanf(argv[4], "%lf", &xmax);
    sscanf(argv[5], "%d", &n);
    sscanf(argv[6], "%d", &sd);

    sd = -abs(sd); /* guarantee it is negative */
    
    i=0;
    do{
      r = ran2(&sd);
      t = -tau*log(r);
      if(t>=xmin && t<xmax){
	printf("%lf\n", t);
	i++;
      }
    }while(i<n);
    break;
  case 2:
    /* uniform */

    if(argc != 6) {
      printf("args: dist_type xmin xmax n sd\n");
      exit(-1);
    }

    sscanf(argv[2], "%lf", &xmin);
    sscanf(argv[3], "%lf", &xmax);
    sscanf(argv[4], "%d", &n);
    sscanf(argv[5], "%d", &sd);

    sd = -abs(sd); /* guarantee it is negative */
  
    for(i=0; i<n; i++){
      r = ran2(&sd);
      t = xmin + (xmax-xmin)*r;
      printf("%lf\n", t);
    }	
    break;
  case 3:
    /* Gaussian */

    if(argc != 8) {
      printf("args: dist_type mean stand xmin xmax n sd\n");
      exit(-1);
    }

    sscanf(argv[2], "%lf", &mean);
    sscanf(argv[3], "%lf", &stand);
    sscanf(argv[4], "%lf", &xmin);
    sscanf(argv[5], "%lf", &xmax);
    sscanf(argv[6], "%d", &n);
    sscanf(argv[7], "%d", &sd);

    sd = -abs(sd); /* guarantee it is negative */
  
    i=0;
    do{
      r = gasdev(&sd);
      t = stand*r + mean;
      if(t>=xmin && t<xmax){
	printf("%lf\n", t);
	i++;
      }
    }while(i<n);
    break;
  case 4:
    /* Sine x Gaussian */

    if(argc != 7) {
      printf("args: dist_type stand xmin xmax n sd\n");
      exit(-1);
    }

    sscanf(argv[2], "%lf", &stand);
    sscanf(argv[3], "%lf", &xmin);
    sscanf(argv[4], "%lf", &xmax);
    sscanf(argv[5], "%d", &n);
    sscanf(argv[6], "%d", &sd);

    sd = -abs(sd); /* guarantee it is negative */
  
    i=0;
    do{
      r0 = sgas(stand, &sd);
      printf("%lf\n", r0);
      i++;
    }while(i<n);
    break;
  case 5:
    /* power law */

    if(argc != 7) {
      printf("args: dist_type xmin xmax b n sd\n");
      exit(-1);
    }

    sscanf(argv[2], "%lf", &xmin);
    sscanf(argv[3], "%lf", &xmax);
    sscanf(argv[4], "%lf", &b);
    sscanf(argv[5], "%d", &n);
    sscanf(argv[6], "%d", &sd);

    sd = -abs(sd); /* guarantee it is negative */
  
    i=0;
    do{
      r0 = powlaw(xmin, xmax, b, &sd);
      printf("%lf\n", r0);
      i++;
    }while(i<n);
    break;
  case 6:
    /* two component */

    if(argc != 7) {
      printf("args: dist_type sg1 sg2 a n sd\n");
      exit(-1);
    }

    sscanf(argv[2], "%lf", &sg1);
    sscanf(argv[3], "%lf", &sg2);
    sscanf(argv[4], "%lf", &a);
    sscanf(argv[5], "%d", &n);
    sscanf(argv[6], "%d", &sd);

    sd = -abs(sd); /* guarantee it is negative */

    sg1 *= PI/180.0;
    sg2 *= PI/180.0;

    i=0;
    do{
      r0 = two_comp(sg1, sg2, a, &sd);
      printf("%lf\n", r0);
      i++;
    }while(i<n);
    break;
  case 7:
    {
      double alpha, x0, xmin, xmax, ymin, ymax;
      double dy, x, y;

      /* cumulative base-10 exponential */
      if(argc != 8) {
	printf("args: dist_type alpha x0 xmin xmax n sd\n");
	exit(-1);
      }

      sscanf(argv[2], "%lf", &alpha);
      sscanf(argv[3], "%lf", &x0);
      sscanf(argv[4], "%lf", &xmin);
      sscanf(argv[5], "%lf", &xmax);
      sscanf(argv[6], "%d", &n);
      sscanf(argv[7], "%d", &sd);

      sd = -abs(sd); /* guarantee it is negative */

      ymin = pow(10.0, alpha*(xmin-x0));
      ymax = pow(10.0, alpha*(xmax-x0));
    
      i=0;
      do{
	r = ran2(&sd);
	dy = ymax-ymin;
	y = dy*r + ymin;
	x = 1.0/alpha*log10(y) + x0;
	if(x>=xmin && x<xmax){
	  printf("%lf\n", x);
	  i++;
	}
      }while(i<n);
    }
    break;
  default:
    printf("no such type: %d\n", dist_type);
    printf("1: exponential, 2: uniform, 3: gaussian\n");
    exit(-1);
  }
}

double two_comp(double sg1, double sg2, double a, long *idum)
{
  double ran2();
  double r0, r1, f;

  do{
    r0 = PI*0.5*ran2(idum);
    r1 = 0.03*ran2(idum);
    f = sin(r0)*(a*exp(-r0*r0/(2.0*sg1*sg1)) + (1.0-a)*exp(-r0*r0/(2.0*sg2*sg2)));
  }while(r1>f);
  return(r0);
}



