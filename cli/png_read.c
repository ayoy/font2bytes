#include "png_read.h"
#include <stdlib.h>
#include <stdio.h>


png_data * png_data_create(const char *filename) {
    FILE *fp = fopen(filename, "rb");

    if (!fp) {
        return NULL;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    png_data *data = (png_data *)(malloc(sizeof(png_data)));

    data->width      = png_get_image_width(png, info);
    data->height     = png_get_image_height(png, info);
    data->color_type = png_get_color_type(png, info);
    data->bit_depth  = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if (data->bit_depth == 16) {
        png_set_strip_16(png);
    }

    if (data->color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
    }

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (data->color_type == PNG_COLOR_TYPE_GRAY && data->bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(png);
    }

    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }

    // These color_type don't have an alpha channel then fill it with 0xff.
    if (data->color_type == PNG_COLOR_TYPE_RGB ||
            data->color_type == PNG_COLOR_TYPE_GRAY ||
            data->color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    }

    if (data->color_type == PNG_COLOR_TYPE_GRAY ||
            data->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(png);
    }

    png_read_update_info(png, info);

    data->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * data->height);
    for (u_int32_t y = 0; y < data->height; y++) {
        data->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    png_read_image(png, data->row_pointers);

    fclose(fp);

    return data;
}

//void png_data_inspect(const png_data *data) {
//    for (int y = 0; y < data->height; y++) {
//        png_bytep row = data->row_pointers[y];
//        for (int x = 0; x < data->width; x++) {
//            png_bytep px = &(row[x * 4]);
//            // Do something awesome for each pixel here...
//            printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
//        }
//    }
//}

void png_data_destroy(png_data *data) {
    free(data->row_pointers);
    free(data);
}

