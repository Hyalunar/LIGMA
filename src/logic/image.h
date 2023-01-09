#ifndef IMAGES_H
#define IMAGES_H

#include <cairo/cairo.h>

typedef struct Image {
    cairo_surface_t* canvas; // needs to be image surface
} image_t;



#endif//IMAGES_H