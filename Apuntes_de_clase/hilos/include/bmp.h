
#ifndef __BMP_H__
#define __BMP_H__ 1

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;
 
void ReadImage(const char *fileName,byte **pixels, int32 *width, int32 *height, int32 *bytesperpixel);
void WriteImage(const char *fileName, byte *pixels, int32 width, int32 height, int32 bytesperpixel);

#endif

