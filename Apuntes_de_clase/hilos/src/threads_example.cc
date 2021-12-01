
#include <stdio.h>
#include <stdlib.h>

#include <esat/window.h>
#include <esat/draw.h>
#include <esat/sprite.h>
#include <esat/input.h>
#include <esat/time.h>

#include "bmp.h"

void InvertImage(byte* pixels, int width, int height, int bytespp) {
  for (int i = 0; i < width*height*bytespp; ++i) {
    pixels[i] = 0xFF - pixels[i];
  }
}

int esat::main(int argc, char** argv) {
  byte *pixels;
  int32 width;
  int32 height;
  int32 bytes_per_pixel;

  esat::WindowInit(1,1);

  for (int i = 1; i < 6; ++i) {
    char tmp[16] = {0};
    sprintf(tmp, "../data/%d.bmp\0", i);
    printf("Opening %s...\n", tmp);
    double time_stamp = esat::Time();
    ReadImage(tmp, &pixels, &width, &height,&bytes_per_pixel);
    InvertImage(pixels, width, height, bytes_per_pixel);
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

