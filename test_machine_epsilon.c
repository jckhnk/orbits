// cc -o test_machine_epsilon test_machine_epsilon.c machine-epsilon.c -lm

#include <stdio.h>
#include <stdlib.h>

int main () {

	double e;
	double determine_machine_epsilon();

	e = determine_machine_epsilon();

	printf("%le\n",e);

}
