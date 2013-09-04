#include <string.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define TWOPI 6.283185307179586476925287
#define MAX(x,y) ((x) > (y)) ? (x) : (y)
#define MIN(x,y) ((x) < (y)) ? (x) : (y)
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define FAILURE -1
#define SUCCESS 0

typedef struct {
  double x, y, z, xd, yd, zd;
} State;

typedef struct {
  double x, y, z;
} Vector;

double principal_value_0(double theta);

double principal_value(double theta);

double machine_epsilon;




