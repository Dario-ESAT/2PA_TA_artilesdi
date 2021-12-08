
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>

#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>

#include "bmp.h"

void InvertImageWorker(byte* pixels, unsigned int head ,unsigned int num_bytes){
  for (int i = 0; i < num_bytes; ++i) {
    pixels[i] = 0xFF - pixels[i];
  }
}

void InvertImage(byte* pixels, int width, int height, int bytespp, int num_cores) {
  unsigned int total_bytes = width*height*bytespp;

  unsigned int bytes_per_core = total_bytes /num_cores;
  unsigned int head = 0;
  std::vector<std::thread*> threds;

  for (int i = 0; i < num_cores - 1; ++i) {
    std::thread* t = new std::thread(InvertImageWorker,pixels,head,bytes_per_core);
    threds.push_back(t); 
    head += bytes_per_core;
  }
  std::thread* t = new std::thread(InvertImageWorker,pixels,head,head - bytes_per_core);
  threds.push_back(t);

  for (int i = 0; i < num_cores; i++) {
    threds[i]->join();
  }

  
}

int esat::main(int argc, char** argv) {
  byte *pixels;
  int32 width;
  int32 height;
  int32 bytes_per_pixel;

  esat::WindowInit(1,1);

  int num_cores = std::thread::hardware_concurrency();
  for (int i = 1; i < 6; ++i) {
    char tmp[16] = {0};
    sprintf(tmp, "../data/%d.bmp\0", i);
    printf("Opening %s...\n", tmp);
    double time_stamp = esat::Time();
    ReadImage(tmp, &pixels, &width, &height,&bytes_per_pixel);
    InvertImage(pixels, width, height, bytes_per_pixel,num_cores);
    sprintf(tmp, "../data/%db.bmp\0", i);
    printf("Writing %s...\n", tmp);
    WriteImage(tmp, pixels, width, height, bytes_per_pixel);
    free(pixels);
    time_stamp = esat::Time() - time_stamp;
    printf("Time: %fs\n", time_stamp * 0.001);
  }

  esat::WindowDestroy();

  return 0;
}

