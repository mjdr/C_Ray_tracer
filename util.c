#include "util.h"


xyz getPosition(int x, int y){
 y = FRAME_HEIGHT - y;
 
 int min_d = MIN(FRAME_WIDTH,FRAME_HEIGHT);
 float u = ((float)x)/min_d;
 float v = ((float)y)/min_d;
 
 return (xyz){2.0f*u - (((float)FRAME_WIDTH)/min_d),2.0f*v - (((float)FRAME_HEIGHT)/min_d), 0.f};
}


xyz vect(xyz a , float(func(float))){
 return (xyz){(*func)(a.x),(*func)(a.y),(*func)(a.z)};
}


float clamp(float min,float max,float x){
 if(x < min) return min;
 if(x > max) return max;
 return x;
}
float length(xyz p){
 return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}

xyz add(xyz a,xyz b){
 return (xyz){a.x + b.x, a.y + b.y, a.z + b.z};
}
xyz sub(xyz a,xyz b){
 return (xyz){a.x - b.x, a.y - b.y, a.z - b.z};
}
xyz mulf(xyz a,float k){
 return (xyz){a.x * k, a.y * k, a.z * k};
}
xyz mulv(xyz a,xyz b){
 return (xyz){a.x * b.x, a.y * b.y, a.z * b.z};
}

xyz normalize(xyz a){
 return mulf(a,1.f/length(a));
}

float dot(xyz a,xyz b){
 return a.x*b.x + a.y*b.y + a.z*b.z;
}
xyz sqrt3(xyz a){
 return vect(a, sqrtf);
}
float polinom(xyz k,float x){
 return k.x*x*x + k.y*x + k.z;
}

xyz mod(xyz a,xyz b){
 return sub(a,mulv(b,floor3(div3(a,b))));
}

float absf(float x){
 return x > 0 ? x : -x;
}
xyz abs3(xyz a){
 return vect(a, absf);
}

xyz max3v(xyz a,float b){
 return (xyz){MAX(a.x, b), MAX(a.y, b),MAX(a.z, b)};
}
xyz div3(xyz a,xyz b){
 return (xyz){a.x / b.x, a.y / b.y, a.z / b.z};
}

xyz floor3(xyz a){
 return vect(a,floorf);
}

float smoothstep(float min,float max ,float v){
 if(v < 0) return 0;
 if(v > max) return 1;
 return (v - min)/(max - min);
}


