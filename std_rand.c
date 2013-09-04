// cc -o std_rand std_rand.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {

	double rn;

	srand(time(NULL));

	rn = rand()/(double)RAND_MAX;
	printf("%lf\n",rn);

}