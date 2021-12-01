#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

const int kDataOffsetOffset = 0x000A;
const int kWidthOffset = 0x0012;
const int kHeightOffset = 0x0016;
const int kBitsPerPixelOffset = 0x001C;
const int kHeaderSize = 14;
const int kInfoHeaderSize = 40;
const int kNoCompresion = 0;
const int kMaxNumberOfColors = 0;
const int kAllColorsRequired = 0;
 
 
void ReadImage(const char *fileName,byte **pixels, int32 *width, int32 *height, int32 *bytes_per_pixel) {
        FILE *image_file = fopen(fileName, "rb");
        int32 data_offset;
        fseek(image_file, kDataOffsetOffset, SEEK_SET);
        fread(&data_offset, 4, 1, image_file);
        fseek(image_file, kWidthOffset, SEEK_SET);
        fread(width, 4, 1, image_file);
        fseek(image_file, kHeightOffset, SEEK_SET);
        fread(height, 4, 1, image_file);
        int16 bits_per_pixel;
        fseek(image_file, kBitsPerPixelOffset, SEEK_SET);
        fread(&bits_per_pixel, 2, 1, image_file);
        *bytes_per_pixel = ((int32)bits_per_pixel) / 8;
 
        int padded_row_size = (int)(4 * ceil((float)(*width) / 4.0f))*(*bytes_per_pixel);
        int unpadded_row_size = (*width)*(*bytes_per_pixel);
        int totalSize = unpadded_row_size*(*height);
        *pixels = (byte*)malloc(totalSize);
        int i = 0;
        byte *currentRowPointer = *pixels+((*height-1)*unpadded_row_size);
        for (i = 0; i < *height; i++)
        {
            fseek(image_file, data_offset+(i*padded_row_size), SEEK_SET);
            fread(currentRowPointer, 1, unpadded_row_size, image_file);
            currentRowPointer -= unpadded_row_size;
        }
 
        fclose(image_file);
}
 
void WriteImage(const char *fileName, byte *pixels, int32 width, int32 height,int32 bytes_per_pixel){
        FILE *output_file = fopen(fileName, "wb");
        //*****HEADER************/
        const char *BM = "BM";
        fwrite(&BM[0], 1, 1, output_file);
        fwrite(&BM[1], 1, 1, output_file);
        int padded_row_size = (int)(4 * ceil((float)width/4.0f))*bytes_per_pixel;
        int32 file_size = padded_row_size*height + kHeaderSize + kInfoHeaderSize;
        fwrite(&file_size, 4, 1, output_file);
        int32 reserved = 0x0000;
        fwrite(&reserved, 4, 1, output_file);
        int32 data_offset = kHeaderSize+kInfoHeaderSize;
        fwrite(&data_offset, 4, 1, output_file);
 
        //*******INFO*HEADER******/
        int32 info_header_size = kInfoHeaderSize;
        fwrite(&info_header_size, 4, 1, output_file);
        fwrite(&width, 4, 1, output_file);
        fwrite(&height, 4, 1, output_file);
        int16 planes = 1; //always 1
        fwrite(&planes, 2, 1, output_file);
        int16 bits_per_pixel = bytes_per_pixel * 8;
        fwrite(&bits_per_pixel, 2, 1, output_file);
        //write compression
        int32 compression = kNoCompresion;
        fwrite(&compression, 4, 1, output_file);
        //write image size (in bytes)
        int32 image_size = width*height*bytes_per_pixel;
        fwrite(&image_size, 4, 1, output_file);
        int32 resolutionX = 11811; //300 dpi
        int32 resolutionY = 11811; //300 dpi
        fwrite(&resolutionX, 4, 1, output_file);
        fwrite(&resolutionY, 4, 1, output_file);
        int32 colors_used = kMaxNumberOfColors;
        fwrite(&colors_used, 4, 1, output_file);
        int32 important_colors = kAllColorsRequired;
        fwrite(&important_colors, 4, 1, output_file);
        int i = 0;
        int unpadded_row_size = width*bytes_per_pixel;
        for ( i = 0; i < height; i++)
        {
                int pixel_offset = ((height - i) - 1)*unpadded_row_size;
                fwrite(&pixels[pixel_offset], 1, padded_row_size, output_file); 
        }
        fclose(output_file);
}

