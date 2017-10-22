#pragma once
#include "xyz.h"
#include <math.h>


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))



xyz getPosition(int, int);


float clamp(float,float,float);
float length(xyz);
xyz add(xyz,xyz);
xyz sub(xyz,xyz);
xyz mulf(xyz,float);
xyz mulv(xyz,xyz);
xyz mod(xyz,xyz);
xyz normalize(xyz);
float dot(xyz,xyz);
xyz sqrt3(xyz);
float polinom(xyz,float);
xyz abs3(xyz);
xyz max3v(xyz,float);
xyz div3(xyz,xyz);
xyz floor3(xyz);

float smoothstep(float,float,float);






