#include "geometry.h"


float material;
float d;

void probe(float newD, float mat){
 if(newD < d){
  d = newD;
  material = mat;
 }
}

float sphere(xyz p, float r) {
    return length(p) - r;
}
float box(xyz p, xyz b){
  xyz d = sub(abs3(p),b);
  return MIN(MAX(d.x,MAX(d.y,d.z)),0.0) + length(max3v(d,0.0));
}

xyz repeat(xyz p, xyz d){
    return sub(mod(p,d), mulf(d, 0.5)); 
}

void room(xyz p , float t){
  
  
  float walls =
    MAX(
      -box(p,(xyz){40.0,7.,40.}),
       box(p,(xyz){45.0,10.,45.})
    );
  
  float colls = box(
      repeat(p, (xyz){13,13,13}),
      (xyz){0.8,10.,0.8}
  );
  float object = sphere(sub(p ,(xyz){0.,0.,5.0}),1.5 * (1.5 + sin(1.0+p.y + 2.0*t)/2.));
    
  probe(walls,1);
  probe(colls,2);
  probe(object,3);
  
}



xyz world(xyz p, float t){
 d = 1.0e10;
 material = 0;  
 room(p, t);
 return (xyz){d,material,0};
}

xyz normal(xyz p, float t){
 float d = world(p , t).x;
 float dx = world(add(p,(xyz){NORMAL_EPS,0,0}),t).x;
 float dy = world(add(p,(xyz){0,NORMAL_EPS,0}),t).x;
 float dz = world(add(p,(xyz){0,0,NORMAL_EPS}),t).x;
 
 return normalize((xyz){dx-d,dy-d,dz-d});
}
