#include "sdk/ligmaPlug.h"


int Ligma_OnLoad()
{
    return 0;
}

int Ligma_OnUnload()
{
    return 0;
}

int Ligma_GetPlugInfo(pluginfo_t* pluginfo)
{
    pluginfo->name      = g_string_new("Invert");
    pluginfo->about     = g_string_new("This plugin inverts the color of the image in RGB space.");
    pluginfo->publisher = g_string_new("Sleppo04");
    pluginfo->arguments = g_array_new(TRUE, TRUE, sizeof(argument_t));
    return 0;
}

int Ligma_Process(image_t* image)
{
    pixel_t* pixel;
    GArray* row;

    for (int i = 0; i < image->height; i++) {
        row = image->rows->pdata[i];
        for(int j = 0; j < image->width; j++) {
            pixel = row->data + j * sizeof(pixel_t);
            pixel->red   = 255 - pixel->red;
            pixel->green = 255 - pixel->green;
            pixel->blue  = 255 - pixel->blue;
        }
    }

    return 0;
}