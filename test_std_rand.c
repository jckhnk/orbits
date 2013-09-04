// cc -o test_std_rand test_std_rand.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char **argv) {

  int i, n;
  double rn;

  srand(time(NULL));

  if(argc != 2) {
    printf("args: n\n");
    exit(-1);
  }

  printf("# ");
  for(i=0; i<argc; i++){
    printf("%s ", argv[i]);
  }
  printf("\n");

  sscanf(argv[1], "%d", &n);

  for(i=0; i<n; i++) {
  	rn = rand()/(double)RAND_MAX;
    printf("%lf\n", rn);
  }
}

double r2()
{
    return (double)rand() / (double)RAND_MAX ;
}