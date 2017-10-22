#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "xyz.h"
#include "util.h"
#include "geometry.h"


typedef struct {
 xyz position;
 xyz color;
 float power;
 xyz koef;
} Light;
typedef struct {
 xyz color;
 float reflectionFactor;
} Material;


void video_init();
xyz video(int,int,float);


