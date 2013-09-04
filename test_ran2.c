/*
compile with
cc -o test_ran2 test_ran2.c ran2.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{

  int i, n;
  long sd;
  double rn;
  double ran();

  if(argc != 3) {
    printf("args: seed n\n");
    exit(-1);
  }

  printf("# ");
  for(i=0; i<argc; i++){
    printf("%s ", argv[i]);
  }
  printf("\n");

  sscanf(argv[1], "%d", &sd);
  sscanf(argv[2], "%d", &n);

  // machine_epsilon = 1e-14;

  sd = -abs(sd); /* guarantee it is negative */

  for(i=0; i<n; i++) {
    rn = ran2(&sd);
    printf("%lf\n", rn);
  }

}
