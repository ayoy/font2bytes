#ifndef PNG_READ_H
#define PNG_READ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <png.h>

typedef struct png_data {
    int width;
    int height;
    png_byte color_type;
    png_byte bit_depth;
    png_bytep *row_pointers;
} png_data;

png_data * png_data_create(const char *filename);
void png_data_inspect(const png_data *data);
void png_data_destroy(png_data *data);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // PNG_READ_H
