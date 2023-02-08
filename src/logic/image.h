#ifndef IMAGES_H
#define IMAGES_H

#include <cairo/cairo.h>
#include <glib.h>

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

typedef struct ARGB32Pixel
{
    uint8_t alpha;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;


/// @brief A struct representing the in-memory image
typedef struct Image {
    /// @brief image data in 2d-array-form
    /// @details each element is a GArray containing pixel_t structs
    GPtrArray*        rows;
    /// @brief Pixel length of a row
    guint            width;
    /// @brief Row count of the image
    guint           height;
} image_t;

#endif//IMAGES_H