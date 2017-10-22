#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "xyz.h"
#include "video.h"
#include "util.h"



uint32_t frame[FRAME_WIDTH*FRAME_HEIGHT];

uint32_t toPixel(xyz color){
 uint32_t r = (uint32_t)(255 * clamp(0,1,color.x));
 uint32_t g = (uint32_t)(255 * clamp(0,1,color.y));
 uint32_t b = (uint32_t)(255 * clamp(0,1,color.z));
 return 0xFF000000 | (b << 16) | (g << 8) | r;
}

void randerFrame(float time){
 for(int y = 0;y < FRAME_HEIGHT;y++)
  for(int x = 0;x < FRAME_WIDTH;x++){ 
   xyz color = video(x,y,time);
   uint32_t pixel = toPixel(color);
   frame[y*FRAME_WIDTH+x] = pixel;
  }
}






int main(){
 
 video_init();
 int64_t nFrames = (uint64_t)(FRAME_RATE * TIME);
 
 for(uint64_t f = 0;f < nFrames;f++){
  float time = ((float)f) / FRAME_RATE;
  randerFrame(time);
  write(1, &frame, sizeof(frame));  
   
 }
 return 0;
}
