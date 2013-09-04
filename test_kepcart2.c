/* 
compile:
	cc -o test_kepcart2 test_kepcart2.c kepcart2.
run:
	./test_kepcart2 1. 1. 1. 1. 1. 1. 1.
*/


#include <stdio.h>

int main(int argc, char **argv) {

	double gm, a, e, incl, longnode, argperi, meananom;
	double x, y, z, xd, yd, zd;

	sscanf(argv[1], "%lf", &gm);
	sscanf(argv[2], "%lf", &a);
	sscanf(argv[3], "%lf", &e);
	sscanf(argv[4], "%lf", &incl);
	sscanf(argv[5], "%lf", &longnode);
	sscanf(argv[6], "%lf", &argperi);
	sscanf(argv[7], "%lf", &meananom);

	// gm = 1.;
	// a = 1.;
	// e = 1.;
	// incl = 1.;
	// longnode = 1.;
	// argperi = 1.;
	// meananom = 1.;

	cartesian(gm, a, e, incl, longnode, argperi, meananom, &x, &y, &z, &xd, &yd, &zd);

	double arr[6] = {x, y, z, xd, yd, zd};

	for(int i=0; i<6; i++) {
		printf("%lf\n",arr[i]);
	}
}