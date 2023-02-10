#include "image.h"

int Image_New(image_t* memblk, guint height, guint width)
{
    pixel_t templatePixel;
    guint pixelSize;
    GArray* rowArray;
    GPtrArray* verticalArray;
    
    if (memblk == NULL) {
        return EINVAL;
    }

    templatePixel.alpha = 0;
    templatePixel.red   = 0;
    templatePixel.green = 0;
    templatePixel.blue  = 0;

    pixelSize = sizeof(pixel_t);

    verticalArray = g_ptr_array_sized_new(height);

    for (int i = 0; i < height; i++) {
        rowArray = g_array_sized_new(FALSE, FALSE, pixelSize, width);
        /** Create array for one row **/
        for (int j = 0; j < width; j++) {
            /** Insert pixels into Array **/
            g_array_append_val(rowArray, templatePixel);
        }

        /** Insert row array into vertical array **/
        g_ptr_array_add(verticalArray, rowArray);
    }

    memblk->height = height;
    memblk->width  = width;
}

/** @brief Get the pixel at height and width and the pointer to it into
    @param image image in which the pixel will be searched
    @param height what height is the pixel at
    @param width what is the width of the pixel
    @param copy where the pixel will be copied to
    @return EINVAL (Out of bounds or NULL-Pointer passed)
**/
int Image_GetPixel(image_t* image, guint y, guint x, pixel_t* copy)
{
    GArray* row;
    
    if (image == NULL) {
        return EINVAL;
    }
    if (copy == NULL) {
        return EINVAL;
    }
    if (image->height <= y) {
        return EINVAL; /** Out of bounds **/
    }
    if (image->width <= x) {
        return EINVAL; /** Out of bounds **/
    }

    row = g_ptr_array_index(image->rows, y - 1);
    copy[0] = g_array_index(row, pixel_t, x - 1);

    return EXIT_SUCCESS;
}

/** @brief Sets the value of pixel at (width | height) in image to value
    @param image image in which a pixel shall be modified
    @param y Pixel-Coordinate
    @param x Pixel-Coordinate
    @param value value to set
    @return EINVAL (Out of Bounds, NULLPTR), EXIT_SUCCESS
**/
int Image_SetPixel(image_t* image, guint y, guint x, pixel_t value)
{
    GArray* row;
    pixel_t* pixelPointer;
    
    if (image == NULL) {
        return EINVAL;
    }
    if (y >= image->height) {
        return EINVAL;
    }
    if (x >= image->width) {
        return EINVAL;
    }

    row             = g_ptr_array_index(image->rows, y);
    pixelPointer    = &g_array_index(row, pixel_t, x);
    pixelPointer[0] = value;

    return EXIT_SUCCESS;
}