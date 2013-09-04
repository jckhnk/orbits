#include <stdio.h>

int main () {

	double a, b, c;
	a = 1.;
	b = 2.;
	c = 3.;

	double x[3] = {a, b, c};

	for(int i=0; i<3; i++) {
		printf("%lf\n",x[i]);
	}
}
