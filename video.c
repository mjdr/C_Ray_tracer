#include "video.h"

#define PI 3.141592


float oldT = -1;
Light lights[2];
Material materials[4];

void video_init(){
 lights[0] = (Light) {
  (xyz){1,5,-5},
  (xyz){1.0f,1.0,1.0f},
  10.0,
  (xyz){.5f,1,1}
 };
 lights[1] = (Light) {
  (xyz){1,5,-5},
  (xyz){1.0f,1.0,1.0f},
  10.0,
  (xyz){.5f,1,1}
 };

 materials[0] = (Material){(xyz){0,0,0},0};
 materials[1] = (Material){(xyz){0.5,0.5,0.9},0};
 materials[2] = (Material){(xyz){0.,1.,0.},0};
 materials[3] = (Material){(xyz){1.,0.,0.},0};
 
}

void update(float t){
 if(oldT == t) return;
 oldT = t;
 
 
 float a = t;
 float r = 5;
 lights[0].position = (xyz){r * sin(a), 5 , r * cos(a)};
 lights[1].position = (xyz){r * sin(a+PI), 5 , r * cos(a+PI)};
}


xyz tracer(xyz p, xyz n, float t, float maxDistance) {
 float d = 0;
 for(int i = 0;i < 512;i++){
  xyz w = world(add(p,mulf(n,d)), t);
  if(w.x < TRACE_EPS)
   return (xyz){d,w.y,0};
  d += w.x * 0.5; 
  if(d > maxDistance)
   return (xyz){-1.,0,0};
 }
 return (xyz){-1.,0,0};
 
}


xyz calculateLight(xyz P, xyz N,Material M, Light L, float t){
 xyz LVec = sub(L.position,P);
 xyz LDir = normalize(LVec);
 float LDist = length(LVec);
 
 float LRayDist = tracer(add(P,mulf(N,0.1)), LDir,t, LDist).x;
 
 float ShadowK = 1;
 if(LRayDist != -1 && LRayDist < LDist)
  ShadowK = smoothstep(0, LDist,LRayDist);


 float LPower = L.power / polinom(L.koef, LDist); 
 float k = clamp(0,1,dot(N,LDir));
 float LInt = k * LPower;
 
 
 return mulf(mulv(M.color,mulf(L.color,LInt)), ShadowK);
 
}


xyz camera360(xyz pos){
 pos.y = FRAME_HEIGHT - pos.y;  
 xyz tmp0 = div3(pos,(xyz){FRAME_WIDTH,FRAME_HEIGHT,0});
 tmp0 = mulf(tmp0,2);
 xyz uv = sub(tmp0,(xyz){1,1,1});
 xyz a = (xyz){uv.x * PI,uv.y * PI/2.,0};
 xyz vec = (xyz){sinf(a.x) * cosf(a.y),sinf(a.y),cosf(a.y)*cosf(a.x)};
 return vec;
}



xyz camera(xyz pos){
 xyz posN = getPosition(pos.x,pos.y);
 return normalize((xyz){posN.x,posN.y,1});
}


xyz video(int x, int y, float t){
 update(t);
 xyz color = (xyz){0.f,0.f,0.f};
 
 
 xyz O = (xyz){0.,1.,-3};
 xyz DIR = camera360((xyz){x,y,0});
 xyz D = tracer(O,DIR,t, 100);
 Material M = materials[(int)D.y];
 
 if(D.x == -1)
  return color;
 
 xyz P = add(O,mulf(DIR,D.x));
 xyz N = normal(P,t);

 //ambiend
 color = add(color, mulf(M.color,0.04f)); 

 for(int i = 0;i < sizeof(lights)/sizeof(Light);i++)
  color = add(color, calculateLight(P,N,M,lights[i],t));
 
 color = sqrt3(color);
 //color.x = color.y = color.z =exp(-D.x * 0.05);
 return color;
}
